/*
 * eqh.h
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */

#ifndef HEADER_H_
#define HEADER_H_


	#include "config.h"
	#include "fft_header.h"
//	#include "uart_header.h"
	#include "adc_dac_header.h"
	#include "gpio_header.h"
	#include "task_header.h"
	#include "display_header.h"
	#include "efectos_header.h"


// ********* FUNCIONES ********** //
	void main_while();
// ****************************** //

	// *** MEMORIA *** //
	//  MFlash512 (rx) : 	ORIGIN = 0x0, 			/* 0 byte */		LENGTH = 0x80000 	/* 512K bytes */
	//  RamLoc64 (rwx) : 	ORIGIN = 0x10000000 	/* 256M byte */,	LENGTH = 0x10000 	/* 64K bytes */
	//  RamPeriph32 (rwx) : ORIGIN = 0x20000000		/* 512M byte */, 	LENGTH = 0x8000 	/* 32K bytes */
	//  RamExt32M (rwx) : 	ORIGIN = 0xA0000000		/* 2.5G byte */, 	LENGTH = 0x2000000 	/* 32M bytes */
	// *************** //

#endif /* HEADER_H_ */


