/*
 * uart_func.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_UART
	#if USE_UART0
		void main_uart0()
		{
				// Si ya se uso el ultimo caracter leido, leo otro:
			if(uart0_rx_status == UART_STATUS_EMPTY)
			{
				uint8_t read_char = 0;
				int bytes = Chip_UART_ReadRB(LPC_UART0, &rxring0, &read_char, 1);

				if(bytes > 0)
				{
					uart0_in = read_char;
					uart0_rx_status = UART_STATUS_LEIDO;
				}
			}

				// Transmite FFT por UART
			#if (USE_FFT) && (UART0_TRANSMIT == UART_TRANSMIT_FFT)
				if (fft_status == FFT_STATUS_DONE)
				{
					fft_status = FFT_STATUS_EMPTY;
					Chip_UART_SendRB(LPC_UART0, &txring0, (const void *)fft_vector_out, FFT_SIZE*2); // Envio la mitad del espectro ya que esta espejado
				}
			#endif

				// Transmite lo mismo que leyo (loopback)
			#if (UART0_TRANSMIT == UART_TRANSMIT_LOOPBACK)
				if(uart0_rx_status == UART_STATUS_LEIDO)
				{
					Chip_UART_SendRB(LPC_UART0, &txring0, &uart0_in, 1);
				}
			#endif
		}
	#endif

	#if USE_UART1
		void main_uart1()
		{
				// Si ya se uso el ultimo caracter leido, leo otro:
			if(uart1_rx_status == UART_STATUS_EMPTY)
			{
				uint8_t read_char = 0;
				int bytes = Chip_UART_ReadRB(LPC_UART1, &rxring1, &read_char, 1);

				if(bytes > 0)
				{
					uart1_in = read_char;
					uart1_rx_status = UART_STATUS_LEIDO;
				}
			}

				// Transmite FFT por UART
			#if (UART1_TRANSMIT == UART_TRANSMIT_FFT)
				if (fft_status == FFT_STATUS_DONE)
				{
					Chip_UART_SendRB(LPC_UART1, &txring1, (const void *)fft_vector, FFT_SIZE/2); // Envio la mitad del espectro ya que esta espejado
				}
			#endif

				// Transmite lo mismo que leyo (loopback)
			#if (UART1_TRANSMIT == UART_TRANSMIT_LOOPBACK)
				if(uart1_rx_status == UART_STATUS_LEIDO)
				{
					Chip_UART_SendRB(LPC_UART1, &txring1, &uart1_in, 1);
				}
			#endif
		}
	#endif

	#if USE_UART2
		void main_uart2()
		{
				// Si ya se uso el ultimo caracter leido, leo otro:
			if(uart2_rx_status == UART_STATUS_EMPTY)
			{
				uint8_t read_char = 0;
				int bytes = Chip_UART_ReadRB(LPC_UART2, &rxring2, &read_char, 1);

				if(bytes > 0)
				{
					uart2_in = read_char;
					uart2_rx_status = UART_STATUS_LEIDO;
				}
			}

				// Transmite FFT por UART
			#if (UART2_TRANSMIT == UART_TRANSMIT_FFT)
				if (fft_status == FFT_STATUS_DONE)
				{
					Chip_UART_SendRB(LPC_UART2, &txring2, (const void *)fft_vector, FFT_SIZE/2); // Envio la mitad del espectro ya que esta espejado
				}
			#endif

				// Transmite lo mismo que leyo (loopback)
			#if (UART2_TRANSMIT == UART_TRANSMIT_LOOPBACK)
				if(uart2_rx_status == UART_STATUS_LEIDO)
				{
					Chip_UART_SendRB(LPC_UART2, &txring2, &uart2_in, 1);
				}
			#endif
		}
	#endif

	#if USE_UART3
		void main_uart3()
		{
				// Si ya se uso el ultimo caracter leido, leo otro:
			if(uart3_rx_status == UART_STATUS_EMPTY)
			{
				uint8_t read_char = 0;
				int bytes = Chip_UART_ReadRB(LPC_UART3, &rxring3, &read_char, 1);

				if(bytes > 0)
				{
					uart3_in = read_char;
					uart3_rx_status = UART_STATUS_LEIDO;
				}
			}

				// Transmite FFT por UART
			#if (UART3_TRANSMIT == UART_TRANSMIT_FFT)
				if (fft_status == FFT_STATUS_DONE)
				{
					Chip_UART_SendRB(LPC_UART3, &txring3, (const void *)fft_vector, FFT_SIZE/2); // Envio la mitad del espectro ya que esta espejado
				}
			#endif

				// Transmite lo mismo que leyo (loopback)
			#if (UART3_TRANSMIT == UART_TRANSMIT_LOOPBACK)
				if(uart3_rx_status == UART_STATUS_LEIDO)
				{
					Chip_UART_SendRB(LPC_UART3, &txring3, &uart3_in, 1);
				}
			#endif
		}
	#endif

	void main_uart()
	{
		#if USE_UART0
			main_uart0();
		#endif
		#if USE_UART1
			main_uart1();
		#endif
		#if USE_UART2
			main_uart2();
		#endif
		#if USE_UART3
			main_uart3();
		#endif
	}
#endif
