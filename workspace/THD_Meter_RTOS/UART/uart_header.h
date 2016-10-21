/*
 * uart_header.h
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */

#ifndef UART_HEADER_H_
#define UART_HEADER_H_



	#include "header.h"


// ********* MODO DE USO ********** //
//
// *** UTILIDADES.H
// 		Se debe poner USE_UART en ON para poder utilizar las UARTs
// 		Se debe poner USE_UARTN en ON para definir que UARTs utilizar
// 		Se puede poner UARTN_TRANSMIT en UART_TRANSMIT_FFT para transmitir automaticamente por UART la fft realizada (ver FFT/fft_header.h)
// 		Se puede poner UARTN_TRANSMIT en UART_TRANSMIT_LOOPBACK para transmitir lo mismo que leyo (loopback)
// 		Se puede poner UARTN_TRANSMIT en UART_TRANSMIT_NONE para NO transmitir nada automaticamente (se puede transmitir manualmente con Chip_UART_SendRB(...))
//
// *** HEADER
// 		en UARTN_SRB_SIZE y UARTN_RRB_SIZE se especifica el tamanio de los ring buffers de las uarts.
// 		en UARTN_BAUDRATE se especifica el baudrate de las uarts.
// 		en UARTN_TX y UARTN_RX se especifican los pines de transmision y recepcion respectivamente.
//
// *** MAIN
// 		primero se debe esperar a que el flag 'uart0_rx_status' sea igual a UART_STATUS_LEIDO (que indica que ya se leyo un dato),
// 		se puede guardar el valor leido que se encuentra en 'uart0_in',
//		una vez utilizado el valor de 'uart0_in' (guardado o descartado), se debe poner 'uart0_rx_status' a UART_STATUS_EMPTY (para que se pueda leer otro dato),
//
// ******************************** //



// ********* FUNCIONES ********** //
	#if USE_UART
		void uart_init();
		void main_uart();
	#endif
// ****************************** //



// ***************** DEFINES ***************** //
	#if USE_UART
			// *** TAMANIOS DE RING BUFFERS
		#define UART0_SRB_SIZE 	16	// Send ring buffer
		#define UART0_RRB_SIZE 	16	// Receive ring buffer
		#define UART1_SRB_SIZE 	16	// Send ring buffer
		#define UART1_RRB_SIZE 	16	// Receive ring buffer
		#define UART2_SRB_SIZE 	16	// Send ring buffer
		#define UART2_RRB_SIZE 	16	// Receive ring buffer
		#define UART3_SRB_SIZE 	16	// Send ring buffer
		#define UART3_RRB_SIZE 	16	// Receive ring buffer

			// *** BAUDRATES DE UART
			#define UART_BAUDRATE_9600	9600
			#define UART_BAUDRATE_19200	19200
			#define UART_BAUDRATE_38400	38400
			#define UART_BAUDRATE_57600	57600
			#define UART_BAUDRATE_115200 115200
		#define UART0_BAUDRATE 	UART_BAUDRATE_9600	// Baudrate de UART0
		#define UART1_BAUDRATE 	UART_BAUDRATE_9600	// Baudrate de UART1
		#define UART2_BAUDRATE 	UART_BAUDRATE_9600	// Baudrate de UART2
		#define UART3_BAUDRATE 	UART_BAUDRATE_9600	// Baudrate de UART3

			// *** estados del flag 'uartN_rx_status'
			#define UART_STATUS_EMPTY	0	// No hay nada leido o algo ya leido
			#define UART_STATUS_LEIDO	1	// Hay algo leido pero aun NO usado

			// *** PINOUT DE UART
			#define UART0_TX_P0_2	0, 2, MD_PLN, IOCON_FUNC1
			#define UART0_RX_P0_3	0, 3, MD_PLN, IOCON_FUNC1
		#define UART0_TX	UART0_TX_P0_2
		#define UART0_RX	UART0_RX_P0_3

			#define UART1_TX_P0_15	0, 15, MD_PLN, IOCON_FUNC1
			#define UART1_TX_P2_0	2, 0, MD_PLN, IOCON_FUNC2
			#define UART1_RX_P0_16	0, 16, MD_PLN, IOCON_FUNC1
			#define UART1_RX_P2_1	2, 1, MD_PLN, IOCON_FUNC2
		#define UART1_TX	UART1_TX_P0_15
		#define UART1_RX	UART1_RX_P0_16

			#define UART2_TX_P0_10	0, 10, MD_PLN, IOCON_FUNC1
			#define UART2_TX_P2_8	2, 8, MD_PLN, IOCON_FUNC2
			#define UART2_RX_P0_11	0, 11, MD_PLN, IOCON_FUNC1
		#define UART2_TX	UART2_TX_P0_10
		#define UART2_RX	UART2_RX_P0_11

			#define UART3_TX_P0_0	0, 0, MD_PLN, IOCON_FUNC2
			#define UART3_TX_P0_25	0, 25, MD_PLN, IOCON_FUNC3
			#define UART3_RX_P0_1	0, 1, MD_PLN, IOCON_FUNC2
			#define UART3_RX_P0_26	0, 26, MD_PLN, IOCON_FUNC3
		#define UART3_TX	UART3_TX_P0_0
		#define UART3_RX	UART3_RX_P0_1
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_UART
		#if USE_UART0
			extern volatile uint8_t uart0_in;						// Senal de entrada.
		#endif
		#if USE_UART1
			extern volatile uint8_t uart1_in;						// Senal de entrada.
		#endif
		#if USE_UART2
			extern volatile uint8_t uart2_in;						// Senal de entrada.
		#endif
		#if USE_UART3
			extern volatile uint8_t uart3_in;						// Senal de entrada.
		#endif

			// Transmit and receive buffers
		#if USE_UART0
			extern RINGBUFF_T rxbuff0[UART0_RRB_SIZE], txbuff0[UART0_SRB_SIZE];
		#endif
		#if USE_UART1
			extern RINGBUFF_T rxbuff1[UART1_RRB_SIZE], txbuff1[UART1_SRB_SIZE];
		#endif
		#if USE_UART2
			extern RINGBUFF_T rxbuff2[UART2_RRB_SIZE], txbuff2[UART2_SRB_SIZE];
		#endif
		#if USE_UART3
			extern RINGBUFF_T rxbuff3[UART3_RRB_SIZE], txbuff3[UART3_SRB_SIZE];
		#endif

			// Transmit and receive ring buffers
		#if USE_UART0
			extern RINGBUFF_T txring0, rxring0;
		#endif
		#if USE_UART1
			extern RINGBUFF_T txring1, rxring1;
		#endif
		#if USE_UART2
			extern RINGBUFF_T txring2, rxring2;
		#endif
		#if USE_UART3
			extern RINGBUFF_T txring3, rxring3;
		#endif

			// Estado de recepcion de la UART
		#if USE_UART0
			extern uint8_t uart0_rx_status;
		#endif
		#if USE_UART1
			extern uint8_t uart1_rx_status;
		#endif
		#if USE_UART2
			extern uint8_t uart2_rx_status;
		#endif
		#if USE_UART3
			extern uint8_t uart3_rx_status;
		#endif

	#endif
// ********************************************** //


#endif /* UART_HEADER_H_ */
