/*
 * fft_globales.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_FFT
	arm_rfft_instance_q31 fft_inst_q31;
	arm_rfft_instance_q31 ifft_inst_q31;
#endif
