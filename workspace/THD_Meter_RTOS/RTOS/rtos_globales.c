/*
 * rtos_globales.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_RTOS
	xQueueHandle xQueue_in;
	xQueueHandle xQueue_rem;
	xQueueHandle xQueue_THD;
#endif
