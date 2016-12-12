/*
===============================================================================
 Name        : eqh.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/


#include <header.h>

/*****************************************************************************
 * Private defines
 ****************************************************************************/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

int main(void)
{
	uint32_t *aux_error= &CONT_ERROR;
	*aux_error = 0;

	main_init();

	#if USE_RTOS

		// Creo las task
		task_init();

		// Start the scheduler
		vTaskStartScheduler();

		// Should never arrive here
		return 1;

	#else
		while(1)
		{
			#if USE_FFT
				fft_function();
			#endif

			#if USE_UART
				main_uart();
			#endif

			#if USE_DAC_INTERNO

			#endif
		}
	#endif

	while(1);

    return 0;
}



