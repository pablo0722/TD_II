/*
 * basics_header_init.h
 *
 *  Created on: 10 de nov. de 2016
 *      Author: Pablo
 */

#ifndef BASICS_HEADER_INIT_H_
#define BASICS_HEADER_INIT_H_


#include "header.h"


static inline void pin_set(uint8_t port, uint8_t pin, bool estado)
{
	Chip_GPIO_SetPinState(LPC_GPIO, port, pin, estado);
}

static inline bool pin_get(uint8_t port, uint8_t pin)
{
	return Chip_GPIO_GetPinState(LPC_GPIO, port, pin);
}

static inline void pin_gpio_init(uint8_t port, uint8_t pin, uint32_t mode, bool salida)
{
	if(DEBUG_MODE)
	{
		printf("[info] pin_init: \n");
		printf("\t puerto %hhu, pin %hhu, modo %hhu, salida %hhu \n", port, pin, mode, salida);
	}

	Chip_IOCON_PinMux(LPC_IOCON, port, pin, mode, IOCON_FUNC0);		// Setea modo (inactivo/pulldown/pullup/repeater) y funcion (gpio) del pin

	Chip_GPIO_SetDir(LPC_GPIO, port, pin, (uint8_t)salida);			// Setea direccion del pin: entrada o salida

	if(salida)
		pin_set(port, pin, 0);										// Inicializa pin en 0 (si es de salida)
}

static inline void pin_init(uint8_t port, uint8_t pin, uint32_t mode, uint8_t func)
{
	if(DEBUG_MODE)
	{
		if(func == 0)
		{
			printf("[error] pin_init:\n");
			printf("\t Quiso inicializar pin como GPIO sin usar funcion dedicada \"pin_gpio_init\" \n");
		}
		else
		{
			printf("[info] pin_init:\n");
		}
		printf("\t puerto %hhu, pin %hhu, modo %hhu, funcion %hhu\n", port, pin, mode, func);	// Setea modo (inactivo/pulldown/pullup/repeater) y funcion del pin
	}

	Chip_IOCON_PinMux(LPC_IOCON, port, pin, mode, func);		// Setea modo y funcion del pin
}



#endif /* BASICS_HEADER_INIT_H_ */
