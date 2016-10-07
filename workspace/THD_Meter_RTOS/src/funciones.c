/*
 * procesamiento.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


void fft_function()
{
	const uint16_t fft_length = FFT_SIZE*2; // el "*2" es porque el espectro original esta espejado

	arm_cfft_radix2_q31(&fft_inst_q31, mSignalIn);
	arm_cmplx_mag_q31(mSignalIn, mFFTOut, fft_length);
}
