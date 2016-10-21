/*
 * uart_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "uart_header.h"



	#if USE_UART0
		#define RX_RING0_P &rxring0
	#else
		#define RX_RING0_P NULL
	#endif
	#if USE_UART1
		#define RX_RING1_P &rxring1
	#else
		#define RX_RING1_P NULL
	#endif
	#if USE_UART2
		#define RX_RING2_P &rxring2
	#else
		#define RX_RING2_P NULL
	#endif
	#if USE_UART3
		#define RX_RING3_P &rxring3
	#else
		#define RX_RING3_P NULL
	#endif


	#if USE_UART0
		#define TX_RING0_P &txring0
	#else
		#define TX_RING0_P NULL
	#endif
	#if USE_UART1
		#define TX_RING1_P &txring1
	#else
		#define TX_RING1_P NULL
	#endif
	#if USE_UART2
		#define TX_RING2_P &txring2
	#else
		#define TX_RING2_P NULL
	#endif
	#if USE_UART3
		#define TX_RING3_P &txring3
	#else
		#define TX_RING3_P NULL
	#endif


	#if USE_UART0
		#define RX_BUFF0_P &rxbuff0
	#else
		#define RX_BUFF0_P NULL
	#endif
	#if USE_UART1
		#define RX_BUFF1_P &rxbuff1
	#else
		#define RX_BUFF1_P NULL
	#endif
	#if USE_UART2
		#define RX_BUFF2_P &rxbuff2
	#else
		#define RX_BUFF2_P NULL
	#endif
	#if USE_UART3
		#define RX_BUFF3_P &rxbuff3
	#else
		#define RX_BUFF3_P NULL
	#endif


	#if USE_UART0
		#define TX_BUFF0_P &txbuff0
	#else
		#define TX_BUFF0_P NULL
	#endif
	#if USE_UART1
		#define TX_BUFF1_P &txbuff1
	#else
		#define TX_BUFF1_P NULL
	#endif
	#if USE_UART2
		#define TX_BUFF2_P &txbuff2
	#else
		#define TX_BUFF2_P NULL
	#endif
	#if USE_UART3
		#define TX_BUFF3_P &txbuff3
	#else
		#define TX_BUFF3_P NULL
	#endif



#define BAUDRATE_UART(n)	(n==0?UART0_BAUDRATE:	(n==1?UART1_BAUDRATE:	(n==2?UART2_BAUDRATE:	UART3_BAUDRATE)))
#define SRB_SIZE_UART(n)	(n==0?UART0_SRB_SIZE:	(n==1?UART1_SRB_SIZE:	(n==2?UART2_SRB_SIZE:	UART3_SRB_SIZE)))
#define RRB_SIZE_UART(n)	(n==0?UART0_RRB_SIZE:	(n==1?UART1_RRB_SIZE:	(n==2?UART2_RRB_SIZE:	UART3_RRB_SIZE)))
#define MODE_UART(n)		(n==0?UART0_MODE:		(n==1?UART1_MODE:		(n==2?UART2_MODE:		UART3_MODE)))
#define LPC_UART(n)			(n==0?LPC_UART0:		(n==1?LPC_UART1:		(n==2?LPC_UART2:		LPC_UART3)))
#define RX_RING(n)			(n==0?RX_RING0_P:		(n==1?RX_RING1_P:		(n==2?RX_RING2_P:		RX_RING3_P)))
#define TX_RING(n)			(n==0?TX_RING0_P:		(n==1?TX_RING1_P:		(n==2?TX_RING2_P:		TX_RING3_P)))
#define RX_BUFF(n)			(n==0?RX_BUFF0_P:		(n==1?RX_BUFF1_P:		(n==2?RX_BUFF2_P:		RX_BUFF3_P)))
#define TX_BUFF(n)			(n==0?TX_BUFF0_P:		(n==1?TX_BUFF1_P:		(n==2?TX_BUFF2_P:		TX_BUFF3_P)))
#define IRQn_UART(n)		(n==0?UART0_IRQn:		(n==1?UART1_IRQn:		(n==2?UART2_IRQn:		UART3_IRQn)))


#if USE_UART
	void init_uartN(uint8_t uart_num)
	{
		#if DEBUG_MODE
			printf("[info] init Uart%d: \r\n", uart_num);
			printf("\t Baudrate: %d \r\n", BAUDRATE_UART(uart_num));
			printf("\t SendBuffSize: %d \r\n", SRB_SIZE_UART(uart_num));
			printf("\t RecvBuffSize: %d \r\n", RRB_SIZE_UART(uart_num));
		#endif

		if(uart_num==0)
		{
			Chip_IOCON_PinMux(LPC_IOCON, UART0_TX);
			Chip_IOCON_PinMux(LPC_IOCON, UART0_RX);
		}
		else if(uart_num==1)
		{
			Chip_IOCON_PinMux(LPC_IOCON, UART1_TX);
			Chip_IOCON_PinMux(LPC_IOCON, UART1_RX);
		}
		else if(uart_num==2)
		{
			Chip_IOCON_PinMux(LPC_IOCON, UART2_TX);
			Chip_IOCON_PinMux(LPC_IOCON, UART2_RX);
		}
		else
		{
			Chip_IOCON_PinMux(LPC_IOCON, UART3_TX);
			Chip_IOCON_PinMux(LPC_IOCON, UART3_RX);
		}

		Board_UART_Init((uint32_t)LPC_UART(uart_num), BAUDRATE_UART(uart_num));

		// Before using the ring buffers, initialize them using the ring
		// buffer init function
		RingBuffer_Init(RX_RING(uart_num), RX_BUFF(uart_num), 1, SRB_SIZE_UART(uart_num));
		RingBuffer_Init(TX_RING(uart_num), TX_BUFF(uart_num), 1, RRB_SIZE_UART(uart_num));

		// Enable receive data and line status interrupt
		Chip_UART_IntEnable(LPC_UART(uart_num), (UART_IER_RBRINT | UART_IER_RLSINT));

		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(IRQn_UART(uart_num), 1);
		NVIC_EnableIRQ(IRQn_UART(uart_num));

		const char Uart_init_msg[] = "\r\nHola mundo:\r\n";

		/* Envia mensaje inicial por UART*/
		Chip_UART_SendRB(LPC_UART(uart_num), TX_RING(uart_num), Uart_init_msg, sizeof(Uart_init_msg));
	}

	void uart_init()
	{
		#if USE_UART0
			init_uartN(0);
		#endif
		#if USE_UART1
			init_uartN(1);
		#endif
		#if USE_UART2
			init_uartN(2);
		#endif
		#if USE_UART3
			init_uartN(3);
		#endif
	}
#endif
