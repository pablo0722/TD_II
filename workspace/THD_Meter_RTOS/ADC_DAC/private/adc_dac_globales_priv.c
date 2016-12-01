/*
 * adc_dac_globales.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"
#include "private/adc_dac_header_priv.h"



#if (USE_ADC_EXTERNO)
	DMA_TransferDescriptor_t *	dma_adc_ext_descriptor 	// Apunta al descriptor del buffer actual (el que se puede procesar) del Ping-Pong del ADC
													__attribute__ ((section (".bss.$RamAHB32"))) = NULL;

	DMA_TransferDescriptor_t 	dma_adc_ext_descriptor_A	// Descriptor del buffer A del Ping-Pong del ADC
													__attribute__ ((section (".bss.$RamAHB32")));

	DMA_TransferDescriptor_t 	dma_adc_ext_descriptor_B	// Descriptor del buffer B del Ping-Pong del ADC
													__attribute__ ((section (".bss.$RamAHB32")));

	volatile uint32_t *			dma_adc_ext_memory_A		// Buffer A del Ping-Pong del ADC
													__attribute__ ((section (".bss.$RamAHB32"))) = NULL;

	volatile uint32_t *			dma_adc_ext_memory_B		// Buffer B del Ping-Pong del ADC
													__attribute__ ((section (".bss.$RamAHB32"))) = NULL;

	uint8_t 					dma_adc_ext_canal			// Canal del ADC en el DMA
													__attribute__ ((section (".bss.$RamAHB32"))) = 0;

	volatile int8_t 			dma_adc_ext_status			// Estado del ADC en la maquina de estados propia
													__attribute__ ((section (".data.$RamAHB32"))) = STATUS_ADC_IDLE;
#endif

#if (USE_DAC_EXTERNO)
	DMA_TransferDescriptor_t 	dma_dac_ext_descriptor	// Descriptor del buffer A del Ping-Pong del DAC
													__attribute__ ((section (".bss.$RamAHB32")));

	volatile uint16_t *			dma_dac_ext_memory		// Buffer A del Ping-Pong del DAC
													__attribute__ ((section (".bss.$RamAHB32"))) = NULL;

	uint8_t 					dma_dac_ext_canal		// Canal del DAC en el DMA
													__attribute__ ((section (".bss.$RamAHB32"))) = 0;
#endif

#if (USE_DAC_INTERNO)
	DMA_TransferDescriptor_t 	dma_dac_int_descriptor	// Descriptor del buffer A del Ping-Pong del DAC
													__attribute__ ((section (".bss.$RamAHB32")));

	volatile uint16_t *			dma_dac_int_memory		// Buffer A del Ping-Pong del DAC
													__attribute__ ((section (".bss.$RamAHB32"))) = NULL;

	uint8_t 					dma_dac_int_canal		// Canal del DAC en el DMA
													__attribute__ ((section (".bss.$RamAHB32"))) = 0;
#endif
