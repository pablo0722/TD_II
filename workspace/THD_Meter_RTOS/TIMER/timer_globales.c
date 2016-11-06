/*
 * timer_globales.c
 *
 *  Created on: 5 de nov. de 2016
 *      Author: Pablo
 */


#include "header.h"


#if USE_TIMER
	#if USE_RTOS
		xSemaphoreHandle sem_timer0_match1;
		xSemaphoreHandle sem_timer1_match0;
		xSemaphoreHandle sem_timer1_match1;
	#endif
#endif
