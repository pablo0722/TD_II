/*
 * uart_irq.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "uart_header.h"


#if USE_UART
	#if USE_UART0
		void UART0_IRQHandler(void)
		{
			Chip_UART_IRQRBHandler(LPC_UART0, &rxring0, &txring0);
		}
	#endif

	#if USE_UART1
		void UART1_IRQHandler(void)
		{
			Chip_UART_IRQRBHandler(LPC_UART1, &rxring1, &txring1);
		}
	#endif

	#if USE_UART2
		void UART2_IRQHandler(void)
		{
			Chip_UART_IRQRBHandler(LPC_UART2, &rxring2, &txring2);
		}
	#endif

	#if USE_UART3
		void UART3_IRQHandler(void)
		{
			Chip_UART_IRQRBHandler(LPC_UART3, &rxring3, &txring3);
		}
	#endif
#endif
