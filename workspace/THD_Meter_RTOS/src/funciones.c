/*
 * procesamiento.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"

void main_while()
{
	#if (USE_FFT)
		// Para hacer la FFT que entra por UART0
		if(uart0_rx_status == UART_STATUS_LEIDO && fft_status != FFT_STATUS_TO_DO)
		{
			static uint16_t fft_idx = 0;
			uint8_t *fft_vector_p = (uint8_t *) fft_vector;	// uso un (uint8_t *) porque por la uart leo de a 1 byte

			fft_vector_p[fft_idx] = uart0_in;		// Guardo lo leido en el vector de la FFT

			uart0_rx_status = UART_STATUS_EMPTY;	// Una vez guardado el valor, doy permiso para leer otro dato

			fft_idx ++;
			fft_idx %= FFT_SIZE*sizeof(uint32_t);

			if(!fft_idx)
			{
				fft_status = FFT_STATUS_TO_DO;	// Doy orden para realizar FFT
				// una vez que se realiza la fft, se envia automaticamente por la UART
			}
		}
	#endif
}
