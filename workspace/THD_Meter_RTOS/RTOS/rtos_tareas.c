/*
 * tareas.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */

#include "header.h"


#if USE_RTOS
	void vtask_ImAlive(void * pvParameters)
	{
		while (1)
		{
			Board_LED_Toggle(0, 22);
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
