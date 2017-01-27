/*
 * procesamiento.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


#if (USE_RTOS)
	void vTask_teclado(void *pvParameters)
	{
		while(1)
		{
			if(!pin_get(BUTTON0))
			{
				flag_dac_send = TRUE;
				flag_do_thd = FALSE;
				flag_do_rem = FALSE;
			}
			if(!pin_get(BUTTON1))
			{
				flag_dac_send = FALSE;
				flag_do_thd = TRUE;
				flag_do_rem = FALSE;
			}
			if(!pin_get(BUTTON2))
			{
				flag_dac_send = FALSE;
				flag_do_thd = FALSE;
				flag_do_rem = TRUE;
			}

			vTaskDelay(50/portTICK_RATE_MS);
		}
	}

	void vTask_tft(void *pvParameters)
	{
		#if (USE_TFT)
			tft_Fill(TFT_COLOR_BLACK);
			tft_Puts(0, 0, 		"TECNICAS DIGITALES",	&tft_Font_11x18, 	TFT_FOREGROUND_GREEN, 	TFT_BACKGROUND_BLACK);
			tft_Puts(120, 25, 	"II",					&tft_Font_11x18, 	TFT_FOREGROUND_RED, 	TFT_BACKGROUND_BLACK);
			tft_Puts(0, 50, 	"PROCESAMIENTO DE",		&tft_Font_11x18, 	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
			tft_Puts(100, 75, 	"AUDIO",				&tft_Font_11x18, 	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
			tft_Puts(0, 100, 	"MENU",					&tft_Font_11x18,	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
			tft_Puts(50, 125, 	"Reverb",				&tft_Font_11x18,	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
			tft_Puts( 50, 150, 	"Echo",					&tft_Font_11x18, 	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
			tft_Puts(50, 175, 	"High Pass Filter",		&tft_Font_11x18,  	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
			tft_Puts(50, 200, 	"Low Pass Filter",		&tft_Font_11x18,  	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);

			tft_DrawFilledCircle(30, 135, 7, TFT_COLOR_WHITE);
			tft_DrawFilledCircle(30, 160, 7, TFT_COLOR_WHITE);
			tft_DrawFilledCircle(30, 185, 7, TFT_COLOR_WHITE);
			tft_DrawFilledCircle(30, 210, 7, TFT_COLOR_WHITE);
		#endif

		while(1)
		{
			#if (USE_TFT)
				if(flag_dac_send)
					tft_Puts(200, 20, "Boton 0",	&tft_Font_11x18, 	TFT_FOREGROUND_RED, 	TFT_BACKGROUND_BLACK);
				if(flag_do_thd)
					tft_Puts(200, 20, "Boton 1",	&tft_Font_11x18, 	TFT_FOREGROUND_GREEN, 	TFT_BACKGROUND_BLACK);
				if(flag_do_rem)
					tft_Puts(200, 20, "Boton 2",	&tft_Font_11x18, 	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);

				vTaskDelay(100/portTICK_PERIOD_MS);
			#endif
		}
	}

	void vTask_THD(void *pvParameters)
	{
		//q31_t num = 0; 	// Es la raiz cuadrada de la suma de los armonicos de la DEP (numerador del THD)
		uint32_t i, j;

		for(i=0; i<FFT_SIZE*2; i++)
			buffer_dac_out[i] = i*128;

		while(1)
		{
			//if( (flag_do_thd) || (flag_do_rem) )
			{
				#if (USE_ADC_EXTERNO)
					adc_ext_start();
					xSemaphoreTake(sem_adc_ext_proc, portMAX_DELAY);
				#endif

				#if (USE_DAC_INTERNO)
					xSemaphoreTake(sem_dac_int_finish, portMAX_DELAY);
				#endif

				#if (USE_DAC_EXTERNO)
					xSemaphoreTake(sem_dac_ext_finish, portMAX_DELAY);
				#endif

				#if (USE_DAC_INTERNO)
					dac_int_send();
				#endif

				#if (USE_DAC_EXTERNO)
					dac_ext_send();
				#endif
/*
					// Obtengo la fft
				fft_toCmplx((q31_t *)buffer_complex, (q31_t *)buffer_complex);
				fft_toDep((q31_t *)buffer_complex, (q31_t *)buffer_dep);

					// Busco la fundamental a traves del maximo valor
				arm_max_q31((q31_t *)buffer_dep, FFT_SIZE/2, &fft_max, &fft_max_idx);

					// *** THD *** //
				if(flag_do_thd)
				{
						// Armado del numerador de la división, sumará armonicos hasta el fin del vector, el denominador es max_val
					for(i=2; i*fft_max_idx < FFT_SIZE; i++)
					{
						for(j = -FFT_ANCHO_LOBULO; j <= FFT_ANCHO_LOBULO; j++);
						{
							num += buffer_dep[i*fft_max_idx + j];
						}
					}

					arm_sqrt_q31(num, &num);

					// calculo de THD propiamente dicho
					THD = num/fft_max;

					flag_do_thd = false;
				}
					// *** REMANENTE *** //
				else if(flag_do_rem)
				{
						// Busco el piso de ruido a traves del minimo valor
					arm_min_q31((q31_t *)buffer_dep, FFT_SIZE/2, &fft_min, &fft_max_idx);

					// Al espectro obtenido debo quitarle el primer armonico (a la parte real y a la imaginaria
	//				fft_cmplx[fft_max_idx*2] = fft_cmplx[fft_max_idx*2-1] = fft_min;
	//				fft_toReal(fft_cmplx, (q31_t *) dma_adc_ext_memory);
				}
*/

				#if (USE_ADC_EXTERNO)
					adc_ext_post_procesamiento();
				#endif
			}
		}
	}
#endif
