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
		void fft_init();
		void fft_function();
	#endif
// ****************************** //


// ***************** DEFINES ***************** //
	#if USE_FFT
		#define     FFT_SIZE    	           	512	// Tamanio del vector del modulo de la FFT (Es un cuarto (1/2) del tamanio original por estar espejado)

			// estados del flag 'fft_status'
		#define	FFT_STATUS_EMPTY 	0	// No hay FFT realizada ni pedido para realizarla
		#define	FFT_STATUS_TO_DO 	1	// Orden para realizar la FFT
		#define	FFT_STATUS_DONE 	2	// FFT realizada
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_FFT
		extern arm_rfft_instance_q31 fft_inst_q31;					// Estructura para aplicar FFT
		extern arm_cfft_radix4_instance_q31 fft_inst_q31_complex;	// Estructura para aplicar FFT

		extern volatile q31_t fft_vector[FFT_SIZE*2];				// Espectro de la senal transformada (el "*2" es porque es real e imaginario)

		extern uint8_t fft_status;									// Estado de la FFT
	#endif
// ********************************************** //


#endif /* FFT_HEADER_H_ */
