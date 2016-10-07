/*
 * Variables_globales.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


#ifdef USE_FFT
	arm_cfft_radix2_instance_q31 fft_inst_q31;

	q31_t spectrum[FFT_SIZE];			// Espectro de la senal transformada
	q31_t mSignalIn[LENGTH_SAMPLES];	// Senal  de entrada. Es vector complejo.
	q31_t mFFTOut[LENGTH_SAMPLES]; 	// Senal  de salida. Es vector complejo.

	uint8_t signalin_flag = 0;
#endif


#ifdef USE_UART
	/* Transmit and receive buffers */
	uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

	/* Transmit and receive ring buffers */
	RINGBUFF_T txring, rxring;
#endif


#ifdef USE_ADC
	//DMA_TransferDescriptor_t DMA_descriptor_ADC;
	volatile uint32_t dma_memory_adc[ADC_DMA_CANT_MUESTRAS];
#endif


#ifdef USE_DAC
	//DMA_TransferDescriptor_t DMA_descriptor_DAC;
	volatile uint16_t dma_memory_dac[DAC_DMA_CANT_MUESTRAS];
#endif
