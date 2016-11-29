/*
 * adc_dac_globales.c
 *
 *  Created on: 7 de nov. de 2016
 *      Author: Pablo
 */


#include "header.h"



#if (USE_ADC_EXTERNO)
	volatile uint32_t *		dma_adc_ext_memory			// Apunta al buffer actual (el que se puede procesar) del ADC
												__attribute__ ((section (".bss.$RamAHB32"))) = NULL;

	#if (USE_RTOS)
		xSemaphoreHandle 	sem_adc_ext_proc				// Semaforo que indica cuando recibe un dato por adc y debe ser procesado.
												__attribute__ ((section (".bss.$RamAHB32")));
	#endif
#endif

#if (USE_DAC_EXTERNO)
	#if (USE_RTOS)
		xSemaphoreHandle 	sem_dac_ext_finish				// Semaforo que indica cuando se termino de enviar un dato por DAC
												__attribute__ ((section (".bss.$RamAHB32")));
	#endif
#endif

#if (USE_DAC_INTERNO)
	#if (USE_RTOS)
		xSemaphoreHandle 	sem_dac_int_finish				// Semaforo que indica cuando se termino de enviar un dato por DAC
												__attribute__ ((section (".bss.$RamAHB32")));
	#endif
#endif
