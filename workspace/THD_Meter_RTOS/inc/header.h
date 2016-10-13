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
	//#define USE_FFT
	//#define USE_UART
	#define USE_ADC_DAC_INTERNO_INTERRUPCION
	//#define USE_ADC_DAC_EXTERNO_INTERRUPCION
	#define USE_ADC_DAC_EXTERNO_DMA
		// *********************** //



	#if defined(USE_ADC_DAC_EXTERNO_INTERRUPCION) && defined(USE_ADC_DAC_EXTERNO_DMA)
		#error USE_ADC_DAC_EXTERNO_POOLING y USE_ADC_DAC_EXTERNO_DMA definidos simultaneamente.
	#endif

	#if defined(USE_ADC_DAC_INTERNO_INTERRUPCION)
		#define USE_ADC_DAC_INTERNO
	#endif

	#if defined(USE_ADC_DAC_EXTERNO_INTERRUPCION) || defined(USE_ADC_DAC_EXTERNO_DMA)
		#define USE_ADC_DAC_EXTERNO
	#endif

	#if defined(USE_ADC_DAC_EXTERNO_DMA)
		#define USE_DMA
	#endif


	#ifdef USE_FFT
		#define     LENGTH_SAMPLES             2048					// Tamanio de los vectores de muestras (son complejos, doble tamanio)
		#define     FFT_SIZE    	           LENGTH_SAMPLES/2

		extern int16_t spectrum[FFT_SIZE/2];				// Espectro de la senal transformada (solo la mitad, por estar espejado)
		extern int16_t mSignalIn[LENGTH_SAMPLES], mFFTOut[LENGTH_SAMPLES];  	// Senal  de entrada y salida. Son vectores complejos.

		extern uint8_t signalin_flag;
	#endif


	#ifdef USE_UART
		/* Transmit and receive ring buffer sizes */
		#define UART_SRB_SIZE LENGTH_SAMPLES	/* Send */
		#define UART_RRB_SIZE 2*50	/* Receive */

		/* Transmit and receive buffers */
		extern static uint8_t *rxbuff, *txbuff;

		/* Transmit and receive ring buffers */
		extern STATIC RINGBUFF_T txring, rxring;
	#endif


	#ifdef USE_ADC_DAC_INTERNO
			// *** ADC *** //
		#define ADC_FREQ 20000
		#define ADC_DMA_CANT_MUESTRAS 1
		#define ADC_DMA_CHANNEL 0

		extern DMA_TransferDescriptor_t DMA_descriptor_ADC;
		extern volatile uint32_t dma_memory_adc[ADC_DMA_CANT_MUESTRAS];

		extern uint8_t canal_adc;

			// *** DAC *** //
		#define DAC_FREQ ADC_FREQ
		#define DAC_DMA_CANT_MUESTRAS ADC_DMA_CANT_MUESTRAS
		#define DAC_DMA_CHANNEL 1

		extern DMA_TransferDescriptor_t DMA_descriptor_DAC;
		extern volatile uint32_t dma_memory_dac[DAC_DMA_CANT_MUESTRAS];

		extern uint8_t canal_dac;
	#endif


	#ifdef USE_ADC_DAC_EXTERNO
		#define	I2S_INT_POLLING		1
		#define I2S_DMA				(!(I2S_INT_POLLING))

		#define LED_stick			0,22
		#define AOUT				0,26

		#define I2SRX_CLK			0,4
		#define I2SRX_WS			0,5
		#define I2SRX_SDA			0,6
		#define RX_MCLK				4,28

		#define I2STX_CLK			0,7
		#define I2STX_WS			0,8
		#define I2STX_SDA			0,9
		#define TX_MCLK				4,29

		#define CH_L				1
		#define CH_R				2

		extern uint16_t adcFlag;
		extern int32_t data, cont, ch;
	#endif


	// ***** FUNCIONES ****** //
		void main_init();

		#ifdef USE_FFT
			void fft_function();
		#endif

		#ifdef USE_UART
			void main_uart();
		#endif

		#ifdef USE_ADC_DAC_INTERNO
			void main_dac();
		#endif
	// ********************** //


#endif /* HEADER_H_ */
