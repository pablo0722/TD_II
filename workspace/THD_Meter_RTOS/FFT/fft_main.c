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
			arm_rfft_q31(&fft_inst_q31, (q31_t *)fft_vector, (q31_t *)fft_vector_out);
			arm_cmplx_mag_q31((q31_t *)fft_vector_out, (q31_t *)fft_vector_out, FFT_SIZE*2);

			fft_status = FFT_STATUS_DONE;
		}
	}
#endif
