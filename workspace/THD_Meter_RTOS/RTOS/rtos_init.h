/*
 * rtos_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_RTOS
	static inline void task_create( TaskFunction_t pxTaskCode, const char * const pcName, const uint16_t usStackDepth,
								void * const pvParameters, UBaseType_t uxPriority, TaskHandle_t * const pxCreatedTask)
	{
		#if DEBUG_MODE
			BaseType_t ret_task =
		#endif

		xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask);

		#if DEBUG_MODE
			if(ret_task < 0)
			{
				printf("[error] tarea %s \n", pcName);
				printf("\t no hay memoria suficiente");
			}
		#endif
	}


	static inline void task_init()
	{
			// *** Tareas
		task_create(	vTask_nvic_init, "vTask_nvic_init", configMINIMAL_STACK_SIZE, NULL, PRIORIDAD_MAXIMA+1, (xTaskHandle *) NULL);
		task_create(	vtask_ImAlive, 	 "vtask_ImAlive", 	configMINIMAL_STACK_SIZE, NULL, PRIORIDAD_MINIMA, 	(xTaskHandle *) NULL);
		#if (USE_UART)
			task_create(vtask_uart, 	 "vtask_uart", 		configMINIMAL_STACK_SIZE, NULL, PRIORIDAD_MINIMA, 	(xTaskHandle *) NULL);
		#endif

			// *** Inicia scheduler
		vTaskStartScheduler();
	}
#endif
