/*
 * globales.c
 *
 *  Created on: 7 de nov. de 2016
 *      Author: Pablo
 */


#include "header.h"


#if USE_RTOS
	Bool flag_do_thd = FALSE;	// Calcula THD
	Bool flag_do_rem = FALSE;	// Calcula senal remanente
#endif