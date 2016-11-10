/*
 * tft_private_func.c
 *
 *  Created on: 6 de nov. de 2016
 *      Author: Pablo
 */


#include "header.h"


// *** PROTOTIPOS FUNCIONES PRIVADAS (en serio) *** //
	static void tft_TM_Send(uint16_t data);
// ********************************************* //


// *** FUNCIONES "PRIVADAS" (solo para funciones internas de TFT) *** //
	void tft_Delay_priv(volatile unsigned long int delay)
	{
		for (; delay != 0; delay--);
	}

	void tft_SendCommand_priv(uint16_t data)
	{
		pin_set(READ_DATA,1);
		pin_set(RS,0);
		pin_set(WR,0);
		pin_set(CS,0);
		tft_TM_Send(data);
		pin_set(CS,1);
		pin_set(WR,1);
	}

	void tft_SendData_priv(uint16_t data)
	{
		//Chip_GPIO_SetPinState(LPC_GPIO,READ_DATA,0);
		pin_set(RS,1);
		pin_set(WR,0);
		pin_set(CS,0);
		tft_TM_Send(data);
		// Segun stm32
		pin_set(CS,1);
		pin_set(WR,1);
	}
// ************************** //


// *** FUNCIONES 'SUPER' PRIVADAS *** //
	static void tft_TM_Send(uint16_t data)
	{
		pin_set(DB0,  (data >> 0) & 1);
		pin_set(DB1,  (data >> 1) & 1);
		pin_set(DB2,  (data >> 2) & 1);
		pin_set(DB3,  (data >> 3) & 1);
		pin_set(DB4,  (data >> 4) & 1);
		pin_set(DB5,  (data >> 5) & 1);
		pin_set(DB6,  (data >> 6) & 1);
		pin_set(DB7,  (data >> 7) & 1);
		pin_set(DB8,  (data >> 8) & 1);
		pin_set(DB9,  (data >> 9) & 1);
		pin_set(DB10, (data >> 10) & 1);
		pin_set(DB11, (data >> 11) & 1);
		pin_set(DB12, (data >> 12) & 1);
		pin_set(DB13, (data >> 13) & 1);
		pin_set(DB14, (data >> 14) & 1);
		pin_set(DB15, (data >> 15) & 1);
	}
// ********************************** //
