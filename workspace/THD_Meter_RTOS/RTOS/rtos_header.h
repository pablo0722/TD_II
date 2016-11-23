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
	#endif
// ****************************** //

// ********* PRIORIDADES ********** //
	#if USE_RTOS
		#define PRIORIDAD_MAXIMA	4
		#define PRIORIDAD_MINIMA	0
	#endif
// ******************************** //

// ********** TAREAS *********** //
	#if USE_RTOS
		void vTask_nvic_init(void *pvParameters);	// Inicializa las interupciones
		void vtask_ImAlive(void * pvParameters);	// Led testigo

		#if (USE_UART)
			void vtask_uart(void * pvParameters);
		#endif
	#endif
// ***************************** //


// ***************** DEFINES ***************** //
	#if USE_RTOS
		#define ENTRADA 	0
		#define SALIDA 		1
	#endif
// ******************************************* //

// ********* INICIALIZACIONES ********** //
	#if USE_RTOS
		#include "rtos_init.h"
	#endif
// ************************************* //


#endif /* RTOS_HEADER_H_ */
