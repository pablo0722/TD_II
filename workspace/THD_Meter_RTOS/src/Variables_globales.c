/*
 * Variables_globales.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


// ************* FFT ************* //
int16_t spectrum[FFT_SIZE/2];		// Espectro de la senal transformada (solo la mitad, por estar espejado)
int16_t mSignalIn[LENGTH_SAMPLES], mFFTOut[LENGTH_SAMPLES];     	// Senal  de entrada y salida. Son vectores complejos.

uint8_t signalin_flag = 0;
// ****************************** //

#ifdef USE_UART
	/* Transmit and receive buffers */
	static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

	/* Transmit and receive ring buffers */
	STATIC RINGBUFF_T txring, rxring;
#endif

#ifdef USE_ADC
	//DMA_TransferDescriptor_t DMA_descriptor_ADC;
	volatile uint32_t dma_memory_adc[ADC_DMA_CANT_MUESTRAS];
#endif


#ifdef USE_DAC
	//DMA_TransferDescriptor_t DMA_descriptor_DAC;
	volatile uint16_t dma_memory_dac[DAC_DMA_CANT_MUESTRAS];
#endif
