/*
 * fft_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"


#define FFT_INIT_FFT_LENGTH 	FFT_SIZE
#define FFT_INIT_FFT 			TRUE
#define FFT_INIT_IFFT 			FALSE
#define FFT_INIT_BIT_REVERSE 	TRUE


#if USE_FFT
	STATIC INLINE void fft_init()
	{
		static arm_cfft_radix4_instance_q31 fft_inst_q31_complex;
		#if DEBUG_MODE
			printf("[info] init FFT: \r\n");
			printf("\t format: q31 \r\n");
			printf("\t fftLength(solo parte real): %d \r\n", FFT_SIZE);
		#endif

		#if DEBUG_MODE
			arm_status st =
		#endif

		arm_rfft_init_q31(&fft_inst_q31, &fft_inst_q31_complex, FFT_INIT_FFT_LENGTH, FFT_INIT_FFT, FFT_INIT_BIT_REVERSE);
		arm_rfft_init_q31(&ifft_inst_q31, &fft_inst_q31_complex, FFT_INIT_FFT_LENGTH, FFT_INIT_IFFT, FFT_INIT_BIT_REVERSE);

		#if DEBUG_MODE
			if(st != ARM_MATH_SUCCESS)
			{
				printf("[error] FFT init: \r\n");
				printf("\t st = %d \r\n", st);
			}
		#endif
	}
#endif

