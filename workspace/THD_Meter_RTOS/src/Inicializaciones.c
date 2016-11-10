/*
 * Inicializaciones.c
 *
 *  Created on: 22 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


static inline void main_gpio_init()
{
		// *** Habilito los botones
//	pin_init(LPC_IOCON, BUTTON0, MD_PLN, IOCON_FUNC0, ENTRADA);
//	pin_init(LPC_IOCON, BUTTON1, MD_PLN, IOCON_FUNC0, ENTRADA);
//	pin_init(LPC_IOCON, BUTTON2, MD_PLN, IOCON_FUNC0, ENTRADA);
//	pin_init(LPC_IOCON, BUTTON3, MD_PLN, IOCON_FUNC0, ENTRADA);
}

static inline void main_task_init()
{
	xTaskCreate(vTask_tft, 		"vTask_tft", 		configMINIMAL_STACK_SIZE, 					NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
	xTaskCreate(vTask_THD, 		"vTask_THD", 		configMINIMAL_STACK_SIZE+4+4+4*FFT_SIZE/2, 	NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
	xTaskCreate(vTask_teclado, 	"vTask_teclado", 	configMINIMAL_STACK_SIZE, 					NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
}

void main_init()
{
	SystemCoreClockUpdate();

	Board_Init();

	main_gpio_init();

	tft_init();

	#if USE_UART
		uart_init();
	#endif

	#if USE_ADC_INTERNO
		adc_init();
	#endif

	#if USE_FFT
		fft_init();
	#endif

	main_task_init();

	#if USE_RTOS
		task_init();
	#endif
}
