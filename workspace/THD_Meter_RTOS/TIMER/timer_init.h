/*
 * timer_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"


#if USE_TIMER
	static inline timer0_init()
	{
		uint32_t timerFreq, matchVal;
		static const uint8_t channel = 1;

		timerFreq = Chip_Clock_GetSystemClockRate();
		matchVal=timerFreq / TIMER0_TICKRATE;


		Chip_TIMER_Init(LPC_TIMER0);

		Chip_TIMER_Reset(LPC_TIMER0); 				//Resets the timer terminal and prescale counts to 0.

		/* Timer setup for match and interrupt at TICKRATE_HZ */
			Chip_TIMER_MatchEnableInt(LPC_TIMER0, channel);	//Enables a match interrupt that fires
														//when the terminal count matches the match counter value. Match1
			Chip_TIMER_SetMatch(LPC_TIMER0, channel, matchVal); //Sets a timer match value.

			Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, channel); //For the specific match counter,
														  //enables reset of the terminal count register when a match occurs

		Chip_TIMER_Enable(LPC_TIMER0);				  //Enables the timer (starts count)

		/* Enable timer interrupt */
		NVIC_ClearPendingIRQ(TIMER0_IRQn);
		NVIC_EnableIRQ(TIMER0_IRQn);
	}

	static inline timer1_init()
	{
	    Chip_TIMER_Init(LPC_TIMER1);

		Chip_TIMER_Reset(LPC_TIMER1); 				//Resets the timer terminal and prescale counts to 0.

	    Chip_TIMER_PrescaleSet( LPC_TIMER1 , Chip_Clock_GetPeripheralClockRate( SYSCTL_PCLK_TIMER1 ) / 1000000 - 1 );

		Chip_TIMER_Enable(LPC_TIMER0);				  //Enables the timer (starts count)

		/* Enable timer interrupt */
		NVIC_ClearPendingIRQ(TIMER1_IRQn);
		NVIC_EnableIRQ(TIMER1_IRQn);
	}

	static inline timer_init()
	{
			// *** Semaforos
		#if (USE_RTOS)
			vSemaphoreCreateBinary(sem_timer0_match1);
			xSemaphoreTake(sem_timer0_match1, 0);
			vSemaphoreCreateBinary(sem_timer1_match0);
			xSemaphoreTake(sem_timer1_match0, 0);
			vSemaphoreCreateBinary(sem_timer1_match1);
			xSemaphoreTake(sem_timer1_match1, 0);
		#endif

		timer0_init();
		timer1_init();
	}
#endif
