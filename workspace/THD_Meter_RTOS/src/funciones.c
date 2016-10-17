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
		if (uart_rx_fft_done)
		{
			uart_rx_fft_done --;

			const uint16_t fft_length = FFT_SIZE*2; // el "*2" es porque es real e imaginario

			arm_rfft_q31(&fft_inst_q31, fft_in, fft_out);
			arm_cmplx_mag_q31(fft_out, fft_out, fft_length);

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

		#if FFT_FROM_UART
			static uint16_t idx=0;
			uint8_t read_char = 0;
			int bytes = Chip_UART_ReadRB(LPC_UARTN, &rxring, &read_char, 1);

			if(bytes > 0)
			{
				char *fft_in_p = (char *) fft_in;	// uso puntero a char para guardar byte por byte desde la uart al vector de fft_in
				fft_in_p[idx] = read_char;
				idx++;
				idx %= UART_SIZE;

				if(idx==0)
				{
					uart_rx_fft_done = 1;
				}
			}
		#endif

		#if FFT_TO_UART
			if (fft_done)
			{
				fft_done --;

				Chip_UART_SendRB(LPC_UART0, &txring, fft_out, UART_SIZE/2); // Envio la mitad del espectro ya que esta espejado
			}
		#endif
	}
#endif
