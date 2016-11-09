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
		Chip_GPIO_SetPinState(LPC_GPIO,READ_DATA,1);
		Chip_GPIO_SetPinState(LPC_GPIO, RS,0);
		Chip_GPIO_SetPinState(LPC_GPIO, WR,0);
		Chip_GPIO_SetPinState(LPC_GPIO, CS,0);
		tft_TM_Send(data);
		Chip_GPIO_SetPinState(LPC_GPIO, CS,1);
		Chip_GPIO_SetPinState(LPC_GPIO, WR,1);
	}

	void tft_SendData_priv(uint16_t data)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, RS,1);
		Chip_GPIO_SetPinState(LPC_GPIO, WR,0);
		Chip_GPIO_SetPinState(LPC_GPIO, CS,0);
		tft_TM_Send(data);
		// Segun stm32
		Chip_GPIO_SetPinState(LPC_GPIO, CS,1);
		Chip_GPIO_SetPinState(LPC_GPIO, WR,1);
	}
// ************************** //


// *** FUNCIONES 'SUPER' PRIVADAS *** //
	static void tft_TM_Send(uint16_t data)
	{
			Chip_GPIO_SetPinState(LPC_GPIO, DB0, (data >> 0) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB1, (data >> 1) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB2, (data >> 2) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB3, (data >> 3) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB4, (data >> 4) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB5, (data >> 5) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB6, (data >> 6) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB7, (data >> 7) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB8, (data >> 8) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB9, (data >> 9) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB10, (data >> 10) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB11, (data >> 11) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB12, (data >> 12) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB13, (data >> 13) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB14, (data >> 14) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB15, (data >> 15) & 1);
	}
// ********************************** //
