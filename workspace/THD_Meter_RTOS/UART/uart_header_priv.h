/*
 * uart_header_priv.h
 *
 *  Created on: 7 de nov. de 2016
 *      Author: Pablo
 */

#ifndef UART_HEADER_PRIV_H_
#define UART_HEADER_PRIV_H_


// *** DEFINES PRIVADAS *** //
	// *** LECTURA *** //
		#define UART_IN_STATUS_A_LISTO					-3	// A esta listo para procesar. No lee nada, espera a que se procece A
		#define UART_IN_STATUS_B_LISTO					-2	// B esta listo para procesar. No lee nada, espera a que se procece B
		#define UART_IN_STATUS_NONE						-1
		#define UART_IN_STATUS_A_LEYENDO				0	// Solamente leyendo A
		#define UART_IN_STATUS_A_LEYENDO_B_LISTO		1	// Leyendo A, el B esta listo para procesar
		#define UART_IN_STATUS_B_LEYENDO				2	// Solamente leyendo B
		#define UART_IN_STATUS_B_LEYENDO_A_LISTO		3	// Leyendo B, el A esta listo para procesar
	// *************** //

	// *** ESCRITURA *** //
		#define UART_OUT_STATUS_NONE					-1
		#define UART_OUT_STATUS_A_ESCRIBIENDO			0	// Solamente escribiendo A
		#define UART_OUT_STATUS_A_ESCRIBIENDO_B_LISTO	1	// Escribiendo A, el B esta listo para escribir luego
		#define UART_OUT_STATUS_B_ESCRIBIENDO			2	// Solamente escribiendo B
		#define UART_OUT_STATUS_B_ESCRIBIENDO_A_LISTO	3	// Escribiendo B, el A esta listo para escribir luego
	// ***************** //
// ********************************** //


// *** VARIABLES GLOBALES PRIVADAS *** //
	// *** SENIAL DE ENTRADA *** //
		#if USE_UART0
			extern volatile uint8_t *uart0_in;
			extern volatile uint8_t *uart0_in_A;
			extern volatile uint8_t *uart0_in_B;
			extern volatile uint32_t uart0_in_len;
			extern volatile uint32_t uart0_in_idx;
			extern volatile int8_t uart0_in_status;
		#endif
		#if USE_UART1
			extern volatile uint8_t *uart1_in;
			extern volatile uint8_t *uart1_in_A;
			extern volatile uint8_t *uart1_in_B;
			extern volatile uint32_t uart1_in_len;
			extern volatile uint32_t uart1_in_idx;
			extern volatile int8_t uart1_in_status;
		#endif
		#if USE_UART2
			extern volatile uint8_t *uart2_in;
			extern volatile uint8_t *uart2_in_A;
			extern volatile uint8_t *uart2_in_B;
			extern volatile uint32_t uart2_in_len;
			extern volatile uint32_t uart2_in_idx;
			extern volatile int8_t uart2_in_status;
		#endif
		#if USE_UART3
			extern volatile uint8_t *uart3_in;
			extern volatile uint8_t *uart3_in_A;
			extern volatile uint8_t *uart3_in_B;
			extern volatile uint32_t uart3_in_len;
			extern volatile uint32_t uart3_in_idx;
			extern volatile int8_t uart3_in_status;
		#endif
	// ************************* //

	// *** SENIAL DE SALIDA *** //
		#if USE_UART0
			extern const uint8_t * volatile uart0_out;
			extern const uint8_t * volatile uart0_out_A;
			extern const uint8_t * volatile uart0_out_B;
			extern volatile uint32_t uart0_out_len;
			extern volatile uint32_t uart0_out_len_A;
			extern volatile uint32_t uart0_out_len_B;
			extern volatile uint32_t uart0_out_idx;
			extern volatile int8_t uart0_out_status;
		#endif
		#if USE_UART1
			extern const uint8_t * volatile uart1_out;
			extern const uint8_t * volatile uart1_out_A;
			extern const uint8_t * volatile uart1_out_B;
			extern volatile uint32_t uart1_out_len;
			extern volatile uint32_t uart1_out_len_A;
			extern volatile uint32_t uart1_out_len_B;
			extern volatile uint32_t uart1_out_idx;
			extern volatile int8_t uart1_out_status;
		#endif
		#if USE_UART2
			extern const uint8_t * volatile uart2_out;
			extern const uint8_t * volatile uart2_out_A;
			extern const uint8_t * volatile uart2_out_B;
			extern volatile uint32_t uart2_out_len;
			extern volatile uint32_t uart2_out_len_A;
			extern volatile uint32_t uart2_out_len_B;
			extern volatile uint32_t uart2_out_idx;
			extern volatile int8_t uart2_out_status;
		#endif
		#if USE_UART3
			extern const uint8_t * volatile uart3_out;
			extern const uint8_t * volatile uart3_out_A;
			extern const uint8_t * volatile uart3_out_B;
			extern volatile uint32_t uart3_out_len;
			extern volatile uint32_t uart3_out_len_A;
			extern volatile uint32_t uart3_out_len_B;
			extern volatile uint32_t uart3_out_idx;
			extern volatile int8_t uart3_out_status;
		#endif
	// ************************ //
// ************************* //


#endif /* UART_HEADER_PRIV_H_ */
