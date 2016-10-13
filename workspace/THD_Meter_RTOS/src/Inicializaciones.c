/*
 * Inicializaciones.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


#ifdef USE_DMA
	void dma_init()
	{
		static char init_flag = 0;

		if(!init_flag)
		{
			Chip_GPDMA_Init(LPC_GPDMA);

			NVIC_DisableIRQ(DMA_IRQn);
			NVIC_SetPriority(DMA_IRQn, ((0x01 << 3) | 0x01));
			NVIC_EnableIRQ(DMA_IRQn);

			canal_adc = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);
//			Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC,
//											(uint32_t) GPDMA_CONN_ADC, (uint32_t) dma_memory_adc,
//											ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
//			DMA_descriptor_ADC.src = GPDMA_CONN_ADC;

			canal_dac = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);
//			Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_DAC,
//											(uint32_t) dma_memory_adc, (uint32_t) GPDMA_CONN_DAC,
//											DAC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, NULL);
//			DMA_descriptor_DAC.dst = GPDMA_CONN_DAC;

				// Setting GPDMA interrupt
			NVIC_EnableIRQ(DMA_IRQn);

			init_flag = 1;
		}
	}
#endif


#ifdef USE_ADC_DAC_EXTERNO
	/* Get divider value */
	STATIC Status getClkDiv(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format, uint16_t *pxDiv, uint16_t *pyDiv, uint32_t *pN)
	{
		uint32_t pClk;
		uint32_t x, y;
		uint64_t divider;
		uint16_t dif;
		uint16_t xDiv = 0, yDiv = 0;
		uint32_t N;
		uint16_t err, ErrorOptimal = 0xFFFF;

	#if defined(CHIP_LPC175X_6X)
		pClk = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_I2S);
	#else
		pClk = Chip_Clock_GetPeripheralClockRate();
	#endif

		/* divider is a fixed point number with 16 fractional bits */
		divider = (((uint64_t) (format->SampleRate) * 2 * (format->WordWidth) * 2) << 16) / pClk;
		/* find N that make x/y <= 1 -> divider <= 2^16 */
		for (N = 64; N > 0; N--) {
			if ((divider * N) < (1 << 16)) {
				break;
			}
		}
		if (N == 0) {
			return ERROR;
		}
		divider *= N;
		for (y = 255; y > 0; y--) {
			x = y * divider;
			if (x & (0xFF000000)) {
				continue;
			}
			dif = x & 0xFFFF;
			if (dif > 0x8000) {
				err = 0x10000 - dif;
			}
			else {
				err = dif;
			}
			if (err == 0) {
				yDiv = y;
				break;
			}
			else if (err < ErrorOptimal) {
				ErrorOptimal = err;
				yDiv = y;
			}
		}
		xDiv = ((uint64_t) yDiv * (format->SampleRate) * 2 * (format->WordWidth) * N * 2) / pClk;
		if (xDiv >= 256) {
			xDiv = 0xFF;
		}
		if (xDiv == 0) {
			xDiv = 1;
		}

		*pxDiv = xDiv;
		*pyDiv = yDiv;
		*pN = N;
		return SUCCESS;
	}


	/* Configure I2S for Audio Format input */
	Status mi_Chip_I2S_TxConfig(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format)
	{
		uint32_t temp;
		uint16_t xDiv, yDiv;
		uint32_t N;


		if (getClkDiv(pI2S, format, &xDiv, &yDiv, &N) == ERROR)
		{
			return ERROR;
		}

		temp = pI2S->DAO & (~(I2S_DAO_WORDWIDTH_MASK | I2S_DAO_MONO | I2S_DAO_SLAVE | I2S_DAO_WS_HALFPERIOD_MASK));
		if (format->WordWidth <= 8)
		{
			temp |= I2S_WORDWIDTH_8;
		}
		else if (format->WordWidth <= 16)
		{
			temp |= I2S_WORDWIDTH_16;
		}
		else
		{
			temp |= I2S_WORDWIDTH_32;
		}

		temp |= (format->ChannelNumber) == 1 ? I2S_MONO : I2S_STEREO;
		temp |= I2S_MASTER_MODE;
		temp |= I2S_DAO_WS_HALFPERIOD(format->WordWidth - 1);
		pI2S->DAO = temp;

		pI2S->TXMODE = 0x8;

		Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_I2S);

		xDiv = 32;
		yDiv = 125;

		pI2S->TXBITRATE = 5;

		pI2S->TXRATE = yDiv | (xDiv << 8);
		return SUCCESS;
	}


	/* Configure I2S for Audio Format input */
	Status mi_Chip_I2S_RxConfig(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format)
	{
		uint32_t temp;
		uint16_t xDiv, yDiv;
		uint32_t N;

		if (getClkDiv(pI2S, format, &xDiv, &yDiv, &N) == ERROR) {
			return ERROR;
		}
		temp = pI2S->DAI & (~(I2S_DAI_WORDWIDTH_MASK | I2S_DAI_MONO | I2S_DAI_SLAVE | I2S_DAI_WS_HALFPERIOD_MASK));
		if (format->WordWidth <= 8)
		{
			temp |= I2S_WORDWIDTH_8;
		}
		else if (format->WordWidth <= 16)
		{
			temp |= I2S_WORDWIDTH_16;
		}
		else
		{
			temp |= I2S_WORDWIDTH_32;
		}

		temp |= (format->ChannelNumber) == 1 ? I2S_MONO : I2S_STEREO;
		temp |= I2S_MASTER_MODE;
		temp |= I2S_DAI_WS_HALFPERIOD(format->WordWidth - 1);
		pI2S->DAI = temp;

		pI2S->RXMODE = 0x8;

		Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_I2S);

		xDiv = 32;
		yDiv = 125;

		pI2S->RXBITRATE = 5;

		pI2S->RXRATE = yDiv | (xDiv << 8);
		return SUCCESS;
	}

	void i2s_init()
	{
		static char init_flag = 0;

		if(!init_flag)
		{
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


			Chip_I2S_DisableMute(LPC_I2S);
			Chip_I2S_RxStart(LPC_I2S);
			Chip_I2S_TxStart(LPC_I2S);

			Chip_I2S_Int_RxCmd(LPC_I2S, ENABLE, 1);
			Chip_I2S_Int_TxCmd(LPC_I2S, DISABLE, 1);

			// Configuro modo RX
			mi_Chip_I2S_RxConfig(LPC_I2S, &audio_Confg);
			// Configuro modo TX
			mi_Chip_I2S_TxConfig(LPC_I2S, &audio_Confg);

			#ifdef USE_DMA
				Chip_I2S_DMA_RxCmd(LPC_I2S, I2S_DMA_REQUEST_CHANNEL_1, ENABLE, 1);
				Chip_I2S_DMA_TxCmd(LPC_I2S, I2S_DMA_REQUEST_CHANNEL_2, ENABLE, 1);

				NVIC_DisableIRQ(I2S_IRQn);
			#else

				NVIC_EnableIRQ(I2S_IRQn);
			#endif


			init_flag = 1;
		}
	}
