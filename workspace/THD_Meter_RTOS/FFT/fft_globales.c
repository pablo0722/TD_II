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

	volatile q31_t fft_in[FFT_SIZE];					// Espectro de la senal a transformar
	volatile q31_t fft_out_cmplx[FFT_SIZE*2];			// Espectro de la senal transformada compleja
	volatile q31_t fft_out_dep[FFT_SIZE];				// Densidad espectral de potencia
	volatile q31_t fft_out_rem[FFT_SIZE];				// Senal temporal remanente (sin fundamental)

	volatile q31_t fft_max_val;							// max de la dep
	volatile uint32_t fft_max_index;					// posición de la dep

	volatile q31_t THD;

	uint8_t volatile fft_status = FFT_STATUS_EMPTY;		// Estado de la FFT
	uint8_t volatile ifft_status = IFFT_STATUS_EMPTY;	// Estado de la IFFT
#endif
