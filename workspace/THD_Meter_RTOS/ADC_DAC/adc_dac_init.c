/*
 * adc_dac_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_DMA
	void dma_init()
	{
		static char init_flag = 0;

		if(!init_flag)
		{
			Chip_GPDMA_Init(LPC_GPDMA);

			NVIC_DisableIRQ(DMA_IRQn);
			NVIC_SetPriority(DMA_IRQn, ((0x01 << 3) | 0x01));
			NVIC_EnableIRQ(DMA_IRQn);

			#if USE_ADC
			canal_adc = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);
				//Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC,
				//								(uint32_t) GPDMA_CONN_ADC, (uint32_t) dma_memory_adc,
				//								ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
				//DMA_descriptor_ADC.src = GPDMA_CONN_ADC;
			#endif

			#if USE_DAC
			canal_dac = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);
				//Chip_GPDMA_GetFreeChannel(LPC_GPDMA , 0);
				//Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_DAC,
				//								(uint32_t) dma_memory_adc, (uint32_t) GPDMA_CONN_DAC,
				//								DAC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, NULL);
				//DMA_descriptor_DAC.dst = GPDMA_CONN_DAC;
			#endif

				// Setting GPDMA interrupt
			NVIC_EnableIRQ(DMA_IRQn);

			init_flag = 1;
		}
	}
#endif


#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
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

			#if USE_DMA
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


#if USE_ADC
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
#endif


#if USE_DAC
	void dac_init()
	{
		Chip_IOCON_PinMux (LPC_IOCON, 0, 26, MD_PLN, IOCON_FUNC2 ); // P0[26] -> AOUT (salida de DAC)


		Chip_DAC_Init(LPC_DAC);

		Chip_DAC_SetDMATimeOut(LPC_DAC, (SystemCoreClock/4) / (DAC_FREQ * DAC_DMA_CANT_MUESTRAS) ); // Se configura el TimeOut.

		Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DBLBUF_ENA | DAC_CNT_ENA | DAC_DMA_ENA); // Se habilita el DMA y soporte de cuenta.
	}
#endif
