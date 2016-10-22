/*
 * utilidades.h
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */

#ifndef UTILIDADES_H_
#define UTILIDADES_H_


	#include "FreeRTOS.h"
	#include "task.h"
	#include "board.h"
	#include "chip.h"
	#include "semphr.h"
	#include "queue.h"

	#include <string.h>	// Funcion memset
	#include <math.h>	// Funcion sqrt

		// CMSIS
	#include "arm_math.h"


	#ifndef ON
		#define ON	1
	#endif
	#ifndef OFF
		#define OFF	0
	#endif


// ***** PERIFERICOS (init) ***** //
	#define USE_UART	ON
	#define USE_ADC		OFF
	#define USE_DAC		OFF
	#define USE_FFT		ON
	#define USE_RTOS	OFF
// ****************************** //


// ***** UTILIDADES (main while) ***** //
	#define DEBUG_MODE			OFF

	#if (USE_UART)
			// Numero de UART a utilizar
		#define USE_UART0 		ON
		#define USE_UART1 		OFF
		#define USE_UART2 		OFF
		#define USE_UART3 		OFF


			// Funcion de la UART
			#define UART_TRANSMIT_NONE		0		// no transmite nada
			#define UART_TRANSMIT_LOOPBACK	1		// transmite lo mismo que recibio
			#define UART_TRANSMIT_FFT		2		// transmite la FFT
		#define UART0_TRANSMIT	UART_TRANSMIT_FFT
		#define UART1_TRANSMIT	UART_TRANSMIT_FFT
		#define UART2_TRANSMIT	UART_TRANSMIT_FFT
		#define UART3_TRANSMIT	UART_TRANSMIT_FFT
	#endif

	#if (USE_ADC)
		#define USE_ADC_INTERNO_INTERRUPCION	ON
		#define USE_ADC_EXTERNO_INTERRUPCION	OFF
		#define USE_ADC_EXTERNO_DMA				ON
	#endif

	#if (USE_DAC)
		#define USE_DAC_INTERNO_INTERRUPCION	ON
		#define USE_DAC_EXTERNO_INTERRUPCION	OFF
		#define USE_DAC_EXTERNO_DMA				ON
	#endif
// *********************************** //


// ******** Utilidades implicitas ******** //
	#if (USE_ADC)
		#define USE_ADC_INTERNO		USE_ADC_INTERNO_INTERRUPCION
		#define USE_ADC_EXTERNO		((USE_ADC_EXTERNO_INTERRUPCION)+(USE_ADC_EXTERNO_DMA))
	#endif

	#if (USE_DAC)
		#define USE_DAC_INTERNO		USE_DAC_INTERNO_INTERRUPCION
		#define USE_DAC_EXTERNO		((USE_DAC_EXTERNO_INTERRUPCION)+(USE_DAC_EXTERNO_DMA))
	#endif


	#if (USE_ADC)||(USE_DAC)
		#define USE_DMA				((USE_ADC_EXTERNO_DMA)+(USE_DAC_EXTERNO_DMA))
	#endif
// *************************************** //


// ***** FUNCIONES ****** //
	void main_init();
// ********************** //


#endif /* UTILIDADES_H_ */
