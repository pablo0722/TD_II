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

	#include "cr_dsplib.h"


		// ***** PERIFERICOS ***** //
	//#define USE_UART
	#define USE_ADC
	#define USE_DAC
		// *********************** //

		// ***** FFT ***** //
	#define     LENGTH_SAMPLES             2048					// Tamanio de los vectores de muestras (son complejos, doble tamano)
	#define     FFT_SIZE    	           LENGTH_SAMPLES/2

	extern int16_t spectrum[FFT_SIZE/2];				// Espectro de la senal transformada (solo la mitad, por estar espejado)
	extern int16_t mSignalIn[LENGTH_SAMPLES], mFFTOut[LENGTH_SAMPLES];  	// Senal  de entrada y salida. Son vectores complejos.

	extern uint8_t signalin_flag;
		// *************** //



	#ifdef USE_UART
		/* Transmit and receive ring buffer sizes */
		#define UART_SRB_SIZE LENGTH_SAMPLES	/* Send */
		#define UART_RRB_SIZE 2*50	/* Receive */

		/* Transmit and receive buffers */
		extern static uint8_t *rxbuff, *txbuff;

		/* Transmit and receive ring buffers */
		extern STATIC RINGBUFF_T txring, rxring;
	#endif

		// ***** VARIABLES GLOBALES ***** //
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


	// ***** FUNCIONES ****** //
		void main_init();
		void fft_function();
	// ********************** //


#endif /* HEADER_H_ */
