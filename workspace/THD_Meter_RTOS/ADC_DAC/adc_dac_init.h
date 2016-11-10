/*
 * adc_dac_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"
#include "adc_dac_init_priv.h"


STATIC INLINE void adc_dac_init()
{
	#if USE_DAC_INTERNO
		dac_init();
	#endif

	#if (USE_ADC_EXTERNO) || (USE_DAC_EXTERNO)
		i2s_init();
	#endif
}
