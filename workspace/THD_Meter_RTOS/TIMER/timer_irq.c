/*
 * timer_irq.c
 *
 *  Created on: 5 de nov. de 2016
 *      Author: Pablo
 */


#include "header.h"


#define CHANNEL_0	0
#define CHANNEL_1	1


void TIMER0_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER0, CHANNEL_1))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER0, CHANNEL_1);
	}
}

void TIMER1_IRQHandler( void )
{
	if( Chip_TIMER_MatchPending(LPC_TIMER1, CHANNEL_0) )
	{
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, BL);
		Chip_TIMER_ClearMatch(LPC_TIMER1, CHANNEL_0);
	}
	if( Chip_TIMER_MatchPending(LPC_TIMER1, CHANNEL_1) )
	{

		Chip_GPIO_SetPinOutLow(LPC_GPIO, BL);
		Chip_TIMER_ClearMatch(LPC_TIMER1, CHANNEL_1);
	}
}
