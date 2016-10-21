/*
 * Inicializaciones.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



void main_init()
{
	SystemCoreClockUpdate();

	Board_Init();

	#if USE_UART
		uart_init();
	#endif

	#if USE_ADC_DAC_INTERNO
		adc_init();
		dac_init();
	#endif

	#if USE_ADC_DAC_EXTERNO
		i2s_init();
	#endif

	#if USE_FFT
		fft_init();
	#endif

	#if USE_DMA
		dma_init();
	#endif


	#if USE_ADC_DMA
		Chip_GPDMA_Transfer(LPC_GPDMA, canal_adc,
								(uint32_t) (GPDMA_CONN_I2S_Channel_1), (uint32_t) dma_memory_adc,
								GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, ADC_DMA_CANT_MUESTRAS);
	#endif


	#if USE_RTOS
		task_init();
	#endif
}
