/*
===============================================================================
 Name        : test_PCM1802_PCM1781.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#include "i2s_17xx_40xx.h"

/*****************************************************************************
 * Private defines
 ****************************************************************************/

#define	I2S_INT_POLLING			0
#define I2S_DMA					1

#define LED_stick				0,22
#define AOUT					0,26

#define I2SRX_CLK				0,4
#define I2SRX_WS				0,5
#define I2SRX_SDA				0,6
#define RX_MCLK					4,28

#define I2STX_CLK				0,7
#define I2STX_WS				0,8
#define I2STX_SDA				0,9
#define TX_MCLK					4,29

#define CH_L					1
#define CH_R					2


#define BURST_MODE

#define DMA_DESCRIPTOR_COUNT   	256

#define TRANSFER_BLOCK     		GPDMA_BSIZE_128 /* size of data transfered per LLI */

#define CANT_DESC 				4

#define TRANSFER_SIZE          	(TRANSFER_BLOCK_SZ * CANT_DESC)

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

uint8_t DMA_I2S_RX_CH_A = 0;
uint8_t DMA_I2S_RX_CH_B = 0;
uint32_t bufferA[128], bufferB[128];

// descriptores del dma
static DMA_TransferDescriptor_t RX_descriptorA;
static DMA_TransferDescriptor_t RX_descriptorB;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

void prepare_DMA_descriptors()
{
	#if CANT_DESC > DMA_DESCRIPTOR_COUNT
		#error Transfer needs CANT_DESC descriptors, but has DMA_DESCRIPTOR_COUNT descriptors only
	#endif

	Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &RX_descriptorA,
		(uint32_t) GPDMA_CONN_I2S_Channel_0,
		(uint32_t) bufferA,
		(uint32_t) (GPDMA_BSIZE_128),
		GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
		NULL);
/*
	Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &RX_descriptorB,
		(uint32_t) GPDMA_CONN_I2S_Channel_1,
		(uint32_t) bufferA,
		(uint32_t) (GPDMA_BSIZE_128),
		GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
		NULL);*/
}

void link_DMA_descriptor()
{
	uint8_t error_SGTransfer = SUCCESS;
	DMA_TransferDescriptor_t templli;

	// create a temporary LLI for the API call, this can be discarded after the call
	templli = RX_descriptorA;
	templli.src = GPDMA_CONN_I2S_Channel_0;

	Chip_GPDMA_Stop(LPC_GPDMA, DMA_I2S_RX_CH_A);
	error_SGTransfer = Chip_GPDMA_SGTransfer(LPC_GPDMA, DMA_I2S_RX_CH_A, &templli,
											GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
	if(error_SGTransfer == ERROR)
	{
		error_SGTransfer = SUCCESS;
	}
}

static void InitHardware(void)
{
	// Configuro el timer del micro en 120MHz						NO ANDA!
	Chip_SetupXtalClocking();
	Chip_SYSCTL_SetFLASHAccess(FLASHTIM_120MHZ_CPU);

	SystemCoreClockUpdate();

	// Led del stick
	Chip_IOCON_PinMux(LPC_IOCON, LED_stick, MD_PLN, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, LED_stick);

	// Init DAC
	Chip_DAC_Init(LPC_DAC);
	Chip_IOCON_PinMux(LPC_IOCON, AOUT, MD_PLN, IOCON_FUNC2);

#if I2S_DMA

	// Init GPDMA
	Chip_GPDMA_Init(LPC_GPDMA);

	NVIC_DisableIRQ(DMA_IRQn);

	// chequeo canal libre y lo habilito
	Chip_GPDMA_ChannelCmd(LPC_GPDMA, DMA_I2S_RX_CH_A, DISABLE);
	DMA_I2S_RX_CH_A = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);

	Chip_GPDMA_ChannelCmd(LPC_GPDMA, DMA_I2S_RX_CH_B, DISABLE);
	DMA_I2S_RX_CH_B = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);

	if(DMA_I2S_RX_CH_A == -1)
	{
		//Error, no hay canal libre
		DMA_I2S_RX_CH_A = -1;
	}

	if(DMA_I2S_RX_CH_B == -1)
	{
		//Error, no hay canal libre
		DMA_I2S_RX_CH_B = -1;
	}

	Chip_GPDMA_Stop(LPC_GPDMA, DMA_I2S_RX_CH_A);
	Chip_GPDMA_Stop(LPC_GPDMA, DMA_I2S_RX_CH_B);

	prepare_DMA_descriptors();

	#ifdef BURST_MODE
	#endif

	//Chip_GPDMA_Interrupt()
	//Chip_GPDMA_IntGetStatus()
	//Chip_GPDMA_ClearIntPending()
