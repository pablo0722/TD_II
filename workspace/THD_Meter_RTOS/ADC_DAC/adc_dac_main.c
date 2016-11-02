/*
 * adc_dac_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"


uint32_t set_data (uint32_t data)
{
	if(data < 0)
		data = (data >> 8);
	else
	{
		data = data >> 8 ;
//		data &= (0x00FFFFFF);
	}

	if(data < 16777216)		// 2^24
		data = data + 8388608;
	else
		data = data - 8388608;

	data &= (0x00FFFFFF);

	return (data >> 8);
}

/*
#if USE_DAC_INTERNO
	void main_dac()
	{
		#if (DEBUG_MODE)
		#endif
	}
#endif
*/
