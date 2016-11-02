/*
 * tareas.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */

#include "header.h"


#if USE_RTOS
/***************************************************/
/*****************Procesamiento*********************/
/***************************************************/

	void vTask_THD( void *pvParameters )
	{
		q31_t numcuad = 0; 	// Es la suma cuadratica de los armonicos de la DEP (numerador del THD al cuadrado)
		q31_t num;			// Es la raiz cuadrada de la suma cuadratica de los armonicos de la DEP (numerador del THD)
		uint32_t i;

		if(xQueueReceive(xQueue_in, fft_in, 0) == pdTRUE)
		{
			/*obtengo la fft*/
			fft_function();

			/*armado del numerador de la división, sumará armonicos hasta el fin del vector, el denominador es max_val*/
			for(i=2; i*fft_max_index < FFT_SIZE; i++)
			{
				numcuad += fft_out_dep[i*fft_max_index];
				i++;
			}

			arm_sqrt_q31(numcuad, &num);

			/* calculo de THD propiamente dicho */
			THD = num/fft_max_val;
			//signalin_flag = 0;

			xQueueSend(xQueue_rem, fft_out_dep, 0);
		}
	}

	void vTask_Remanente( void *pvParameters )
	{
//		q31_t min;
//		uint32_t min_index;
//		short int buf_rem[QUEUE_LEN_IN];
//		uint32_t i=2;
//
//		if(xQueueReceive(xQueue_in, mSignalIn, 0) == pdTRUE)
//		{
//			/*al espectro obtenido debo quitarle el primer armonico*/
//			arm_min_q31((q31_t *) fft_vector_out, FFT_SIZE, (q31_t *) min, (q31_t *) min_index);
//			fft_complete[max_index]=min;
//			remanente = ifft_function(*fft_complete);
//			xQueueSend(xQueue_rem, spectrum, 0);
//		}
	}
#endif
