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
	STATIC INLINE void init_uart0()
	{
		#if DEBUG_MODE
			printf("[info] init Uart0: \r\n");
			printf("\t Baudrate: %d \r\n", UART0_BAUDRATE);
			printf("\t SendBuffSize: %d \r\n", UART0_SRB_SIZE);
			printf("\t RecvBuffSize: %d \r\n", UART0_RRB_SIZE);
		#endif

		Chip_IOCON_PinMux(LPC_IOCON, UART0_TX);
		Chip_IOCON_PinMux(LPC_IOCON, UART0_RX);

		Board_UART_Init((uint32_t)LPC_UART0, UART0_BAUDRATE);

		// Before using the ring buffers, initialize them using the ring
		// buffer init function
		RingBuffer_Init(RX_RING0_P, RX_BUFF0_P, 1, UART0_RRB_SIZE);
		RingBuffer_Init(TX_RING0_P, TX_BUFF0_P, 1, UART0_SRB_SIZE);

		// Enable receive data and line status interrupt
		Chip_UART_IntEnable(LPC_UART0, (UART_IER_RBRINT | UART_IER_RLSINT));

		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(UART0_IRQn, 1);
		NVIC_EnableIRQ(UART0_IRQn);

		const char Uart_init_msg[] = "\r\nInit:\r\n";

		/* Envia mensaje inicial por UART*/
		Chip_UART_SendRB(LPC_UART0, TX_RING0_P, Uart_init_msg, sizeof(Uart_init_msg));
	}

	STATIC INLINE  void uart_init()
	{
		#if USE_UART0
			init_uart0();
		#endif
		#if USE_UART1
			init_uart1;
		#endif
		#if USE_UART2
			init_uart2;
		#endif
		#if USE_UART3
			init_uart3;
		#endif
	}
#endif
