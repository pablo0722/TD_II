/*
 * adc_dac_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"
#include "private/adc_dac_header_priv.h"


#if USE_ADC_EXTERNO
	STATIC INLINE uint32_t adc_ext_set_data(uint32_t data)
	{
			// Shiftea 8 veces para acomodar los 24 bits adquiridos en la parte baja del uint32_t. asi tengo 8 bits de overflow.
			// 		Nota: Al ser uint32_t, se hace un shifteo logico (completa con ceros).
			// Luego, invierte el bit de signo para convertir de 'signed' (como toma el adc) a unsigned
		return ((data >> 8) ^ 0x00800000);
	}
#endif


#if USE_ADC_EXTERNO
	void adc_ext_pre_procesamiento()
	{
		if(STATUS_ADC_ISPROC(dma_adc_ext_status)) // Si ya recibi del ADC, proceso la senal
		{
				// Acomodar el dato del ADC antes de procesar
			for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
			{
				dma_adc_ext_memory[i] = adc_ext_set_data(dma_adc_ext_memory[i]);
			}

			#if USE_RTOS
				xSemaphoreGive(sem_adc_ext_proc);
			#endif
		}
	}
#endif

