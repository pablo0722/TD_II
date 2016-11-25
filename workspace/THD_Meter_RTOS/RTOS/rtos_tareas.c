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

		#if (USE_ADC_INTERNO)
			NVIC_EnableIRQ(ADC_IRQn);
		#endif

		#if (USE_ADC_EXTERNO) || (USE_DAC_EXTERNO)
			NVIC_DisableIRQ(I2S_IRQn);
		#endif

		#if (USE_DMA)
			NVIC_EnableIRQ(DMA_IRQn);
		#endif


		vTaskDelete(NULL);	// Se mata a si misma luego de inicianizar las interrupciones
	}

	void vtask_ImAlive(void * pvParameters)
	{
			// Pin 95 - Led 0
		#define P1_0	1,0
		Chip_IOCON_PinMux(LPC_IOCON, P1_0, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_WriteDirBit(LPC_GPIO, P1_0, true); // true = output - false = input

		while (1)
		{
			Chip_GPIO_SetPinToggle(LPC_GPIO, P1_0);
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
