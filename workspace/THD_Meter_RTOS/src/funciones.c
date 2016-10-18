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
		#if (FFT_FROM_UART) && (UART_BY_VECTOR)
			if (uart_rx_done)
			{
				uart_rx_done --;
		#endif

				const uint16_t fft_length = FFT_SIZE*2; // el "*2" es porque es real e imaginario

				#if (FFT_FROM_UART) && (UART_BY_VECTOR)
					arm_rfft_q31(&fft_inst_q31, (q31_t *) uart_in, fft_out);
				#else
					arm_rfft_q31(&fft_inst_q31, fft_in, fft_out);
				#endif
				arm_cmplx_mag_q31(fft_out, fft_out, fft_length);

				fft_done = FFT_DONE_MAX;
		#if (FFT_FROM_UART) && (UART_BY_VECTOR)
			}
		#endif
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

		#if UART_BYTE_BY_BYTE
			if(!uart_rx_done)
			{
				static uint16_t idx = 0;
				uint8_t read_char = 0;
				int bytes = Chip_UART_ReadRB(LPC_UARTN, &rxring, &read_char, 1);

				if(bytes > 0)
				{
					uart_in = read_char;
					uart_rx_done = UART_RX_DONE_MAX;
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
