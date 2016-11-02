/*
 * rtos_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_RTOS
	void task_init()
	{
			// Inicializacion de colas
		//xQueue_in = xQueueCreate(QUEUE_LEN_IN, QUEUE_ITEM_SIZE_IN);
		//xQueue_rem = xQueueCreate(QUEUE_LEN_REM, QUEUE_ITEM_SIZE_REM);
		//xQueue_THD = xQueueCreate(QUEUE_LEN_THD, QUEUE_ITEM_SIZE_THD);

		xTaskCreate(vTask_THD, "vTask_THD", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);
	}
#endif
