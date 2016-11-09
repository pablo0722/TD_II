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
	#if (USE_ADC_EXTERNO)
		void main_adc_post();	// Funcion que debe ejecutar luego de procesar los datos, para enviar por DAC
		void dma_init();
	#endif
// ****************************** //

// ********* TAREAS ********** //
	#if (USE_ADC_EXTERNO)
		void adc_pre_procesamiento();
		void adc_post_procesamiento();
	#endif
// *************************** //


// ***************** DEFINES ***************** //
	#if USE_ADC
		#define ADC_FREQ 				20000
		#define ADC_DMA_CANT_MUESTRAS 	2048
		#define ADC_DMA_CHANNEL 		1
	#endif

	#if USE_DAC
		#define DAC_FREQ 				ADC_FREQ
		#define DAC_DMA_CANT_MUESTRAS 	ADC_DMA_CANT_MUESTRAS
		#define DAC_DMA_CHANNEL 		0
	#endif

	#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
		#define LED_stick			0,22
		#define AOUT				0,26

		#define I2SRX_CLK			0,4
		#define I2SRX_WS			0,5
		#define I2SRX_SDA			0,6
		#define RX_MCLK				4,28

		#define I2STX_CLK			0,7
		#define I2STX_WS			0,8
		#define I2STX_SDA			0,9
		#define TX_MCLK				4,29

		#define CH_L				1
		#define CH_R				2
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if (USE_ADC_EXTERNO)
		extern volatile uint32_t *dma_adc_ext_memory;					// Apunta al buffer actual (el que se puede procesar) del ADC

		#if (USE_RTOS)
			extern xSemaphoreHandle sem_adc_proc;
		#endif
	#endif

	#if (USE_DAC_INTERNO)
		extern Bool dac_send;
	#endif
// ********************************************** //

// ************* INICIALIZACION ************* //
	#include "adc_dac_init.h"
// ****************************************** //


#endif /* ADC_DAC_HEADER_H_ */
