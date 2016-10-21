/*
 * fft_globales.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_FFT
	arm_rfft_instance_q31 fft_inst_q31;
	arm_cfft_radix4_instance_q31 fft_inst_q31_complex;

	volatile q31_t fft_vector[FFT_SIZE*2];	// Espectro de la senal transformada

	uint8_t fft_status = FFT_STATUS_EMPTY;
#endif
