/*
 * Inicializaciones.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


#if defined(USE_ADC) || defined(USE_DAC)
	void dma_init()
	{
		static char init_flag = 0;

		if(!init_flag)
		{
			Chip_GPDMA_Init(LPC_GPDMA);

			NVIC_DisableIRQ(DMA_IRQn);
			NVIC_SetPriority(DMA_IRQn, ((0x01 << 3) | 0x01));
			NVIC_EnableIRQ(DMA_IRQn);

			#ifdef USE_ADC
				//Chip_GPDMA_GetFreeChannel(LPC_GPDMA , 0);
				//Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC,
				//								(uint32_t) GPDMA_CONN_ADC, (uint32_t) dma_memory_adc,
				//								ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
				//DMA_descriptor_ADC.src = GPDMA_CONN_ADC;
			#endif

			#ifdef USE_DAC
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


#ifdef USE_UART
	void uart_init()
	{
		Board_UART_Init((uint32_t)LPC_UARTN, UART_BAUDRATE);

		// Before using the ring buffers, initialize them using the ring
		// buffer init function
		RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
		RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

		// Enable receive data and line status interrupt
		Chip_UART_IntEnable(LPC_UARTN, (UART_IER_RBRINT | UART_IER_RLSINT));

		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(UARTN_IRQn, 1);
		NVIC_EnableIRQ(UARTN_IRQn);

		const char Uart_init_msg[] = "\r\nHola mundo:\r\n";

		/* Envia mensaje inicial por UART*/
		Chip_UART_SendRB(LPC_UARTN, &txring, Uart_init_msg, sizeof(Uart_init_msg));
	}
#endif

int fft_init()
{
	const uint8_t ifft = FALSE;
	const uint8_t bit_reverse = TRUE;
	const uint16_t fft_length = FFT_SIZE*2; // el "*2" es porque el espectro original esta espejado
	arm_status status = ARM_MATH_SUCCESS;

	status = arm_cfft_radix2_init_q31(&fft_inst_q31, fft_length, ifft, bit_reverse);
	if(status == ARM_MATH_TEST_FAILURE)
	{
		return -1;
	}

	return 0;
}

#ifdef USE_ADC
	void adc_init()
	{
		Chip_IOCON_PinMux (LPC_IOCON, 0, 23, MD_PLN, IOCON_FUNC1 ); // P0[23] -> AD0.0 (entrada de ADC)

		dma_init();

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

#ifdef USE_DAC
	void dac_init()
	{
		Chip_IOCON_PinMux (LPC_IOCON, 0, 26, MD_PLN, IOCON_FUNC2 ); // P0[26] -> AOUT (salida de DAC)

		dma_init();

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

	#ifdef USE_ADC
		adc_init();
	#endif

	#ifdef USE_DAC
		dac_init();
	#endif

	#ifdef USE_FFT
		fft_init();
	#endif


	#if defined(USE_ADC) || defined(USE_DAC)
		Chip_GPDMA_Transfer(LPC_GPDMA, ADC_DMA_CHANNEL,
								(uint32_t) (GPDMA_CONN_ADC), (uint32_t) dma_memory_adc,
								GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, ADC_DMA_CANT_MUESTRAS);
	#endif


	// Start the scheduler so the created tasks start executing.
	// vTaskStartScheduler();
}
