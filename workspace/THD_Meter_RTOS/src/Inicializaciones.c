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

		// *** Habilito los gpios del ADC
	pin_gpio_init(ADC_OSR_INIT);
	pin_set(ADC_OSR, 0);
	pin_gpio_init(ADC_FSYNC_INIT);
	pin_set(ADC_FSYNC, 1);

		// *** Habilito los gpios del DAC
	pin_gpio_init(DAC_MUTE_INIT);
	pin_set(DAC_MUTE, 0);
	pin_gpio_init(DAC_ZEROA_INIT);
	pin_gpio_init(DAC_DATA_INIT);
}

static inline void main_task_init()
{
	task_create(vTask_tft, 		"vTask_tft", 		configMINIMAL_STACK_SIZE, 	NULL, PRIORIDAD_MINIMA, (xTaskHandle *) NULL);
	task_create(vTask_THD, 		"vTask_THD", 		configMINIMAL_STACK_SIZE+8, NULL, PRIORIDAD_MAXIMA, (xTaskHandle *) NULL);
	task_create(vTask_teclado, 	"vTask_teclado", 	configMINIMAL_STACK_SIZE, 	NULL, PRIORIDAD_MINIMA, (xTaskHandle *) NULL);
}

static inline void main_buffer_init()
{
	#if (USE_ADC_EXTERNO)
		adc_ext_prepare(buffer_complex, NULL);
	#endif
	#if (USE_DAC_INTERNO)
		dac_int_prepare(buffer_dac_out);
	#endif
	#if (USE_DAC_EXTERNO)
		dac_ext_prepare(buffer_dac_out);
	#endif
}

void main_init()
{
	SystemCoreClockUpdate();

	Board_Init();

	//tft_init();

	#if USE_UART
		uart_init();
	#endif

	#if (USE_ADC_INTERNO) || (USE_DAC_INTERNO) || (USE_ADC_EXTERNO) || (USE_DAC_EXTERNO)
		adc_dac_init();
	#endif

	#if USE_FFT
		//fft_init();
	#endif

	//main_gpio_init();

	main_buffer_init();

	main_task_init();

	#if USE_RTOS
		task_init();
	#endif
}
