/*
 * tareas.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */

#include "header.h"


#if USE_RTOS
	void vTask_nvic_init(void *pvParameters)
	{
		#if (USE_TIMER)
	       NVIC_EnableIRQ( TIMER1_IRQn );
		#endif

		#if (USE_DMA)
			NVIC_EnableIRQ(DMA_IRQn);
		#endif

		#if ( (USE_ADC_EXTERNO) && (ADC_EXTERNO_MODO == ADC_EXTERNO_INTERRUPCION) ) || \
			( (USE_DAC_EXTERNO) && (DAC_EXTERNO_MODO == DAC_EXTERNO_INTERRUPCION) )
			NVIC_EnableIRQ(I2S_IRQn);
		#endif

		#if (USE_ADC_INTERNO) && (ADC_INTERNO_MODO == ADC_INTERNO_INTERRUPCION)
			NVIC_EnableIRQ(ADC_IRQn);
		#endif

		vTaskDelete(NULL);	// Se mata a si misma luego de inicializar las interrupciones
	}

	void vtask_ImAlive(void * pvParameters)
	{
		pin_gpio_init(LED_IM_ALIVE_INIT);
		pin_gpio_init(LED_1_INIT);
		pin_gpio_init(LED_2_INIT);
		pin_gpio_init(LED_3_INIT);

		while (1)
		{
			Chip_GPIO_SetPinToggle(LPC_GPIO, LED_IM_ALIVE);
			Chip_GPIO_SetPinToggle(LPC_GPIO, LED_1);
			Chip_GPIO_SetPinToggle(LPC_GPIO, LED_2);
			Chip_GPIO_SetPinToggle(LPC_GPIO, LED_3);
			vTaskDelay(500 / portTICK_RATE_MS);
		}
	}

	#if (USE_UART)
		#if (UART0_MODE == UART_MODE_LOOPBACK)
			void vtask_uart(void * pvParameters)
			{
				uint8_t buffer_A[1];
				uint8_t buffer_B[1];
				uint8_t *uart0_buf;

				uart0_leer(buffer_A, buffer_B, 1);

				while (1)
				{
					if( (uart0_buf = uart0_puedo_procesar()) )
					{
						uart0_escribir(uart0_buf, 1);

						while( uart0_escribiendo() );

						uart0_proceso_listo();
					}
					vTaskDelay(20 / portTICK_RATE_MS);
				}
			}
		#else
			void vtask_uart(void * pvParameters)
			{
				while(1);
			}
		#endif
	#endif
#endif
