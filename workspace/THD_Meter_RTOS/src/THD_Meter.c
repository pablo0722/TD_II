/*
===============================================================================
 Name        : THD_Meter.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <cr_section_macros.h>

#include "header.h"







void main_uninit()
{
	/* DeInitialize UART1 peripheral */
	NVIC_DisableIRQ(UART0_IRQn);
	Chip_UART_DeInit(LPC_UART0);
}

int main(void)
{
	main_init();

	while(1)
	{
		/*
		if (signalin_flag == 1)
		{
			// Wrap value back around
			//Chip_UART_SendRB(LPC_UART0, &txring, (const uint8_t *) &key, 1);
		}
		*/
	}

	main_uninit();

	while(1);

    return 0 ;
}
