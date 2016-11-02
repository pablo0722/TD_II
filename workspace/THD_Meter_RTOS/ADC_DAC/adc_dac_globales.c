/*
 * adc_dac_globales.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_ADC
	volatile DMA_TransferDescriptor_t DMA_descriptor_ADC_A;		// Descriptor del buffer A del Ping-Pong del ADC
	volatile DMA_TransferDescriptor_t DMA_descriptor_ADC_B;		// Descriptor del buffer B del Ping-Pong del ADC

	volatile uint32_t dma_memory_adc_A[ADC_DMA_CANT_MUESTRAS]	// Buffer A del Ping-Pong del ADC
									   __attribute__ ((section (".data.$RamAHB32")));

	volatile uint32_t dma_memory_adc_B[ADC_DMA_CANT_MUESTRAS]	// Buffer B del Ping-Pong del ADC
									   __attribute__ ((section (".data.$RamAHB32")));

	volatile uint8_t canal_adc;

	volatile uint8_t adc_buffer = BUFFER_A_PINGPONG;
#endif

#if USE_DAC_INTERNO
	DMA_TransferDescriptor_t DMA_descriptor_DAC_A;				// Descriptor del buffer A del Ping-Pong del DAC
	DMA_TransferDescriptor_t DMA_descriptor_DAC_B;				// Descriptor del buffer B del Ping-Pong del DAC

	volatile uint16_t dma_memory_dac_A[DAC_DMA_CANT_MUESTRAS]	// Buffer A del Ping-Pong del DAC
									   __attribute__ ((section (".data.$RamAHB32")));
	volatile uint16_t dma_memory_dac_B[DAC_DMA_CANT_MUESTRAS]	// Buffer B del Ping-Pong del DAC
									   __attribute__ ((section (".data.$RamAHB32")));

	volatile uint8_t canal_dac;

	volatile uint8_t dac_buffer = BUFFER_A_PINGPONG;
#endif


#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
	uint16_t adcFlag = 1;
	int32_t data, cont = 0, ch = 0;
#endif
