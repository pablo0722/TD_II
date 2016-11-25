/*
 * adc_dac_header.h
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */

#ifndef ADC_DAC_HEADER_H_
#define ADC_DAC_HEADER_H_



#include "header.h"


// ********* FUNCIONES ********** //
	void adc_dac_init();								// Inicializa lo necesario para usar dma y adc/dac interno/externo (externo por i2s)

	#if (USE_ADC_EXTERNO)
		void adc_ext_prepare(volatile uint32_t *buffer_A,	// Prepara el buffer para poder recibir desde el ADC. Si esta definido buffer B, comienza a recibir por el A
						 volatile uint32_t *buffer_B);
		void adc_ext_start();								// Si el buffer B no fue definido, se detendra la transferencia luego de llenar el A. para reanudar hay que llamar a esta funcion
		void adc_ext_post_procesamiento();					// Funcion que debe ejecutar luego de procesar los datos, para continuar con la transferencia del ADC
	#endif

	#if USE_DAC_EXTERNO
		uint16_t dac_ext_set_data(uint32_t data);			// transforma un dato de uint32_t a uint16_t para ser transmitido por DAC
		void dac_ext_prepare(volatile uint16_t *buffer);	// Prepara el buffer para poder ser enviado por DAC
		bool dac_ext_disponible();							// Determina si el dac esta disponible para transmitir
		void dac_ext_send();								// Envia una senial por DAC
	#endif

	#if USE_DAC_INTERNO
		void dac_int_prepare(volatile uint16_t *buffer);	// Prepara el buffer para poder ser enviado por DAC
		void dac_int_send();								// Envia una senial por DAC
	#endif
// ****************************** //

// ***************** DEFINES ***************** //
	#if USE_ADC
		#define ADC_DMA_CANT_MUESTRAS 	2048
		#define ADC_FREQ 				32000
	#endif

	#if USE_DAC
		#define DAC_DMA_CANT_MUESTRAS 	2048
		#define DAC_FREQ 				ADC_FREQ
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if (USE_ADC_EXTERNO)
		extern volatile uint32_t 		*dma_adc_ext_memory;	// Apunta al buffer actual (el que se puede procesar) del ADC

		#if (USE_RTOS)
			extern xSemaphoreHandle 	sem_adc_ext_proc;			// Semaforo que indica que recibio un dato por adc y debe ser procesado.
		#endif
	#endif

	#if (USE_DAC_EXTERNO)
		#if (USE_RTOS)
			extern xSemaphoreHandle 	sem_dac_ext_finish;			// Semaforo que indica cuando se termino de enviar un dato por DAC
		#endif
	#endif

	#if (USE_DAC_INTERNO)
		#if (USE_RTOS)
			extern xSemaphoreHandle 	sem_dac_int_finish;			// Semaforo que indica cuando se termino de enviar un dato por DAC
		#endif
	#endif
// ********************************************** //


#endif /* ADC_DAC_HEADER_H_ */
