/*
 * rtos_header.h
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#ifndef TIMER_HEADER_H_
#define TIMER_HEADER_H_



#include "header.h"



// ********* FUNCIONES ********** //
	#if USE_TIMER
	#endif
// ****************************** //


// ********** TAREAS *********** //
	#if USE_TIMER
	#endif
// ***************************** //


// ***************** DEFINES ***************** //
	#if USE_TIMER
		#define TIMER0_TICKRATE 	50		// 50 ticks per second
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_TIMER
		#if USE_RTOS
			extern xSemaphoreHandle sem_timer0_match1;
			extern xSemaphoreHandle sem_timer1_match0;
			extern xSemaphoreHandle sem_timer1_match1;
		#endif
	#endif
// ********************************************** //



#endif /* TIMER_HEADER_H_ */
