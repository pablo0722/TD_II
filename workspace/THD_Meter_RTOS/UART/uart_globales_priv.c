/*
 * uart_global.h
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"
#include "uart_header_priv.h"


// *** VARIABLES GLOBALES PRIVADAS *** //
	// *** SENIAL DE ENTRADA *** //
		#if USE_UART0
			volatile uint8_t *uart0_in = NULL;
			volatile uint8_t *uart0_in_A = NULL;
			volatile uint8_t *uart0_in_B = NULL;
			volatile uint32_t uart0_in_len = 0;
			volatile uint32_t uart0_in_idx = 0;
			volatile int8_t uart0_in_status = UART_IN_STATUS_NONE;
		#endif
		#if USE_UART1
			volatile uint8_t *uart1_in = NULL;
			volatile uint8_t *uart1_in_A = NULL;
			volatile uint8_t *uart1_in_B = NULL;
			volatile uint32_t uart1_in_len = 0;
			volatile uint32_t uart1_in_idx = 0;
			volatile int8_t uart1_in_status = UART_IN_STATUS_NONE;
		#endif
		#if USE_UART2
			volatile uint8_t *uart2_in = NULL;
			volatile uint8_t *uart2_in_A = NULL;
			volatile uint8_t *uart2_in_B = NULL;
			volatile uint32_t uart2_in_len = 0;
			volatile uint32_t uart2_in_idx = 0;
			volatile int8_t uart2_in_status = UART_IN_STATUS_NONE;
		#endif
		#if USE_UART3
			volatile uint8_t *uart3_in = NULL;
			volatile uint8_t *uart3_in_A = NULL;
			volatile uint8_t *uart3_in_B = NULL;
			volatile uint32_t uart3_in_len = 0;
			volatile uint32_t uart3_in_idx = 0;
			volatile int8_t uart3_in_status = UART_IN_STATUS_NONE;
		#endif
	// ************************* //

	// *** SENIAL DE SALIDA *** //
		#if USE_UART0
			const uint8_t * volatile uart0_out = NULL;
			const uint8_t * volatile uart0_out_A = NULL;
			const uint8_t * volatile uart0_out_B = NULL;
			volatile uint32_t uart0_out_len = 0;
			volatile uint32_t uart0_out_len_A = 0;
			volatile uint32_t uart0_out_len_B = 0;
			volatile uint32_t uart0_out_idx = 0;
			volatile int8_t uart0_out_status = UART_OUT_STATUS_NONE;
		#endif
		#if USE_UART1
			const uint8_t * volatile uart1_out = NULL;
			const uint8_t * volatile uart1_out_A = NULL;
			const uint8_t * volatile uart1_out_B = NULL;
			volatile uint32_t uart1_out_len = 0;
			volatile uint32_t uart1_out_len_A = 0;
			volatile uint32_t uart1_out_len_B = 0;
			volatile uint32_t uart1_out_idx = 0;
			volatile int8_t uart1_out_status = UART_OUT_STATUS_NONE;
		#endif
		#if USE_UART2
			const uint8_t * volatile uart2_out = NULL;
			const uint8_t * volatile uart2_out_A = NULL;
			const uint8_t * volatile uart2_out_B = NULL;
			volatile uint32_t uart2_out_len = 0;
			volatile uint32_t uart2_out_len_A = 0;
			volatile uint32_t uart2_out_len_B = 0;
			volatile uint32_t uart2_out_idx = 0;
			volatile int8_t uart2_out_status = UART_OUT_STATUS_NONE;
		#endif
		#if USE_UART3
			const uint8_t * volatile uart3_out = NULL;
			const uint8_t * volatile uart3_out_A = NULL;
			const uint8_t * volatile uart3_out_B = NULL;
			volatile uint32_t uart3_out_len = 0;
			volatile uint32_t uart3_out_len_A = 0;
			volatile uint32_t uart3_out_len_B = 0;
			volatile uint32_t uart3_out_idx = 0;
			volatile int8_t uart3_out_status = UART_OUT_STATUS_NONE;
		#endif
	// ************************ //
// ************************* //
