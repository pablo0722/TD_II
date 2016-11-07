/*
 * uart_func.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"
#include "uart_header_priv.h"



// *** FUNCIONES *** //
	#if (USE_UART)
		// *** LEER *** //
			#if (USE_UART0)
				void uart0_leer(uint8_t *buffer_in_A, uint8_t *buffer_in_B, uint32_t buffer_len)
				{
					if( (buffer_len > 0) && buffer_in_A )
					{
						uart0_in_A = buffer_in_A;
						uart0_in_B = buffer_in_B;
						uart0_in_len = buffer_len;
						uart0_in = buffer_in_A;
						uart0_in_status = UART_IN_STATUS_A_LEYENDO;
					}
					else
					{
						uart0_in_A = NULL;
						uart0_in_B = NULL;
						uart0_in_len = 0;
						uart0_in = NULL;
						uart0_in_status = UART_IN_STATUS_NONE;
					}

					uart0_in_idx = 0 ;
				}
			#endif

			#if (USE_UART1)
				void uart1_leer(uint8_t *buffer_in_A, uint8_t *buffer_in_B, uint32_t buffer_len)
				{
					if( (buffer_len > 0) && buffer_in_A )
					{
						uart1_in_A = buffer_in_A;
						uart1_in_B = buffer_in_B;
						uart1_in_len = buffer_len;
						uart1_in = buffer_in_A;
						uart1_in_status = UART_IN_STATUS_A_LEYENDO;
					}
					else
					{
						uart1_in_A = NULL;
						uart1_in_B = NULL;
						uart1_in_len = 0;
						uart1_in = NULL;
						uart1_in_status = UART_IN_STATUS_NONE;
					}

					uart1_in_idx = 0 ;
				}
			#endif

			#if (USE_UART2)
				void uart2_leer(uint8_t *buffer_in_A, uint8_t *buffer_in_B, uint32_t buffer_len)
				{
					if( (buffer_len > 0) && buffer_in_A )
					{
						uart2_in_A = buffer_in_A;
						uart2_in_B = buffer_in_B;
						uart2_in_len = buffer_len;
						uart2_in = buffer_in_A;
						uart2_in_status = UART_IN_STATUS_A_LEYENDO;
					}
					else
					{
						uart2_in_A = NULL;
						uart2_in_B = NULL;
						uart2_in_len = 0;
						uart2_in = NULL;
						uart2_in_status = UART_IN_STATUS_NONE;
					}

					uart2_in_idx = 0 ;
				}
			#endif

			#if (USE_UART3)
				void uart3_leer(uint8_t *buffer_in_A, uint8_t *buffer_in_B, uint32_t buffer_len)
				{
					if( (buffer_len > 0) && buffer_in_A )
					{
						uart3_in_A = buffer_in_A;
						uart3_in_B = buffer_in_B;
						uart3_in_len = buffer_len;
						uart3_in = buffer_in_A;
						uart3_in_status = UART_IN_STATUS_A_LEYENDO;
					}
					else
					{
						uart3_in_A = NULL;
						uart3_in_B = NULL;
						uart3_in_len = 0;
						uart3_in = NULL;
						uart3_in_status = UART_IN_STATUS_NONE;
					}

					uart3_in_idx = 0 ;
				}
			#endif
		// ************ //

		// *** TERMINO DE LEER UN BUFFER *** //
			#if (USE_UART0)
				uint8_t *uart0_puedo_procesar()
				{
					if( (uart0_in_status == UART_IN_STATUS_A_LISTO) || (uart0_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO) )
					{
						return uart0_in_A;
					}
					else if( (uart0_in_status == UART_IN_STATUS_B_LISTO) || (uart0_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO) )
					{
						return uart0_in_B;
					}

					return NULL;
				}
			#endif

			#if (USE_UART1)
				uint8_t *uart1_puedo_procesar()
				{
					if( (uart1_in_status == UART_IN_STATUS_A_LISTO) || (uart1_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO) )
					{
						return uart1_in_A;
					}
					else if( (uart1_in_status == UART_IN_STATUS_B_LISTO) || (uart1_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO) )
					{
						return uart1_in_B;
					}

					return NULL;
				}
			#endif

			#if (USE_UART2)
				uint8_t *uart2_puedo_procesar()
				{
					if( (uart2_in_status == UART_IN_STATUS_A_LISTO) || (uart2_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO) )
					{
						return uart2_in_A;
					}
					else if( (uart2_in_status == UART_IN_STATUS_B_LISTO) || (uart2_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO) )
					{
						return uart2_in_B;
					}

					return NULL;
				}
			#endif

			#if (USE_UART3)
				uint8_t *uart3_puedo_procesar()
				{
					if( (uart3_in_status == UART_IN_STATUS_A_LISTO) || (uart3_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO) )
					{
						return uart3_in_A;
					}
					else if( (uart3_in_status == UART_IN_STATUS_B_LISTO) || (uart3_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO) )
					{
						return uart3_in_B;
					}

					return NULL;
				}
			#endif
		// ********************************* //

		// *** TERMINE DE PROCESAR UN BUFFER (permite seguir leyendo) *** //
			#if (USE_UART0)
				void uart0_proceso_listo()
				{
					if(uart0_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO)
					{
						uart0_in_status = UART_IN_STATUS_B_LEYENDO;
					}
					else if(uart0_in_status == UART_IN_STATUS_A_LISTO)
					{
						uart0_in_status = UART_IN_STATUS_A_LEYENDO_B_LISTO;
						uart0_in = uart0_in_A;
					}
					else if(uart0_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO)
					{
						uart0_in_status = UART_IN_STATUS_A_LEYENDO;
					}
					else if(uart0_in_status == UART_IN_STATUS_B_LISTO)
					{
						uart0_in_status = UART_IN_STATUS_B_LEYENDO_A_LISTO;
						uart0_in = uart0_in_B;
					}
				}
			#endif

			#if (USE_UART1)
				void uart1_proceso_listo()
				{
					if(uart1_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO)
					{
						uart1_in_status = UART_IN_STATUS_B_LEYENDO;
					}
					else if(uart1_in_status == UART_IN_STATUS_A_LISTO)
					{
						uart1_in_status = UART_IN_STATUS_A_LEYENDO_B_LISTO;
						uart1_in = uart1_in_A;
					}
					else if(uart1_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO)
					{
						uart1_in_status = UART_IN_STATUS_A_LEYENDO;
					}
					else if(uart1_in_status == UART_IN_STATUS_B_LISTO)
					{
						uart1_in_status = UART_IN_STATUS_B_LEYENDO_A_LISTO;
						uart1_in = uart1_in_B;
					}
				}
			#endif

			#if (USE_UART2)
				void uart2_proceso_listo()
				{
					if(uart2_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO)
					{
						uart2_in_status = UART_IN_STATUS_B_LEYENDO;
					}
					else if(uart2_in_status == UART_IN_STATUS_A_LISTO)
					{
						uart2_in_status = UART_IN_STATUS_A_LEYENDO_B_LISTO;
						uart2_in = uart2_in_A;
					}
					else if(uart2_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO)
					{
						uart2_in_status = UART_IN_STATUS_A_LEYENDO;
					}
					else if(uart2_in_status == UART_IN_STATUS_B_LISTO)
					{
						uart2_in_status = UART_IN_STATUS_B_LEYENDO_A_LISTO;
						uart2_in = uart2_in_B;
					}
				}
			#endif

			#if (USE_UART3)
				void uart3_proceso_listo()
				{
					if(uart3_in_status == UART_IN_STATUS_B_LEYENDO_A_LISTO)
					{
						uart3_in_status = UART_IN_STATUS_B_LEYENDO;
					}
					else if(uart3_in_status == UART_IN_STATUS_A_LISTO)
					{
						uart3_in_status = UART_IN_STATUS_A_LEYENDO_B_LISTO;
						uart3_in = uart3_in_A;
					}
					else if(uart3_in_status == UART_IN_STATUS_A_LEYENDO_B_LISTO)
					{
						uart3_in_status = UART_IN_STATUS_A_LEYENDO;
					}
					else if(uart3_in_status == UART_IN_STATUS_B_LISTO)
					{
						uart3_in_status = UART_IN_STATUS_B_LEYENDO_A_LISTO;
						uart3_in = uart3_in_B;
					}
				}
			#endif
		// ********************************* //

		// *** ESCRIBIR *** //
			#if (USE_UART0)
				Bool uart0_escribir(const uint8_t *buffer_out, uint32_t buffer_len)
				{
					if( (uart0_out_status == UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO) || (uart0_out_status == UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO) )
						return FALSE;

					if(uart0_out_status == UART_OUT_STATUS_A_ESCRIBIENDO)
					{
						uart0_out_B = buffer_out;
						uart0_out_len = uart0_out_len_B = buffer_len;
						uart0_out_status = UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO;
					}
					else if(uart0_out_status == UART_OUT_STATUS_B_ESCRIBIENDO)
					{
						uart0_out_A = buffer_out;
						uart0_out_len = uart0_out_len_A = buffer_len;
						uart0_out_status = UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO;
					}
					else // if(uart0_out_status == UART_OUT_STATUS_NONE)
					{
						uart0_out = uart0_out_A = buffer_out;
						uart0_out_len = uart0_out_len_A = buffer_len;
						uart0_out_idx = 0;
						uart0_out_status = UART_OUT_STATUS_A_ESCRIBIENDO;
					}

					return TRUE;
				}
			#endif

			#if (USE_UART1)
				Bool uart1_escribir(const uint8_t *buffer_out, uint32_t buffer_len)
				{
					if( (uart1_out_status == UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO) || (uart1_out_status == UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO) )
						return FALSE;

					if(uart1_out_status == UART_OUT_STATUS_A_ESCRIBIENDO)
					{
						uart1_out_B = buffer_out;
						uart1_out_len = uart1_out_len_B = buffer_len;
						uart1_out_status = UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO;
					}
					else if(uart1_out_status == UART_OUT_STATUS_B_ESCRIBIENDO)
					{
						uart1_out_A = buffer_out;
						uart1_out_len = uart1_out_len_A = buffer_len;
						uart1_out_status = UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO;
					}
					else // if(uart1_out_status == UART_OUT_STATUS_NONE)
					{
						uart1_out = uart1_out_A = buffer_out;
						uart1_out_len = uart1_out_len_A = buffer_len;
						uart1_out_idx = 0;
						uart1_out_status = UART_OUT_STATUS_A_ESCRIBIENDO;
					}

					return TRUE;
				}
			#endif

			#if (USE_UART2)
				Bool uart2_escribir(const uint8_t *buffer_out, uint32_t buffer_len)
				{
					if( (uart2_out_status == UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO) || (uart2_out_status == UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO) )
						return FALSE;

					if(uart2_out_status == UART_OUT_STATUS_A_ESCRIBIENDO)
					{
						uart2_out_B = buffer_out;
						uart2_out_len = uart2_out_len_B = buffer_len;
						uart2_out_status = UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO;
					}
					else if(uart2_out_status == UART_OUT_STATUS_B_ESCRIBIENDO)
					{
						uart2_out_A = buffer_out;
						uart2_out_len = uart2_out_len_A = buffer_len;
						uart2_out_status = UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO;
					}
					else // if(uart2_out_status == UART_OUT_STATUS_NONE)
					{
						uart2_out = uart2_out_A = buffer_out;
						uart2_out_len = uart2_out_len_A = buffer_len;
						uart2_out_idx = 0;
						uart2_out_status = UART_OUT_STATUS_A_ESCRIBIENDO;
					}

					return TRUE;
				}
			#endif

			#if (USE_UART3)
				bool uart3_escribir(const uint8_t *buffer_out, uint32_t buffer_len)
				{
					if( (uart3_out_status == UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO) || (uart3_out_status == UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO) )
						return FALSE;

					if(uart3_out_status == UART_OUT_STATUS_A_ESCRIBIENDO)
					{
						uart3_out_B = buffer_out;
						uart3_out_len = uart3_out_len_B = buffer_len;
						uart3_out_status = UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO;
					}
					else if(uart3_out_status == UART_OUT_STATUS_B_ESCRIBIENDO)
					{
						uart3_out_A = buffer_out;
						uart3_out_len = uart3_out_len_A = buffer_len;
						uart3_out_status = UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO;
					}
					else // if(uart3_out_status == UART_OUT_STATUS_NONE)
					{
						uart3_out = uart3_out_A = buffer_out;
						uart3_out_len = uart3_out_len_A = buffer_len;
						uart3_out_idx = 0;
						uart3_out_status = UART_OUT_STATUS_A_ESCRIBIENDO;
					}

					return TRUE;
				}
			#endif
		// ************ //

		// *** ESCRIBIENDO *** //
			#if (USE_UART0)
				Bool uart0_escribiendo()
				{
					return (uart0_out_status != UART_OUT_STATUS_NONE);
				}
			#endif

			#if (USE_UART1)
				Bool uart1_escribiendo()
				{
					return (uart1_out_status != UART_OUT_STATUS_NONE);
				}
			#endif

			#if (USE_UART2)
				Bool uart2_escribiendo()
				{
					return (uart2_out_status != UART_OUT_STATUS_NONE);
				}
			#endif

			#if (USE_UART3)
				Bool uart3_escribiendo()
				{
					return (uart3_out_status != UART_OUT_STATUS_NONE);
				}
			#endif
		// ******************* //
	#endif
// ***************** //
