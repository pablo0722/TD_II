/*
 * adc_dac_globales.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_ADC
	DMA_TransferDescriptor_t DMA_descriptor_ADC;
	volatile uint32_t dma_memory_adc[ADC_DMA_CANT_MUESTRAS];

	volatile uint8_t canal_adc;
#endif

#if USE_DAC_INTERNO
	DMA_TransferDescriptor_t DMA_descriptor_DAC;
	volatile uint32_t dma_memory_dac[DAC_DMA_CANT_MUESTRAS];

	volatile uint8_t canal_dac;
#endif


#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
	uint16_t adcFlag = 1;
	int32_t data, cont = 0, ch = 0;
#endif
