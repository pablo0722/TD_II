/*
 * header.h
 *
 *  Created on: 18 de ago. de 2016
 *      Author: pablo
 */


#ifndef HEADER_H_
#define HEADER_H_

	#include "utilidades.h"
	#include "fft_header.h"
	#include "uart_header.h"
	#include "adc_dac_header.h"


// *** MEMORIA *** //
//  MFlash512 (rx) : 	ORIGIN = 0x0, 			/* 256M byte */		LENGTH = 0x80000 	/* 512K bytes */
//  RamLoc64 (rwx) : 	ORIGIN = 0x10000000 	/* 256M byte */,	LENGTH = 0x10000 	/* 64K bytes */
//  RamPeriph32 (rwx) : ORIGIN = 0x20000000		/* 512M byte */, 	LENGTH = 0x8000 	/* 32K bytes */
//  RamExt32M (rwx) : 	ORIGIN = 0xA0000000		/* 256M byte */, 	LENGTH = 0x2000000 	/* 32M bytes */
// *************** //

// ********* FUNCIONES ********** //
	void main_while();
// ****************************** //




// Corroboracion de errores //
	#if (USE_ADC_EXTERNO_INTERRUPCION) && (USE_ADC_EXTERNO_DMA)
		#error defines incompatibles activados simultaneamente: "USE_ADC_EXTERNO_INTERRUPCION" y "USE_ADC_EXTERNO_DMA"
	#endif

	#if (USE_DAC_EXTERNO_INTERRUPCION) && (USE_DAC_EXTERNO_DMA)
		#error defines incompatibles activados simultaneamente: "USE_DAC_EXTERNO_INTERRUPCION" y "USE_DAC_EXTERNO_DMA"
	#endif
// ************************ //

#endif /* HEADER_H_ */
