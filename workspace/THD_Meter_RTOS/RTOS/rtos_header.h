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
	#endif
// ****************************** //


// ********** TAREAS *********** //
	#if USE_RTOS
		void vtask_ImAlive(void * pvParameters);	// led testigo

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


// ************* VARIABLES GLOBALES ************* //
	#if USE_RTOS
		extern Bool flag_use_dac;	// Hace loopback por DAC
		extern Bool flag_do_thd;	// Calcula THD
		extern Bool flag_do_rem;	// Calcula senal remanente
	#endif
// ********************************************** //



#endif /* RTOS_HEADER_H_ */
