/*
 * globales.c
 *
 *  Created on: 7 de nov. de 2016
 *      Author: Pablo
 */


#include "header.h"


// ************* VARIABLES GLOBALES ************* //
	Bool flag_dac_send;	// Envia senial por DAC
	Bool flag_do_thd;	// Calcula THD
	Bool flag_do_rem;	// Calcula senal remanente

	q31_t THD;
	q31_t fft_max;
	uint32_t fft_max_idx;
	q31_t fft_min;
// ********************************************** //

// *** BUFFERS *** //
	uint32_t buffer_complex	[FFT_SIZE*2]
							 	 	 __attribute__ ((section (".bss.$RamAHB32")));

	uint32_t buffer_dac_out	[FFT_SIZE*2]
							 	 	 __attribute__ ((section (".bss.$RamAHB32")));

	uint32_t buffer_dep		[FFT_SIZE]
							 	 	 __attribute__ ((section (".bss.$RamAHB32")));

	uint32_t buffer_dac		[FFT_SIZE/2]
							 	 	 __attribute__ ((section (".bss.$RamAHB32")));
// *************** //
