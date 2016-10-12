/*
 * header.h
 *
 *  Created on: 18 de ago. de 2016
 *      Author: pablo
 */


#ifndef HEADER_H_
#define HEADER_H_


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


// ***** PERIFERICOS ***** //
	#define USE_UART
	//#define USE_ADC
	//#define USE_DAC
// *********************** //


// ***** UTILIDADES ***** //
	#define USE_FFT
// ********************** //


// ***** FUNCIONES ****** //
	void main_init();

	#ifdef USE_FFT
		void fft_function();
	#endif
// ********************** //


// ***** VARIABLES GLOBALES ***** //
	#ifdef USE_FFT

		#define     LENGTH_SAMPLES             2048					// Tamanio de los vectores de muestras (son complejos, doble tamanio por real+imaginario)
		#define     FFT_SIZE    	           LENGTH_SAMPLES/4		// Tamanio del vector del modulo de la FFT (Es un cuarto (1/4) del tamanio original por ser solo el modulo y por estar espejado)

		extern arm_cfft_radix2_instance_q31 fft_inst_q31;			// Estructura para aplicar FFT

		extern q31_t spectrum[FFT_SIZE];							// Espectro de la senal transformada
		extern q31_t mSignalIn[LENGTH_SAMPLES];						// Senal  de entrada. Es vector complejo.
		extern q31_t mFFTOut[LENGTH_SAMPLES];  						// Senal  de salida. Es vector complejo.

		extern uint8_t signalin_flag;
	#endif


	#ifdef USE_UART
		#define LPC_UARTN 			LPC_UART0				// Numero de UART a utilizar
		#define UARTN_IRQn 			UART0_IRQn				// Numero de UART a utilizar
		#define UARTN_IRQHandler 	UART0_IRQHandler		// Numero de UART a utilizar

		#define UART_BAUDRATE 		9600					// Baud rate de la UART

			// Transmit and receive ring buffer sizes
		#define UART_SRB_SIZE 	LENGTH_SAMPLES	// Send
		#define UART_RRB_SIZE 	LENGTH_SAMPLES	// Receive

			// Transmit and receive buffers
		extern uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

			// Transmit and receive ring buffers
		extern RINGBUFF_T txring, rxring;
	#endif


	#ifdef USE_ADC
		#define ADC_FREQ 20000
		#define ADC_DMA_CANT_MUESTRAS 1
		#define ADC_DMA_CHANNEL 0

		//extern DMA_TransferDescriptor_t DMA_descriptor_ADC;
		extern volatile uint32_t dma_memory_adc[ADC_DMA_CANT_MUESTRAS];
	#endif


	#ifdef USE_DAC
		#define DAC_FREQ ADC_FREQ
		#define DAC_DMA_CANT_MUESTRAS ADC_DMA_CANT_MUESTRAS
		#define DAC_DMA_CHANNEL 1

		//extern DMA_TransferDescriptor_t DMA_descriptor_DAC;
		extern volatile uint16_t dma_memory_dac[DAC_DMA_CANT_MUESTRAS];
	#endif
// ****************************** //


#endif /* HEADER_H_ */
