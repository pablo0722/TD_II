/*
 * adc_dac_globales.c
 *
 *  Created on: 7 de nov. de 2016
 *      Author: Pablo
 */


#include "header.h"



#if (USE_ADC_EXTERNO)
	volatile uint32_t *dma_adc_ext_memory = NULL;					// Apunta al buffer actual (el que se puede procesar) del ADC

	#if (USE_RTOS)
		xSemaphoreHandle sem_adc_proc;
	#endif
#endif

#if (USE_DAC_INTERNO)
	Bool dac_send = FALSE;
#endif