#endif


#ifdef USE_UART
	void uart_init()
	{
		Board_UART_Init((uint32_t)LPC_UART0, 9600);

		// Before using the ring buffers, initialize them using the ring
		// buffer init function
		RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
		RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

		// Enable receive data and line status interrupt
		Chip_UART_IntEnable(LPC_UART0, (UART_IER_RBRINT | UART_IER_RLSINT));

		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(UART0_IRQn, 1);
		NVIC_EnableIRQ(UART0_IRQn);

		const char Uart_init_msg[] = "\r\nHola mundo:\r\n";

		/* Envia mensaje inicial por UART*/
		Chip_UART_SendRB(LPC_UART0, &txring, Uart_init_msg, sizeof(Uart_init_msg));


			// Inicializacion de colas
		xQueue_in = xQueueCreate(QUEUE_LEN_IN, QUEUE_ITEM_SIZE_IN);
		xQueue_rem = xQueueCreate(QUEUE_LEN_REM, QUEUE_ITEM_SIZE_REM);
		xQueue_THD = xQueueCreate(QUEUE_LEN_THD, QUEUE_ITEM_SIZE_THD);

		xTaskCreate(vTask_THD, "vTask_THD", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);
	}
#endif

#ifdef USE_FFT
	void fft_init()
	{
			memset(mSignalIn, 	0, sizeof(int16_t) * LENGTH_SAMPLES );	//Inicializo en 0 la entrada
			memset(mFFTOut, 	0, sizeof(int16_t) * LENGTH_SAMPLES);		//Inicializo en 0 la salida
	}
#endif


#ifdef USE_ADC_DAC_INTERNO
	void adc_init()
	{
		Chip_IOCON_PinMux (LPC_IOCON, 0, 23, MD_PLN, IOCON_FUNC1 ); // P0[23] -> AD0.0 (entrada de ADC)


		ADC_CLOCK_SETUP_T adc;

		Chip_ADC_Init(LPC_ADC, &adc);
		NVIC_DisableIRQ(ADC_IRQn);
		Chip_ADC_EnableChannel(LPC_ADC, ADC_CH0, ENABLE);
		Chip_ADC_SetSampleRate(LPC_ADC, &adc, ADC_FREQ);
		Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH0, ENABLE);
		Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);
		//Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING); // cuando NO es modo Burst
	}

	void dac_init()
	{
		Chip_IOCON_PinMux (LPC_IOCON, 0, 26, MD_PLN, IOCON_FUNC2 ); // P0[26] -> AOUT (salida de DAC)


		Chip_DAC_Init(LPC_DAC);

		Chip_DAC_SetDMATimeOut(LPC_DAC, (SystemCoreClock/4) / (DAC_FREQ * DAC_DMA_CANT_MUESTRAS) ); // Se configura el TimeOut.

		Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DBLBUF_ENA | DAC_CNT_ENA | DAC_DMA_ENA); // Se habilita el DMA y soporte de cuenta.
	}
#endif

void main_init()
{
	SystemCoreClockUpdate();

	Board_Init();

	#ifdef USE_UART
		uart_init();
	#endif

	#ifdef USE_FFT
		fft_init();
	#endif

	#ifdef USE_DMA
		dma_init();
	#endif

	#ifdef USE_ADC_DAC_INTERNO
		adc_init();
		dac_init();
	#endif

	#ifdef USE_ADC_DAC_EXTERNO
		i2s_init();
	#endif


	#ifdef USE_ADC_DAC_EXTERNO_DMA
		Chip_GPDMA_Transfer(LPC_GPDMA, canal_adc,
								(uint32_t) (GPDMA_CONN_I2S_Channel_1), (uint32_t) dma_memory_adc,
								GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, ADC_DMA_CANT_MUESTRAS);
	#endif


	// Start the scheduler so the created tasks start executing.
	// vTaskStartScheduler();
}
