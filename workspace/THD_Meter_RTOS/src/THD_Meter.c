/*
===============================================================================
 Name        : THD_Meter.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <cr_section_macros.h>

#include "header.h"


void main_uninit()
{
	/* DeInitialize UART1 peripheral */
	NVIC_DisableIRQ(UART0_IRQn);
	Chip_UART_DeInit(LPC_UART0);
}

int main(void)
{
	main_init();

	#if !USE_RTOS
		while(1)
		{
			#if USE_FFT
				fft_function();
			#endif

			#if USE_UART
				main_uart();
			#endif

			#if USE_ADC_DAC_INTERNO
				main_dac();
			#endif
		}

		main_uninit();
	#endif

	while(1);

    return 0 ;
}
