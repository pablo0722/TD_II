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
			// *** Tareas
		xTaskCreate(	vtask_ImAlive, 	"vtask_ImAlive", 	configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
		xTaskCreate(	vTask_THD, 		"vTask_THD", 		configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
		#if (USE_UART)
			xTaskCreate(vtask_uart, 	"vtask_uart", 		configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
		#endif

			// *** Inicia scheduler
		vTaskStartScheduler();
	}
#endif
