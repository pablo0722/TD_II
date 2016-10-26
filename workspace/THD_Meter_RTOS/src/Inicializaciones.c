/*
 * Inicializaciones.c
 *
 *  Created on: 22 de oct. de 2016
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

	#if USE_ADC_INTERNO
		adc_init();
	#endif

	#if USE_DAC_INTERNO
		dac_init();
	#endif

	#if (USE_ADC_EXTERNO) || (USE_DAC_EXTERNO)
		i2s_init();
	#endif

	#if USE_DMA
		dma_init();
	#endif

	#if USE_FFT
		fft_init();
	#endif


	#if USE_RTOS
		task_init();
	#endif
}
