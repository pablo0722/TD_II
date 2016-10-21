/*
 * adc_dac_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_DAC_INTERNO
	void main_dac()
	{
		int sel = CH_L;


		if(adcFlag)
		{
			data = dma_memory_dac[0];
			if(data < 0)
				data = (data >> 8);
			else
			{
				data = data >> 8 ;
				data &= (0x00FFFFFF);
			}

			if(sel == CH_L)
			{
				if(data < 1024)
					data = data + 512;
				else
					data = data - 512;

				Chip_DAC_UpdateValue(LPC_DAC, data);
				adcFlag = 0;
				sel = CH_R;
			}
			else
				sel = CH_L;
		}
	}
#endif
