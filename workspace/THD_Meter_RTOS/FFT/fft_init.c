/*
 * fft_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"


#define FFT_INIT_FFT_LENGTH 	FFT_SIZE
#define FFT_INIT_IFFT 			FALSE
#define FFT_INIT_BIT_REVERSE 	TRUE


#if USE_FFT
	void fft_init()
	{
		#if DEBUG_MODE
			printf("[info] init FFT: \r\n");
			printf("\t format: q31 \r\n");
			printf("\t fftLength(solo parte real): %d \r\n", FFT_SIZE);
		#endif

		#if DEBUG_MODE
			arm_status st =
		#endif

		arm_rfft_init_q31(&fft_inst_q31, &fft_inst_q31_complex, FFT_INIT_FFT_LENGTH, FFT_INIT_IFFT, FFT_INIT_BIT_REVERSE);

		#if DEBUG_MODE
			if(st != ARM_MATH_SUCCESS)
			{
				printf("[error] FFT init: \r\n");
				printf("\t st = %d \r\n", st);
			}
		#endif
	}
#endif
