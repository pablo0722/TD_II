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
	#define USE_UART	OFF
	#define USE_ADC		ON
	#define USE_DAC		ON
	#define USE_FFT		OFF
	#define USE_RTOS	OFF
// ****************************** //


// ***** UTILIDADES (main while) ***** //
	#define DEBUG_MODE			ON

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
		//Usar ADC interno y/o externo (externo por I2S)
		#define USE_ADC_INTERNO		OFF
		#define USE_ADC_EXTERNO		ON

		#if (USE_ADC_INTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define ADC_INTERNO_INTERRUPCION	0
				#define ADC_INTERNO_DMA				1
			#define ADC_INTERNO_MODO	ADC_INTERNO_INTERRUPCION
		#endif
		#if (USE_ADC_EXTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define ADC_EXTERNO_INTERRUPCION	0
				#define ADC_EXTERNO_DMA				1
			#define ADC_EXTERNO_MODO	ADC_EXTERNO_DMA
		#endif
	#endif

	#if (USE_DAC)
		//Usar DAC interno y/o externo (externo por I2S)
		#define USE_DAC_INTERNO		ON
		#define USE_DAC_EXTERNO		OFF

		#if (USE_DAC_INTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define DAC_INTERNO_INTERRUPCION	0
				#define DAC_INTERNO_DMA				1
			#define DAC_INTERNO_MODO	DAC_INTERNO_INTERRUPCION
		#endif
		#if (USE_DAC_EXTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define DAC_EXTERNO_INTERRUPCION	0
				#define DAC_EXTERNO_DMA				1
			#define DAC_EXTERNO_MODO	DAC_EXTERNO_DMA
		#endif
	#endif
// *********************************** //


// ******** Utilidades implicitas ******** //
	#if ( (defined(ADC_INTERNO_MODO) && ADC_INTERNO_MODO == ADC_INTERNO_DMA) || \
		  (defined(ADC_EXTERNO_MODO) && ADC_EXTERNO_MODO == ADC_EXTERNO_DMA) || \
		  (defined(DAC_INTERNO_MODO) && DAC_INTERNO_MODO == DAC_INTERNO_DMA) || \
		  (defined(DAC_EXTERNO_MODO) && DAC_EXTERNO_MODO == DAC_EXTERNO_DMA) )
		#define USE_DMA				ON
	#else
		#define USE_DMA				OFF
	#endif
// *************************************** //


// ***** FUNCIONES ****** //
	void main_init();
// ********************** //


#endif /* UTILIDADES_H_ */
