/*
 * timer_irq.c
 *
 *  Created on: 5 de nov. de 2016
 *      Author: Pablo
 */


#include "header.h"


void TIMER0_IRQHandler(void)
{
	static const uint8_t channel_1 = 1;

	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	//Verificamos para el Timer 0, cual fue la fuente de interrupción.
	//En este ejemplo, la única habilitada es Match 1.

	if (Chip_TIMER_MatchPending(LPC_TIMER0, channel_1))
	{
		// 'Give' the semaphore to unblock the task.
		xSemaphoreGiveFromISR(sem_timer0_match1, &xHigherPriorityTaskWoken );

		/* Giving the semaphore may have unblocked a task - if it did and the
		unblocked task has a priority equal to or above the currently executing
		task then xHigherPriorityTaskWoken will have been set to pdTRUE and
		portEND_SWITCHING_ISR() will force a context switch to the newly unblocked
		higher priority task.

		NOTE: The syntax for forcing a context switch within an ISR varies between
		FreeRTOS ports.  The portEND_SWITCHING_ISR() macro is provided as part of
		the Cortex M3 port layer for this purpose.  taskYIELD() must never be called
		from an ISR! */
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
		Chip_TIMER_ClearMatch(LPC_TIMER0, channel_1);
	}
}

void TIMER1_IRQHandler( void )
{
	static const uint8_t channel_0 = 0;
	static const uint8_t channel_1 = 0;
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	if( Chip_TIMER_MatchPending(LPC_TIMER1, channel_0) )
	{
		xSemaphoreGiveFromISR(sem_timer1_match0, &xHigherPriorityTaskWoken );
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
		Chip_TIMER_ClearMatch(LPC_TIMER1, channel_0);
		//Chip_GPIO_SetPinOutHigh(LPC_GPIO, BL);
	}
	if( Chip_TIMER_MatchPending(LPC_TIMER1, channel_1) )
	{
		xSemaphoreGiveFromISR(sem_timer1_match1, &xHigherPriorityTaskWoken );
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
		Chip_TIMER_ClearMatch(LPC_TIMER1, channel_1);
		//Chip_GPIO_SetPinOutLow(LPC_GPIO, BL);
	}
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
