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
