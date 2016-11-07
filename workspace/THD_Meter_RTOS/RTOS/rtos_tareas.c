/*
 * tareas.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */

#include "header.h"


q31_t THD;
q31_t fft_max;
uint32_t fft_max_idx;
q31_t fft_min;
q31_t fft_cmplx[FFT_SIZE*2];


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

	void vTask_main(void *pvParameters)
	{
		while(1)
		{
			xSemaphoreTake(sem_timer0_match1, 0);

			if(Chip_GPIO_GetPinState(LPC_GPIO, BUTTON0))
			{
				flag_use_dac = TRUE;
				flag_do_thd = FALSE;
				flag_do_rem = FALSE;
			}
			if(Chip_GPIO_GetPinState(LPC_GPIO, BUTTON1))
			{
				flag_use_dac = FALSE;
				flag_do_thd = TRUE;
				flag_do_rem = FALSE;
			}
			if(Chip_GPIO_GetPinState(LPC_GPIO, BUTTON2))
			{
				flag_use_dac = FALSE;
				flag_do_thd = FALSE;
				flag_do_rem = TRUE;
			}
		}
	}

	void vTask_THD( void *pvParameters )
	{
		q31_t num = 0; 	// Es la raiz cuadrada de la suma cuadratica de los armonicos de la DEP (numerador del THD)
		uint32_t i;
		q31_t fft_dep[FFT_SIZE/2];

		while(1)
		{
			xSemaphoreTake(sem_adc_proc, 0);

				// Obtengo la fft
			fft_toCmplx((q31_t *)dma_adc_ext_memory, fft_cmplx);
			fft_toDep(fft_cmplx, fft_dep);

				// Busco el piso de ruido a traves del minimo valor
			arm_min_q31(fft_dep, FFT_SIZE/2, &fft_min, &fft_max_idx);

				// Busco la fundamental a traves del maximo valor
			arm_max_q31(fft_dep, FFT_SIZE/2, &fft_max, &fft_max_idx);


				// *** THD *** //
			if(flag_do_thd)
			{
					// Armado del numerador de la división, sumará armonicos hasta el fin del vector, el denominador es max_val
				for(i=2; i*fft_max_idx < FFT_SIZE; i++)
				{
					num += fft_dep[i*fft_max_idx];
					i++;
				}

				arm_sqrt_q31(num, &num);

				/* calculo de THD propiamente dicho */
				THD = num/fft_max;
			}
				// *** REMANENTE *** //
			else if(flag_do_rem)
			{
				// Al espectro obtenido debo quitarle el primer armonico (a la parte real y a la imaginaria
				fft_cmplx[fft_max_idx*2] = fft_cmplx[fft_max_idx*2-1] = fft_min;
				fft_toReal(fft_cmplx, (q31_t *) dma_adc_ext_memory);
			}

			adc_post_procesamiento();
		}
	}
#endif
