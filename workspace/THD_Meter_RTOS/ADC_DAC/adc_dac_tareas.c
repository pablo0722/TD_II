/*
 * adc_dac_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"


#if USE_ADC_EXTERNO
	void main_adc_task_pre()
	{
		xSemaphoreTake(sem_adc_pre, 0);

		while(1)
		{
			xSemaphoreTake(sem_adc_pre, 0);

			main_adc_pre();

			xSemaphoreGive(sem_adc_proc);
		}
	}


	void main_adc_task_post()
	{
		xSemaphoreTake(sem_adc_post, 0);

		while(1)
		{
			xSemaphoreTake(sem_adc_post, 0);

			main_adc_post();
		}
	}
#endif

