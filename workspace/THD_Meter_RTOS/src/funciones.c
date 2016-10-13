/*
 * procesamiento.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"

#ifdef USE_FFT
	void fft_function()
	{
		int16_t i;
		int16_t real,imaginaria;
		// Segun la cantidad de muestras de la fft (definidas en FFT_SIZE) se llama a la funcion correspondiente
		#if FFT_SIZE == 64
			vF_dspl_fftR4b16N64(mFFTOut, mSignalIn);
		#elif FFT_SIZE == 256
			vF_dspl_fftR4b16N256(mFFTOut, mSignalIn);
		#elif FFT_SIZE == 1024
			vF_dspl_fftR4b16N1024(mFFTOut, mSignalIn);
		#elif FFT_SIZE == 4096
			vF_dspl_fftR4b16N4096(mFFTOut, mSignalIn);
		#else
		#endif

		// Se arma el espectro en frecuencia, a partir del modulo de la transformada
		// Se toman solamente la primer mitad de los puntos, ya que el espectro esta espejado
		for(i = 0; i < FFT_SIZE/2; i++)
		{
			// Se toman la parte real e imaginaria de cada punto
			real 		= mFFTOut[ i*2 ];
			imaginaria 	= mFFTOut[ i*2 + 1];

			// Se calcula cada punto del espectro obteniendo el modulo
			spectrum[i] = (int16_t) sqrt( (real * real) + ( imaginaria * imaginaria) );
		}
	}
#endif


#ifdef USE_UART
	void main_uart()
	{
		if (signalin_flag == 1)
		{
			// Wrap value back around
			Chip_UART_SendRB(LPC_UART0, &txring, (const uint8_t *) &key, 1);
		}
	}
#endif


#ifdef USE_ADC_DAC_INTERNO
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
