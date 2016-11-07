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
		#if (USE_UART0)
			void 		uart0_leer(uint8_t *buffer_in_A, uint8_t *buffer_in_B, uint32_t buffer_len);
			uint8_t*	uart0_puedo_procesar();		// Termino de leer un buffer
			void 		uart0_proceso_listo();		// Llamar cuando se termine de procesar un buffer (permite seguir leyendo)
			Bool 		uart0_escribir(const uint8_t *buffer_out, uint32_t buffer_len);
			Bool 		uart0_escribiendo();		// Determina si se encuentra escribiendo algo
		#endif

		#if (USE_UART1)
			void 		uart1_leer(uint8_t *buffer_in_A, uint8_t *buffer_in_B, uint32_t buffer_len);
			uint8_t*	uart1_puedo_procesar();		// Termino de leer un buffer
			void 		uart1_proceso_listo();		// Llamar cuando se termine de procesar un buffer (permite seguir leyendo)
			Bool 		uart1_escribir(const uint8_t *buffer_out, uint32_t buffer_len);
			Bool 		uart1_escribiendo();		// Determina si se encuentra escribiendo algo
		#endif

		#if (USE_UART2)
			void 		uart2_leer(uint8_t *buffer_in_A, uint8_t *buffer_in_B, uint32_t buffer_len);
			uint8_t*	uart2_puedo_procesar();		// Termino de leer un buffer
			void 		uart2_proceso_listo();		// Llamar cuando se termine de procesar un buffer (permite seguir leyendo)
			Bool 		uart2_escribir(const uint8_t *buffer_out, uint32_t buffer_len);
			Bool 		uart2_escribiendo();		// Determina si se encuentra escribiendo algo
		#endif

		#if (USE_UART3)
			void 		uart3_leer(uint8_t *buffer_in_A, uint8_t *buffer_in_B, uint32_t buffer_len);
			uint8_t*	uart3_puedo_procesar();		// Termino de leer un buffer
			void 		uart3_proceso_listo();		// Llamar cuando se termine de procesar un buffer (permite seguir leyendo)
			bool 		uart3_escribir(const uint8_t *buffer_out, uint32_t buffer_len);
			Bool 		uart3_escribiendo();		// Determina si se encuentra escribiendo algo
		#endif
	#endif
// ****************************** //



// ***************** DEFINES ***************** //
	#if USE_UART
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

			// *** PINOUT DE UART
			#define UART0_TX_PIN_P0_2	0, 2, MD_PLN, IOCON_FUNC1
			#define UART0_RX_PIN_P0_3	0, 3, MD_PLN, IOCON_FUNC1
		#define UART0_TX_PIN	UART0_TX_PIN_P0_2
		#define UART0_RX_PIN	UART0_RX_PIN_P0_3

			#define UART1_TX_PIN_P0_15	0, 15, MD_PLN, IOCON_FUNC1
			#define UART1_TX_PIN_P2_0	2, 0, MD_PLN, IOCON_FUNC2
			#define UART1_RX_PIN_P0_16	0, 16, MD_PLN, IOCON_FUNC1
			#define UART1_RX_PIN_P2_1	2, 1, MD_PLN, IOCON_FUNC2
		#define UART1_TX_PIN	UART1_TX_PIN_P0_15
		#define UART1_RX_PIN	UART1_RX_PIN_P0_16

			#define UART2_TX_PIN_P0_10	0, 10, MD_PLN, IOCON_FUNC1
			#define UART2_TX_PIN_P2_8	2, 8, MD_PLN, IOCON_FUNC2
			#define UART2_RX_PIN_P0_11	0, 11, MD_PLN, IOCON_FUNC1
		#define UART2_TX_PIN	UART2_TX_PIN_P0_10
		#define UART2_RX_PIN	UART2_RX_PIN_P0_11

			#define UART3_TX_PIN_P0_0	0, 0, MD_PLN, IOCON_FUNC2
			#define UART3_TX_PIN_P0_25	0, 25, MD_PLN, IOCON_FUNC3
			#define UART3_RX_PIN_P0_1	0, 1, MD_PLN, IOCON_FUNC2
			#define UART3_RX_PIN_P0_26	0, 26, MD_PLN, IOCON_FUNC3
		#define UART3_TX_PIN	UART3_TX_PIN_P0_0
		#define UART3_RX_PIN	UART3_RX_PIN_P0_1
	#endif
// ******************************************* //


// ************* INICIALIZACION ************* //
	#include "uart_init.h"
// ****************************************** //


#endif /* UART_HEADER_H_ */
