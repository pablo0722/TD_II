/*
 * fft_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_FFT
	void fft_function()
	{
		if(fft_status == FFT_STATUS_TO_DO)
		{
			arm_rfft_q31(&fft_inst_q31, (q31_t *)fft_in, (q31_t *)fft_out_cmplx);
			arm_cmplx_mag_q31((q31_t *)fft_out_cmplx, (q31_t *)fft_out_dep, FFT_SIZE*2);

			/*la elevo al cuadrado para obtener la densidad espectral de potencia*/
			arm_mult_q31(
					  (q31_t *) fft_out_dep,
					  (q31_t *) fft_out_dep,
					  (q31_t *) fft_out_dep,
					  FFT_SIZE);

			/*busco la fundamental a traves del maximo valor*/
			arm_max_q31	(	(q31_t *) fft_out_dep,
							FFT_SIZE,
							(q31_t *) fft_max_val,
							(uint32_t *) fft_max_index
						);

			fft_status = FFT_STATUS_DONE;
		}
	}

	void ifft_function()
	{
		if(ifft_status == IFFT_STATUS_TO_DO)
		{
			arm_rfft_q31(&ifft_inst_q31, (q31_t *)fft_out_cmplx, (q31_t *)fft_out_rem);

			ifft_status = IFFT_STATUS_DONE;
		}
	}
#endif
