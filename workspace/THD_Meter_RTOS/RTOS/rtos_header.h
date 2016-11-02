/*
 * rtos_header.h
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#ifndef RTOS_HEADER_H_
#define RTOS_HEADER_H_



#include "header.h"



// ********* FUNCIONES ********** //
	#if USE_RTOS
		void task_init();
		void vTask_THD( void *pvParameters );
	#endif
// ****************************** //


// ********** TAREAS *********** //
	void vTask_THD( void *pvParameters );
// ***************************** //


// ***************** DEFINES ***************** //
	#if USE_RTOS
			//Colas
		#define QUEUE_LEN_IN	1
		#define QUEUE_LEN_REM	QUEUE_LEN_IN
		#define QUEUE_LEN_THD	1

		#if USE_FFT
			#define QUEUE_ITEM_SIZE_IN	(sizeof(short int)*FFT_SIZE)
		#else
			#define QUEUE_ITEM_SIZE_IN	(sizeof(short int)*512)
		#endif

		#define QUEUE_ITEM_SIZE_REM	QUEUE_ITEM_SIZE_IN
		#define QUEUE_ITEM_SIZE_THD	(sizeof(float))
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_RTOS
		extern xQueueHandle xQueue_in;
		extern xQueueHandle xQueue_rem;
		extern xQueueHandle xQueue_THD;
	#endif
// ********************************************** //



#endif /* RTOS_HEADER_H_ */
