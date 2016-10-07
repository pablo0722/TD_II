/*
 * procesamiento.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


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
