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
	pin_gpio_init(BUTTON0, MD_PUP, ENTRADA);
	pin_gpio_init(BUTTON1, MD_PUP, ENTRADA);
	pin_gpio_init(BUTTON2, MD_PUP, ENTRADA);
	pin_gpio_init(BUTTON3, MD_PUP, ENTRADA);
}

static inline void main_task_init()
{
	task_create(vTask_tft, 		"vTask_tft", 		configMINIMAL_STACK_SIZE, 	NULL, PRIORIDAD_MINIMA, (xTaskHandle *) NULL);
	task_create(vTask_THD, 		"vTask_THD", 		configMINIMAL_STACK_SIZE+8, NULL, PRIORIDAD_MINIMA, (xTaskHandle *) NULL);
	task_create(vTask_teclado, 	"vTask_teclado", 	configMINIMAL_STACK_SIZE, 	NULL, PRIORIDAD_MINIMA, (xTaskHandle *) NULL);
}

static inline void main_buffer_init()
{
	adc_ext_prepare(buffer_complex, NULL);
}

void main_init()
{
	SystemCoreClockUpdate();

	Board_Init();

	main_gpio_init();

	main_buffer_init();

	main_task_init();

	tft_init();

	#if USE_UART
		uart_init();
	#endif

	//adc_dac_init();

	#if USE_FFT
		fft_init();
	#endif

	#if USE_RTOS
		task_init();
	#endif
}
