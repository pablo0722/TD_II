/*
 * uart_irq.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "uart_header.h"
#include "uart_header_priv.h"



#if USE_UART
	#if USE_UART0
		void UART0_IRQHandler(void)
		{
			if(uart0_out_status != UART_OUT_STATUS_NONE)
			{
				if (Chip_UART_GetIntsEnabled(LPC_UART0) & UART_IER_THREINT)
				{
					Chip_UART_SendByte(LPC_UART0, uart0_out[uart0_out_idx]);
					uart0_out_idx++;
					uart0_out_idx %= uart0_out_len;

					if(!uart0_out_idx)
					{
						if( (uart0_out_status == UART_OUT_STATUS_A_ESCRIBIENDO) || (uart0_out_status == UART_OUT_STATUS_B_ESCRIBIENDO) )
						{
							uart0_out_status = UART_OUT_STATUS_NONE;
						}
						else if(uart0_out_status == UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO)
						{
							uart0_out_status = UART_OUT_STATUS_B_ESCRIBIENDO;
							uart0_out = uart0_out_B;
							uart0_out_len = uart0_out_len_B;
						}
						else if(uart0_out_status == UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO)
						{
							uart0_out_status = UART_OUT_STATUS_A_ESCRIBIENDO;
							uart0_out = uart0_out_A;
							uart0_out_len = uart0_out_len_A;
						}
					}
				}
			}
			while(Chip_UART_ReadLineStatus(LPC_UART0) & UART_LSR_RDR)
			{
				uint8_t read_char = Chip_UART_ReadByte(LPC_UART0);

				if(uart0_in_status > UART_IN_STATUS_NONE)
				{
					uart0_in[uart0_in_idx] = read_char;
					uart0_in_idx++;
					uart0_in_idx %= uart0_in_len;

					if(!uart0_in_idx)
					{
						if(uart0_in_status == UART_IN_STATUS_A_LEYENDO)
						{
							if(uart0_in_B)
							{
								uart0_in = uart0_in_B;
								uart0_in_status = UART_IN_STATUS_B_LEYENDO_A_LISTO;
							}
							else
							{
								uart0_in_status = UART_IN_STATUS_NONE;
							}
						}
						else if(uart0_in_status == UART_IN_STATUS_B_LEYENDO)
						{
							uart0_in = uart0_in_A;
							uart0_in_status = UART_IN_STATUS_A_LEYENDO_B_LISTO;
						}
						else if(uart0_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO)
						{
							uart0_in_status = UART_IN_STATUS_B_LISTO;
						}
						else if(uart0_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO)
						{
							uart0_in_status = UART_IN_STATUS_A_LISTO;
						}
					}
				}
			}
		}
	#endif

	#if USE_UART1
		void UART1_IRQHandler(void)
		{
			if(uart1_out_status != UART_OUT_STATUS_NONE)
			{
				if (LPC_UART1->IER & UART_IER_THREINT)
				{
					Chip_UART_SendByte(LPC_UART1, uart1_out[uart1_out_idx]);
					uart1_out_idx++;
					uart1_out_idx %= uart1_out_len;

					if(!uart1_out_idx)
					{
						if( (uart1_out_status == UART_OUT_STATUS_A_ESCRIBIENDO) || (uart1_out_status == UART_OUT_STATUS_B_ESCRIBIENDO) )
						{
							uart1_out_status = UART_OUT_STATUS_NONE;
						}
						else if(uart1_out_status == UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO)
						{
							uart1_out_status = UART_OUT_STATUS_B_ESCRIBIENDO;
							uart1_out = uart1_out_B;
							uart1_out_len = uart1_out_len_B;
						}
						else if(uart1_out_status == UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO)
						{
							uart1_out_status = UART_OUT_STATUS_A_ESCRIBIENDO;
							uart1_out = uart1_out_A;
							uart1_out_len = uart1_out_len_A;
						}
					}
				}
			}
			while(Chip_UART_ReadLineStatus(LPC_UART1) & UART_LSR_RDR)
			{
				uint8_t read_char = Chip_UART_ReadByte(LPC_UART1);

				if(uart1_in_status > UART_IN_STATUS_NONE)
				{
					uart1_in[uart1_in_idx] = read_char;
					uart1_in_idx++;
					uart1_in_idx %= uart1_in_len;

					if(!uart1_in_idx)
					{
						if(uart1_in_status == UART_IN_STATUS_A_LEYENDO)
						{
							if(uart1_in_B)
							{
								uart1_in = uart1_in_B;
								uart1_in_status = UART_IN_STATUS_B_LEYENDO_A_LISTO;
							}
							else
							{
								uart1_in_status = UART_IN_STATUS_NONE;
							}
						}
						else if(uart1_in_status == UART_IN_STATUS_B_LEYENDO)
						{
							uart1_in = uart1_in_A;
							uart1_in_status = UART_IN_STATUS_A_LEYENDO_B_LISTO;
						}
						else if(uart1_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO)
						{
							uart1_in_status = UART_IN_STATUS_B_LISTO;
						}
						else if(uart1_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO)
						{
							uart1_in_status = UART_IN_STATUS_A_LISTO;
						}
					}
				}
			}
		}
	#endif

	#if USE_UART2
		void UART2_IRQHandler(void)
		{
			if(uart2_out_status != UART_OUT_STATUS_NONE)
			{
				if (LPC_UART2->IER & UART_IER_THREINT)
				{
					Chip_UART_SendByte(LPC_UART2, uart2_out[uart2_out_idx]);
					uart2_out_idx++;
					uart2_out_idx %= uart2_out_len;

					if(!uart2_out_idx)
					{
						if( (uart2_out_status == UART_OUT_STATUS_A_ESCRIBIENDO) || (uart2_out_status == UART_OUT_STATUS_B_ESCRIBIENDO) )
						{
							uart2_out_status = UART_OUT_STATUS_NONE;
						}
						else if(uart2_out_status == UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO)
						{
							uart2_out_status = UART_OUT_STATUS_B_ESCRIBIENDO;
							uart2_out = uart2_out_B;
							uart2_out_len = uart2_out_len_B;
						}
						else if(uart2_out_status == UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO)
						{
							uart2_out_status = UART_OUT_STATUS_A_ESCRIBIENDO;
							uart2_out = uart2_out_A;
							uart2_out_len = uart2_out_len_A;
						}
					}
				}
			}
			while(Chip_UART_ReadLineStatus(LPC_UART2) & UART_LSR_RDR)
			{
				uint8_t read_char = Chip_UART_ReadByte(LPC_UART2);

				if(uart2_in_status > UART_IN_STATUS_NONE)
				{
					uart2_in[uart2_in_idx] = read_char;
					uart2_in_idx++;
					uart2_in_idx %= uart2_in_len;

					if(!uart2_in_idx)
					{
						if(uart2_in_status == UART_IN_STATUS_A_LEYENDO)
						{
							if(uart2_in_B)
							{
								uart2_in = uart2_in_B;
								uart2_in_status = UART_IN_STATUS_B_LEYENDO_A_LISTO;
							}
							else
							{
								uart2_in_status = UART_IN_STATUS_NONE;
							}
						}
						else if(uart2_in_status == UART_IN_STATUS_B_LEYENDO)
						{
							uart2_in = uart2_in_A;
							uart2_in_status = UART_IN_STATUS_A_LEYENDO_B_LISTO;
						}
						else if(uart2_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO)
						{
							uart2_in_status = UART_IN_STATUS_B_LISTO;
						}
						else if(uart2_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO)
						{
							uart2_in_status = UART_IN_STATUS_A_LISTO;
						}
					}
				}
			}
		}
	#endif

	#if USE_UART3
		void UART3_IRQHandler(void)
		{
			if(uart3_out_status != UART_OUT_STATUS_NONE)
			{
				if (LPC_UART3->IER & UART_IER_THREINT)
				{
					Chip_UART_SendByte(LPC_UART3, uart3_out[uart3_out_idx]);
					uart3_out_idx++;
					uart3_out_idx %= uart3_out_len;

					if(!uart3_out_idx)
					{
						if( (uart3_out_status == UART_OUT_STATUS_A_ESCRIBIENDO) || (uart3_out_status == UART_OUT_STATUS_B_ESCRIBIENDO) )
						{
							uart3_out_status = UART_OUT_STATUS_NONE;
						}
						else if(uart3_out_status == UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO)
						{
							uart3_out_status = UART_OUT_STATUS_B_ESCRIBIENDO;
							uart3_out = uart3_out_B;
							uart3_out_len = uart3_out_len_B;
						}
						else if(uart3_out_status == UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO)
						{
							uart3_out_status = UART_OUT_STATUS_A_ESCRIBIENDO;
							uart3_out = uart3_out_A;
							uart3_out_len = uart3_out_len_A;
						}
					}
				}
			}
			while(Chip_UART_ReadLineStatus(LPC_UART3) & UART_LSR_RDR)
			{
				uint8_t read_char = Chip_UART_ReadByte(LPC_UART3);

				if(uart3_in_status > UART_IN_STATUS_NONE)
				{
					uart3_in[uart3_in_idx] = read_char;
					uart3_in_idx++;
					uart3_in_idx %= uart3_in_len;

					if(!uart3_in_idx)
					{
						if(uart3_in_status == UART_IN_STATUS_A_LEYENDO)
						{
							if(uart3_in_B)
							{
								uart3_in = uart3_in_B;
								uart3_in_status = UART_IN_STATUS_B_LEYENDO_A_LISTO;
							}
							else
							{
								uart3_in_status = UART_IN_STATUS_NONE;
							}
						}
						else if(uart3_in_status == UART_IN_STATUS_B_LEYENDO)
						{
							uart3_in = uart3_in_A;
							uart3_in_status = UART_IN_STATUS_A_LEYENDO_B_LISTO;
						}
						else if(uart3_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO)
						{
							uart3_in_status = UART_IN_STATUS_B_LISTO;
						}
						else if(uart3_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO)
						{
							uart3_in_status = UART_IN_STATUS_A_LISTO;
						}
					}
				}
			}
		}
	#endif
#endif
