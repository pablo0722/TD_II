/*
 * adc_dac_globales.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_ADC_EXTERNO
	volatile DMA_TransferDescriptor_t dma_adc_ext_descriptor_A;		// Descriptor del buffer A del Ping-Pong del ADC
	volatile DMA_TransferDescriptor_t dma_adc_ext_descriptor_B;		// Descriptor del buffer B del Ping-Pong del ADC

	volatile uint32_t dma_adc_ext_memory_A[ADC_DMA_CANT_MUESTRAS]	// Buffer A del Ping-Pong del ADC
									   __attribute__ ((section (".bss.$RamAHB32")));

	volatile uint32_t dma_adc_ext_memory_B[ADC_DMA_CANT_MUESTRAS]	// Buffer B del Ping-Pong del ADC
									   __attribute__ ((section (".bss.$RamAHB32")));

	volatile uint8_t dma_adc_ext_canal;

	volatile uint8_t dma_dac_int_status = PINGPONG_IDLE;
#endif

#if USE_DAC_INTERNO
	DMA_TransferDescriptor_t dma_dac_int_descriptor_A;				// Descriptor del buffer A del Ping-Pong del DAC
	DMA_TransferDescriptor_t dma_dac_int_descriptor_B;				// Descriptor del buffer B del Ping-Pong del DAC

	volatile uint16_t dma_dac_int_memory_A[DAC_DMA_CANT_MUESTRAS]	// Buffer A del Ping-Pong del DAC
									   __attribute__ ((section (".bss.$RamAHB32")));
	volatile uint16_t dma_dac_int_memory_B[DAC_DMA_CANT_MUESTRAS]	// Buffer B del Ping-Pong del DAC
									   __attribute__ ((section (".bss.$RamAHB32")));

	volatile uint8_t dma_dac_int_canal;

	volatile uint8_t dma_dac_int_status = PINGPONG_IDLE;
#endif


#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
	uint16_t adcFlag = 1;
	int32_t data, cont = 0, ch = 0;
#endif
