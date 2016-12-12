/*
 * display_int.c
 *
 *  Created on: 7 de nov. de 2016
 *      Author: agustin
 */


#include "header.h"


#if (USE_DISPLAY)


	void TIMER1_IRQHandler( void )
	{
		portBASE_TYPE pxHigherPriorityTaskWoken = pdFALSE;

	   if( Chip_TIMER_MatchPending( LPC_TIMER1 , 0 ) )
	   {
		  Chip_TIMER_ClearMatch( LPC_TIMER1 , 0 );
		  Chip_GPIO_SetPinOutHigh( LPC_GPIO , BL );
	   }
	   if( Chip_TIMER_MatchPending( LPC_TIMER1 , 1 ) )
	   {
		  Chip_TIMER_ClearMatch( LPC_TIMER1 , 1 );
		  Chip_GPIO_SetPinOutLow( LPC_GPIO , BL );
	   }
	   portEND_SWITCHING_ISR( pxHigherPriorityTaskWoken );
	}


#endif
