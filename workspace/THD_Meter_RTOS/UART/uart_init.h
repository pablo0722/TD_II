/*
 * uart_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"


#if USE_UART
	#if (USE_UART0)
		STATIC INLINE void init_uart0()
		{
			#if DEBUG_MODE
				printf("[info] init Uart0: \r\n");
				printf("\t Baudrate: %d \r\n", UART0_BAUDRATE);
			#endif

			Chip_IOCON_PinMux(LPC_IOCON, UART0_TX_PIN);
			Chip_IOCON_PinMux(LPC_IOCON, UART0_RX_PIN);

			Board_UART_Init((uint32_t)LPC_UART0, UART0_BAUDRATE);

			// Enable receive data and line status interrupt
			Chip_UART_IntEnable(LPC_UART0, (UART_IER_RBRINT | UART_IER_THREINT | UART_IER_RLSINT));

			/* preemption = 1, sub-priority = 1 */
			NVIC_SetPriority(UART0_IRQn, 1);
			NVIC_EnableIRQ(UART0_IRQn);

			const uint8_t Uart_init_msg[] = "\r\nInit:\r\n";

			/* Envia mensaje inicial por UART*/
			uart0_escribir(Uart_init_msg, sizeof(Uart_init_msg));

			while(uart0_escribiendo());	// Esperar a que se termine de escribir para poder liberar la memoria de 'Uart_init_msg'
		}
	#endif

	#if (USE_UART1)
		STATIC INLINE void init_uart1()
		{
			#if DEBUG_MODE
				printf("[info] init Uart1: \r\n");
				printf("\t Baudrate: %d \r\n", UART1_BAUDRATE);
			#endif

			Chip_IOCON_PinMux(LPC_IOCON, UART1_TX_PIN);
			Chip_IOCON_PinMux(LPC_IOCON, UART1_RX_PIN);

			Board_UART_Init((uint32_t)LPC_UART1, UART1_BAUDRATE);

			// Enable receive data and line status interrupt
			Chip_UART_IntEnable(LPC_UART1, (UART_IER_RBRINT | UART_IER_THREINT | UART_IER_RLSINT));

			/* preemption = 1, sub-priority = 1 */
			NVIC_SetPriority(UART1_IRQn, 1);
			NVIC_EnableIRQ(UART1_IRQn);

			const uint8_t Uart_init_msg[] = "\r\nInit:\r\n";

			/* Envia mensaje inicial por UART*/
			uart1_escribir(Uart_init_msg, sizeof(Uart_init_msg));

			while(uart1_escribiendo());	// Esperar a que se termine de escribir para poder liberar la memoria de 'Uart_init_msg'
		}
	#endif

	#if (USE_UART2)
		STATIC INLINE void init_uart2()
		{
			#if DEBUG_MODE
				printf("[info] init Uart2: \r\n");
				printf("\t Baudrate: %d \r\n", UART2_BAUDRATE);
			#endif

			Chip_IOCON_PinMux(LPC_IOCON, UART2_TX_PIN);
			Chip_IOCON_PinMux(LPC_IOCON, UART2_RX_PIN);

			Board_UART_Init((uint32_t)LPC_UART2, UART2_BAUDRATE);

			// Enable receive data and line status interrupt
			Chip_UART_IntEnable(LPC_UART2, (UART_IER_RBRINT | UART_IER_THREINT | UART_IER_RLSINT));

			/* preemption = 1, sub-priority = 1 */
			NVIC_SetPriority(UART2_IRQn, 1);
			NVIC_EnableIRQ(UART2_IRQn);

			const uint8_t Uart_init_msg[] = "\r\nInit:\r\n";

			/* Envia mensaje inicial por UART*/
			uart2_escribir(Uart_init_msg, sizeof(Uart_init_msg));

			while(uart2_escribiendo());	// Esperar a que se termine de escribir para poder liberar la memoria de 'Uart_init_msg'
		}
	#endif

	#if (USE_UART3)
		STATIC INLINE void init_uart3()
		{
			#if DEBUG_MODE
				printf("[info] init Uart3: \r\n");
				printf("\t Baudrate: %d \r\n", UART3_BAUDRATE);
			#endif

			Chip_IOCON_PinMux(LPC_IOCON, UART3_TX_PIN);
			Chip_IOCON_PinMux(LPC_IOCON, UART3_RX_PIN);

			Board_UART_Init((uint32_t)LPC_UART3, UART3_BAUDRATE);

			// Enable receive data and line status interrupt
			Chip_UART_IntEnable(LPC_UART3, (UART_IER_RBRINT | UART_IER_THREINT | UART_IER_RLSINT));

			/* preemption = 1, sub-priority = 1 */
			NVIC_SetPriority(UART3_IRQn, 1);
			NVIC_EnableIRQ(UART3_IRQn);

			const uint8_t Uart_init_msg[] = "\r\nInit:\r\n";

			/* Envia mensaje inicial por UART*/
			uart3_escribir(Uart_init_msg, sizeof(Uart_init_msg));

			while(uart3_escribiendo());	// Esperar a que se termine de escribir para poder liberar la memoria de 'Uart_init_msg'
		}
	#endif

	STATIC INLINE  void uart_init()
	{
		#if USE_UART0
			init_uart0();
		#endif
		#if USE_UART1
			init_uart1();
		#endif
		#if USE_UART2
			init_uart2();
		#endif
		#if USE_UART3
			init_uart3();
		#endif
	}
#endif
