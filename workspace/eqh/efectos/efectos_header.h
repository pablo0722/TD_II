/*
 * efectos_header.h
 *
 *  Created on: 8 de dic. de 2016
 *      Author: agustin
 */

#ifndef EFECTOS_HEADER_H_
#define EFECTOS_HEADER_H_

#include "header.h"


// ********* FUNCIONES ********** //
	#if (USE_EFECTOS)

		void distorsion(q31_t *in, q31_t *out, uint16_t length, q31_t dist);
		void overdrive(q31_t *in, q31_t *out, uint16_t length, q31_t dist);
		q31_t eco_iir(q31_t in, q31_t profundidad, uint8_t densidad);
		q31_t reverb(q31_t in, q31_t profundidad, uint8_t densidad);
		q31_t flanger(q31_t in, q31_t profundidad, uint16_t cos_f, uint8_t densidad);

	#endif
// ****************************** //


// ***************** DEFINES ***************** //
	#if (USE_EFECTOS)

	// Cantidad de ecos que suma para obtener el efecto reverb
	#define CANT_REVERB 4

	// Cantidad de ecos que suma para obtener el efecto reverb
	#define DELAY_LENGTH 8000

	#define TS	((q31_t) 0x10625)

	#endif
// ******************************************* //


// *************** ESTRUCTURAS *************** //
	#if (USE_EFECTOS)



	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if (USE_EFECTOS)




	#endif
// ********************************************** //


// ************* HEADERS ************* //


// ****************************************** //



#endif /* EFECTOS_HEADER_H_ */
