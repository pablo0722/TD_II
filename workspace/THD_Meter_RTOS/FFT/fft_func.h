/*
 * fft_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_FFT
	STATIC INLINE void fft_toCmplx(q31_t fft_in_real[FFT_SIZE], q31_t fft_out_cmplx[FFT_SIZE*2])
	{
		arm_rfft_q31(&fft_inst_q31, fft_in_real, fft_out_cmplx);
	}

	STATIC INLINE void fft_toDep(q31_t fft_in_cmplx[FFT_SIZE*2], q31_t fft_out_dep[FFT_SIZE/2])
	{
		q31_t aux_fft_out_dep[FFT_SIZE];

		arm_cmplx_mag_q31(fft_in_cmplx, aux_fft_out_dep, FFT_SIZE*2);

		memcpy(fft_out_dep, aux_fft_out_dep, FFT_SIZE/2);

		// Elevo al cuadrado para obtener la densidad espectral de potencia
		arm_mult_q31(
				  (q31_t *) fft_out_dep,
				  (q31_t *) fft_out_dep,
				  (q31_t *) fft_out_dep,
				  FFT_SIZE);
	}

	STATIC INLINE void fft_toReal(q31_t fft_in_cmplx[FFT_SIZE], q31_t fft_out_real[FFT_SIZE])
	{
		arm_rfft_q31(&ifft_inst_q31, fft_in_cmplx, fft_out_real);
	}
#endif
