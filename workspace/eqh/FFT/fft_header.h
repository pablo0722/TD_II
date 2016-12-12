/*
 * fft_header.h
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */

#ifndef FFT_HEADER_H_
#define FFT_HEADER_H_



#include "header.h"


// ********* MODO DE USO ********** //
//
// *** UTILIDADES.H
// 		Se debe poner USE_FFT en ON para poder utilizar las funciones de FFT
// 		Se puede poner UARTN_TRANSMIT en UART_TRANSMIT_FFT para transmitir automaticamente por UART la fft realizada
//
// *** FFT_HEADER.H
// 		en FFT_SIZE se especifica el tamanio del vector que se quiere transformar.
//
// *** MAIN
// 		primero se debe poner el flag 'fft_status' en FFT_STATUS_EMPTY (para que nadie intente acceder al vector 'fft_vector'),
// 		luego se carga el vector 'fft_vector' con la señal a transformar (solo parte real, tamanio FFT_SIZE),
// 		luego se debe poner el flag 'fft_status' en FFT_STATUS_TO_DO (para indicar que se debe realizar FFT),
// 		finalmente se debe esperar a que el flag 'fft_status' sea igual a FFT_STATUS_DONE (que indica que ya se realizo la FFT).
// 		la senial transformada se encuentra en el mismo vector 'fft_vector'
//
// ******************************** //


// ********* FUNCIONES ********** //
	#if USE_FFT
	#endif
// ****************************** //


// ***************** DEFINES ***************** //
	#if USE_FFT
			#define     FFT_SIZE_32				32
			#define     FFT_SIZE_64				64
			#define     FFT_SIZE_128			128
			#define     FFT_SIZE_256			256
			#define     FFT_SIZE_512			512
			#define     FFT_SIZE_1024			1024
			#define     FFT_SIZE_2048			2048
			#define     FFT_SIZE_4096			4096
		#define     FFT_SIZE    	           	FFT_SIZE_512	// Tamanio del vector del modulo de la FFT = tamanio parte real de senial a transformar
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_FFT
		extern q31_t fft_window[FFT_SIZE];

		extern arm_rfft_instance_q31 fft_inst_q31;			// Estructura para aplicar FFT
		extern arm_rfft_instance_q31 ifft_inst_q31;			// Estructura para aplicar IFFT
	#endif
// ********************************************** //


// ************* INICIALIZACION ************* //
	#include "fft_init.h"
	#include "fft_func.h"
// ****************************************** //


#endif /* FFT_HEADER_H_ */