#endif

	// Init I2S
	// Configuro los pines de RX de P0, ver defines
	Chip_IOCON_PinMux(LPC_IOCON, I2SRX_CLK, MD_PLN, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, I2SRX_SDA, MD_PLN, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, I2SRX_WS, MD_PLN, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, RX_MCLK, MD_PLN, IOCON_FUNC1);
	// Configuro los pibes del TX de P0, ver defines
	Chip_IOCON_PinMux(LPC_IOCON, I2STX_CLK, MD_PLN, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, I2STX_SDA, MD_PLN, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, I2STX_WS, MD_PLN, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, TX_MCLK, MD_PLN, IOCON_FUNC1);

	// Configuro I2S_TX usando la estructura I2S_AUDIO_FORMAT_T y modifico la función
	I2S_AUDIO_FORMAT_T audio_Confg;
	audio_Confg.SampleRate = 32000;
	audio_Confg.ChannelNumber = 2;			// 1 mono 2 stereo
	audio_Confg.WordWidth = 32;				// Word Len

	// Configuro el clk del periférico para que trabaje a 96MHz
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_I2S, SYSCTL_CLKDIV_1);

	Chip_I2S_Init(LPC_I2S);

	Chip_I2S_RxStop(LPC_I2S);
	Chip_I2S_TxStop(LPC_I2S);
	Chip_I2S_EnableMute(LPC_I2S);

	// Configuro modo RX
//	Chip_I2S_RxModeConfig(LPC_I2S, 0, 1, ENABLE);
//	Chip_I2S_SetRxBitRate(LPC_I2S, 1);
//	Chip_I2S_SetRxXYDivider(LPC_I2S, 1, 1);
	Chip_I2S_RxConfig(LPC_I2S, &audio_Confg);

	// Configuro modo TX
//	Chip_I2S_TxModeConfig(LPC_I2S, 0, 0, 1);
//	Chip_I2S_SetTxBitRate(LPC_I2S, 5);
//	Chip_I2S_SetTxXYDivider(LPC_I2S, 32, 125);
	Chip_I2S_TxConfig(LPC_I2S, &audio_Confg);
	Chip_I2S_Int_TxCmd(LPC_I2S, DISABLE, 1);

	Chip_I2S_DisableMute(LPC_I2S);
	Chip_I2S_RxStart(LPC_I2S);
	Chip_I2S_TxStart(LPC_I2S);

#if I2S_INT_POLLING
	Chip_I2S_Int_RxCmd(LPC_I2S, ENABLE, 1);
	NVIC_EnableIRQ(I2S_IRQn);
#else
	Chip_I2S_Int_RxCmd(LPC_I2S, ENABLE, 1);
	NVIC_DisableIRQ(I2S_IRQn); //la interrupcion de i2s es para hacer pooling

	link_DMA_descriptor();

	NVIC_SetPriority(DMA_IRQn, ((0x01 << 3) | 0x01));
	NVIC_EnableIRQ(DMA_IRQn);


#endif

}

static int32_t data, dataa = 0xFAFAF0F0;
static uint16_t adcFlag = 1;

#if I2S_INT_POLLING
void I2S_IRQHandler(void)
{
	if(Chip_I2S_GetRxLevel(LPC_I2S))
	{
		data = Chip_I2S_Receive(LPC_I2S);
		adcFlag=1;

	}
	Chip_I2S_Send(LPC_I2S, dataa);
}
#endif

