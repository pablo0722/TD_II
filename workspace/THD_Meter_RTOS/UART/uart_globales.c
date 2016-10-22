/*
 * uart_global.h
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "uart_header.h"


#if USE_UART
		#if USE_UART0
			volatile uint8_t uart0_in;						// Senal de entrada.
		#endif
		#if USE_UART1
			volatile uint8_t uart1_in;						// Senal de entrada.
		#endif
		#if USE_UART2
			volatile uint8_t uart2_in;						// Senal de entrada.
		#endif
		#if USE_UART3
			volatile uint8_t uart3_in;						// Senal de entrada.
		#endif


			// Transmit and receive buffers
		#if USE_UART0
			uint8_t rxbuff0[UART0_RRB_SIZE], txbuff0[UART0_SRB_SIZE];
		#endif
		#if USE_UART1
			uint8_t rxbuff1[UART1_RRB_SIZE], txbuff1[UART1_SRB_SIZE];
		#endif
		#if USE_UART2
			uint8_t rxbuff2[UART2_RRB_SIZE], txbuff2[UART2_SRB_SIZE];
		#endif
		#if USE_UART3
			uint8_t rxbuff3[UART3_RRB_SIZE], txbuff3[UART3_SRB_SIZE];
		#endif


			// Transmit and receive ring buffers
		#if USE_UART0
			RINGBUFF_T txring0, rxring0;
		#endif
		#if USE_UART1
			RINGBUFF_T txring1, rxring1;
		#endif
		#if USE_UART2
			RINGBUFF_T txring2, rxring2;
		#endif
		#if USE_UART3
			RINGBUFF_T txring3, rxring3;
		#endif


			// Estado de recepcion de UART
		#if USE_UART0
			uint8_t uart0_rx_status = UART_STATUS_EMPTY;
		#endif
		#if USE_UART1
			uint8_t uart1_rx_status = UART_STATUS_EMPTY;
		#endif
		#if USE_UART2
			uint8_t uart2_rx_status = UART_STATUS_EMPTY;
		#endif
		#if USE_UART3
			uint8_t uart3_rx_status = UART_STATUS_EMPTY;
		#endif
#endif
