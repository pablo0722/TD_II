/*
 * Inicializaciones.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


#if (USE_ADC) || (USE_DAC)
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
				//Chip_GPDMA_GetFreeChannel(LPC_GPDMA , 0);
				//Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC,
				//								(uint32_t) GPDMA_CONN_ADC, (uint32_t) dma_memory_adc,
				//								ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
				//DMA_descriptor_ADC.src = GPDMA_CONN_ADC;
			#endif

			#if USE_DAC
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


#if USE_UART
	void uart_init()
	{
		#if USE_UART0
			#if DEBUG_MODE
				printf("[info] init Uart0: \r\n");
				printf("\t Baudrate: %d \r\n", UART_BAUDRATE);
				printf("\t format: 8N1 \r\n");
				printf("\t buffsize: %d \r\n", UART_RRB_SIZE);
				#if UART_BYTE_BY_BYTE
					printf("\t modo: Byte x Byte \r\n");
				#elif UART_BY_VECTOR
					printf("\t modo: Vector x Vector (ping-pong) \r\n");
				#endif
			#endif
			Chip_IOCON_PinMux (LPC_IOCON, 0,  2, MD_PLN, IOCON_FUNC1 ); // P0[2] -> TXD0
			Chip_IOCON_PinMux (LPC_IOCON, 0,  3, MD_PLN, IOCON_FUNC1 ); // P0[3] -> RXD0
			Chip_IOCON_PinMux (LPC_IOCON, 0,  15, MD_PLN, IOCON_FUNC1 ); // P0[15] -> TXD1
			Chip_IOCON_PinMux (LPC_IOCON, 0,  16, MD_PLN, IOCON_FUNC1 ); // P0[16] -> RXD1
		#endif

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


void fft_init()
{
	#if DEBUG_MODE
		printf("[info] init FFT: \r\n");
		printf("\t format: q31 \r\n");
		printf("\t fftLength(solo parte real): %d \r\n", FFT_SIZE);
	#endif

	const uint8_t ifft = FALSE;
	const uint8_t bit_reverse = TRUE;
	const uint16_t fft_length = FFT_SIZE;

	#if DEBUG_MODE
		arm_status st =
	#endif

	arm_rfft_init_q31(&fft_inst_q31, &fft_inst_q31_complex, fft_length, ifft, bit_reverse);

	#if DEBUG_MODE
		if(st != ARM_MATH_SUCCESS)
		{
			printf("[error] FFT init: \r\n");
			printf("\t st = %d \r\n", st);
		}
	#endif
}


#if USE_ADC
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

#if USE_DAC
	void dac_init()
	{
		Chip_IOCON_PinMux (LPC_IOCON, 0, 26, MD_PLN, IOCON_FUNC2 ); // P0[26] -> AOUT (salida de DAC)

		dma_init();

		Chip_DAC_Init(LPC_DAC);

		Chip_DAC_SetDMATimeOut(LPC_DAC, (SystemCoreClock/4) / (DAC_FREQ * DAC_DMA_CANT_MUESTRAS) ); // Se configura el TimeOut.

		Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DBLBUF_ENA | DAC_CNT_ENA | DAC_DMA_ENA); // Se habilita el DMA y soporte de cuenta.
	}
#endif


#if USE_RTOS
	void task_init()
	{
			// Inicializacion de colas
		xQueue_in = xQueueCreate(QUEUE_LEN_IN, QUEUE_ITEM_SIZE_IN);
		xQueue_rem = xQueueCreate(QUEUE_LEN_REM, QUEUE_ITEM_SIZE_REM);
		xQueue_THD = xQueueCreate(QUEUE_LEN_THD, QUEUE_ITEM_SIZE_THD);

		xTaskCreate(vTask_THD, "vTask_THD", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);
	}
#endif


void main_init()
{
	SystemCoreClockUpdate();

	Board_Init();

	#if USE_UART
		uart_init();
	#endif

	#if USE_ADC
		adc_init();
	#endif

	#if USE_DAC
		dac_init();
	#endif

	#if USE_FFT
		fft_init();
	#endif


	#if USE_RTOS
		task_init();
	#endif


	#if (USE_ADC) || (USE_DAC)
		Chip_GPDMA_Transfer(LPC_GPDMA, ADC_DMA_CHANNEL,
								(uint32_t) (GPDMA_CONN_ADC), (uint32_t) dma_memory_adc,
								GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, ADC_DMA_CANT_MUESTRAS);
	#endif


	#if USE_RTOS
		// Start the scheduler so the created tasks start executing.
		vTaskStartScheduler();
	#endif
}