#if I2S_DMA

uint8_t BufferA_ready = 0;
uint8_t BufferB_ready = 0;

void DMA_IRQHandler(void)
{
	if(Chip_GPDMA_Interrupt(LPC_GPDMA, DMA_I2S_RX_CH_A))
	{
		if(Chip_GPDMA_IntGetStatus(LPC_GPDMA, GPDMA_STAT_INTTC, DMA_I2S_RX_CH_A))
		{
			Chip_GPDMA_ClearIntPending(LPC_GPDMA, GPDMA_STATCLR_INTTC, DMA_I2S_RX_CH_A);
			BufferA_ready= 1;
		}
	}

	if(Chip_GPDMA_Interrupt(LPC_GPDMA, DMA_I2S_RX_CH_B))
	{
		if(Chip_GPDMA_IntGetStatus(LPC_GPDMA, GPDMA_STAT_INTTC, DMA_I2S_RX_CH_B))
		{
			Chip_GPDMA_ClearIntPending(LPC_GPDMA, GPDMA_STATCLR_INTTC, DMA_I2S_RX_CH_B);
			BufferB_ready= 1;
		}
	}

	Chip_GPDMA_Interrupt(LPC_GPDMA, DMA_I2S_RX_CH_A);
}
#endif

/*****************************************************************************
 * Public functions
 ****************************************************************************/

int main(void)
{
	int count = 0, sel = CH_L, i;

	InitHardware();

	while(1){

		if(adcFlag)
		{
#if I2S_INT_POLLING
			if(data < 0)
				data = (data >> 8);
			else
			{
				data = data >> 8 ;
				data &= (0x00FFFFFF);
			}

			if(sel == CH_L)
			{
				if(data < 1024)
					data = data + 512;
				else
					data = data - 512;

				Chip_DAC_UpdateValue(LPC_DAC, data);
				adcFlag = 0;
				sel = CH_R;
			}
			else
				sel = CH_L;

/*+++++++++++++++++++++++++++ Si uso DMA +++++++++++++++++++++++++++*/
#else
	/* BUFFER A listo para procesar */
	if(BufferA_ready)
	{
		for(i=0; i<128; i++)
		{
			if(bufferA[i] < 0)
				bufferA[i] = (bufferA[i] >> 8);
			else
			{
				bufferA[i] = bufferA[i] >> 8 ;
				bufferA[i] &= (0x00FFFFFF);
			}

			if(sel == CH_L)
			{
				if(bufferA[i] < 1024)
					bufferA[i] = bufferA[i] + 512;
				else
					bufferA[i] = bufferA[i] - 512;

				Chip_DAC_UpdateValue(LPC_DAC, bufferA[i]);
				adcFlag = 0;
				sel = CH_R;
			}
			else
				sel = CH_L;
		}
	}
	/* BUFFER B listo para procesar */
	if(BufferB_ready)
	{
		for(i=0; i<128; i++)
		{
			if(bufferB[i] < 0)
				bufferB[i] = (bufferB[i] >> 8);
			else
			{
				bufferB[i] = bufferB[i] >> 8 ;
				bufferB[i] &= (0x00FFFFFF);
			}

			if(sel == CH_L)
			{
				if(bufferB[i] < 1024)
					bufferB[i] = bufferB[i] + 512;
				else
					bufferB[i] = bufferB[i] - 512;

				Chip_DAC_UpdateValue(LPC_DAC, bufferB[i]);
				adcFlag = 0;
				sel = CH_R;
			}
			else
				sel = CH_L;
		}
	}
#endif
		}

/*+++++++++++++++++++++++++++ Parpadeo de led testido +++++++++++++++++++++++++++*/
		if(count == 500000)
		{
			Chip_GPIO_SetPinToggle(LPC_GPIO, LED_stick);
			count = 0;
		}
		count ++;

	}

	while(1);

	/* Should never arrive here */
	return 1;
}

