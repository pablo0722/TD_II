/*
 * config.h
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */


#ifndef CONFIG_H_
#define CONFIG_H_


	#include "FreeRTOS.h"
	#include "task.h"
	#include "board.h"
	#include "chip.h"
	#include "semphr.h"
	#include "queue.h"

	// CMSIS DSP lib
	#include "arm_math.h"

//	#include <string.h>	// Funcion memset
//	#include <math.h>	// Funcion sqrt
//
//	#include "stdio.h"

		// CMSIS
//	#include "arm_math.h"


	#ifndef ON
		#define ON	1
	#endif
	#ifndef OFF
		#define OFF	0
	#endif


// ***** PERIFERICOS (init) ***** //
//	#define USE_UART		OFF
	#define	USE_GPIO		ON
	#define USE_ADC			ON
	#define USE_DAC			ON
	#define USE_DISPLAY		ON
	#define USE_FFT			ON
	#define USE_RTOS		ON
	#define USE_EFECTOS		ON
// ****************************** //


// ***** UTILIDADES (main while) ***** //
	#define DEBUG_MODE			ON

//	#if (USE_UART)
//			// Numero de UART a utilizar
//		#define USE_UART0 		ON
//		#define USE_UART1 		OFF
//		#define USE_UART2 		OFF
//		#define USE_UART3 		OFF
//
//
//			// Funcion de la UART
//			#define UART_TRANSMIT_NONE		0		// no transmite nada
//			#define UART_TRANSMIT_LOOPBACK	1		// transmite lo mismo que recibio
//			#define UART_TRANSMIT_FFT		2		// transmite la FFT
//		#define UART0_TRANSMIT	UART_TRANSMIT_FFT
//		#define UART1_TRANSMIT	UART_TRANSMIT_FFT
//		#define UART2_TRANSMIT	UART_TRANSMIT_FFT
//		#define UART3_TRANSMIT	UART_TRANSMIT_FFT
//	#endif

	#if (USE_ADC)
		//Usar ADC interno y/o externo (externo por I2S)
		#define USE_ADC_INTERNO		OFF
		#define USE_ADC_EXTERNO		ON

		#if (USE_ADC_INTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define ADC_INTERNO_INTERRUPCION	ON
				#define ADC_INTERNO_DMA				OFF
			#define ADC_INTERNO_MODO	ADC_INTERNO_INTERRUPCION
		#endif
		#if (USE_ADC_EXTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define ADC_EXTERNO_INTERRUPCION	OFF
				#define ADC_EXTERNO_DMA				ON
			#define ADC_EXTERNO_MODO	ADC_EXTERNO_DMA
		#endif
	#endif

	#if (USE_DAC)
		//Usar DAC interno y/o externo (externo por I2S)
		#define USE_DAC_INTERNO		OFF
		#define USE_DAC_EXTERNO		ON

		#if (USE_DAC_INTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define DAC_INTERNO_INTERRUPCION	ON
				#define DAC_INTERNO_DMA				OFF
			#define DAC_INTERNO_MODO	DAC_INTERNO_INTERRUPCION
		#endif
		#if (USE_DAC_EXTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define DAC_EXTERNO_INTERRUPCION	ON
				#define DAC_EXTERNO_DMA				OFF
			#define DAC_EXTERNO_MODO	DAC_EXTERNO_DMA
		#endif
	#endif

	#if (USE_GPIO)
		#define USE_BOTONES		ON
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

	#if (USE_DMA)
		#define USE_BUFFER_SERIE		ON
		#define USE_BUFFER_PARALELO		OFF
	#endif
// *************************************** //



// ***** FUNCIONES ****** //
	void main_init();
// ********************** //


#endif /* CONFIG_H_ */
