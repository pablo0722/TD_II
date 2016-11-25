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
	pin_gpio_init(BUTTON0_INIT);
	pin_gpio_init(BUTTON1_INIT);
	pin_gpio_init(BUTTON2_INIT);
	pin_gpio_init(BUTTON3_INIT);

		// *** Habilito los leds
	pin_gpio_init(LED0_INIT);

		// *** Habilito los gpios del ADC
	pin_gpio_init(ADC_OSR_INIT);
	pin_set(ADC_OSR, 0);

		// *** Habilito los gpios del DAC
	pin_gpio_init(DAC_MUTE_INIT);
	pin_set(DAC_MUTE, 0);
	pin_gpio_init(DAC_ZEROA_INIT);
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
	dac_ext_prepare(buffer_dac_out);
}

void main_init()
{
	SystemCoreClockUpdate();

	Board_Init();

	tft_init();

	#if USE_UART
		uart_init();
	#endif

	adc_dac_init();

	#if USE_FFT
		fft_init();
	#endif

	main_gpio_init();

	main_buffer_init();

	main_task_init();

	#if USE_RTOS
		task_init();
	#endif
}
