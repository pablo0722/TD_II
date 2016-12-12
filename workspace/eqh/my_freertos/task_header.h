/*
 * task_header.h
 *
 *  Created on: 6 de nov. de 2016
 *      Author: agustin
 */

#ifndef TASK_HEADER_H_
#define TASK_HEADER_H_



#include <header.h>



// ********* FUNCIONES ********** //
	#if (USE_RTOS)
		void queue_init();
		void task_init();
	#endif
// ****************************** //


// ***************** DEFINES ***************** //
//	#if USE_ADC
//		#define ADC_FREQ 				20000										// PROBAR CAMBIANDO A 32000
//		#define ADC_DMA_CANT_MUESTRAS 	8
//		#define ADC_DMA_CHANNEL 		1
//	#endif
//
//	#if USE_DAC
//		#define DAC_FREQ 				ADC_FREQ
//		#define DAC_DMA_CANT_MUESTRAS 	ADC_DMA_CANT_MUESTRAS
//		#define DAC_DMA_CHANNEL 		0
//	#endif

// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if (USE_RTOS)

		// Queue
		extern volatile xQueueHandle Queue_new_data;

		// Semaphore


	#endif


// ********************************************** //


// ************* INICIALIZACION ************* //
		#include "FreeRTOS.h"
		#include "task.h"
		#include "queue.h"
		#include "semphr.h"

		#include "task_func.h"

// ****************************************** //



#endif /* TASK_HEADER_H_ */
