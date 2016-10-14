/*
 * procesamiento.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


#if USE_FFT
	void fft_function()
	{
		if (uart_rx_done)
		{
			uart_rx_done --;

			const uint16_t fft_length = FFT_SIZE*2; // el "*2" es porque es real e imaginario

			arm_rfft_q31(&fft_inst_q31, mSignalIn, spectrum);
			arm_cmplx_mag_q31(spectrum, spectrum, fft_length);

			fft_done = FFT_DONE_MAX;
		}
	}
#endif


#if USE_UART
	void main_uart()
	{
		#if UART_LOOPBACK
			if (uart_rx_done)
			{
				uart_rx_done --;

				Chip_UART_SendRB(LPC_UART0, &txring, mSignalIn, UART_SIZE);
			}
		#endif

		#if UART_FFT
			if (fft_done)
			{
				fft_done --;

				Chip_UART_SendRB(LPC_UART0, &txring, spectrum, UART_SIZE/2); // Envio la mitad del espectro ya que esta espejado
			}
		#endif
	}
#endif
