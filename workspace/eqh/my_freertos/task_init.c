/*
 * task_init.c
 *
 *  Created on: 6 de nov. de 2016
 *      Author: agustin
 */


#include "header.h"


#if (USE_RTOS)


	void queue_init()
	{
		// Creo queue
		Queue_new_data = xQueueCreate(4, sizeof(uint8_t));

		// Creo semaphore


	}



	void task_init()
	{
		// Creo tareas
		#if (USE_GPIO)
			// TAREA LED
			xTaskCreate(vTaskLED_alive, (signed char *) "vTaskLED_alive",
						configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
						(xTaskHandle *) NULL);
			#if(USE_BOTONES)
				// TAREA DEBOUNCER
				xTaskCreate(vDEBOUNCETask, (signed char *) "vDEBOUNCETask",
							configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
							(xTaskHandle *) NULL);
			#endif
		#endif
		#if (USE_ADC && USE_DAC)
			// TAREA SIGNAL_PROCESSING
			xTaskCreate(vTaskSIGNAL_PROC, (signed char *) "vTaskSIGNAL_PROC",
						configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
						(xTaskHandle *) NULL);
		#endif

		#if (USE_DISPLAY)
			xTaskCreate(vDisplayTask, (signed char *) "Tarea_Display",
						configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2,
						0);
		#endif


	}


#endif

