/*
 * tareas.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */

#include "header.h"


#if USE_RTOS
	void vTask_THD( void *pvParameters )
	{
		short int buf_rem[QUEUE_LEN_IN];

		if(xQueueReceive(xQueue_in, mSignalIn, 0) == pdTRUE)
		{
			//fft_function();

			//signalin_flag = 0;

			xQueueSend(xQueue_rem, spectrum, 0);
		}
	}
#endif
