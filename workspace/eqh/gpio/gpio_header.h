/*
 * gpio_header.h
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */

#ifndef GPIO_HEADER_H_
#define GPIO_HEADER_H_


#include <header.h>



// ********* FUNCIONES ********** //

// ****************************** //


// ***************** DEFINES ***************** //
	#if USE_GPIO

		#define LED_Alive			0,16

		#if (USE_BOTONES)
			// Switch
			#define SW1 1,30
			#define SW2 1,31
			#define SW3 0,3
			#define SW4 0,2
			#define SW_5 0,22

			// Debounce
			#define WAIT_1 0
			#define VALIDATE_1 1
			#define WAIT_0 2
			#define VALIDATE_0 3
		#endif

	#endif

// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_GPIO

		extern volatile uint8_t flag_volumen_up;
		extern volatile uint8_t flag_volumen_down;

	#endif
// ********************************************** //


// ************* INICIALIZACION ************* //
		#include <gpio_init.h>
// ****************************************** //




#endif /* GPIO_HEADER_H_ */
