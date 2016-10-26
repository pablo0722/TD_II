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
	#if (USE_DAC_INTERNO)
		void main_dac();
		void main_dac_aux();
	#endif
// ****************************** //


// ***************** DEFINES ***************** //
	#if USE_ADC
		#define ADC_FREQ 				20000
		#define ADC_DMA_CANT_MUESTRAS 	8
		#define ADC_DMA_CHANNEL 		1
	#endif

	#if USE_DAC
		#define DAC_FREQ 				ADC_FREQ
		#define DAC_DMA_CANT_MUESTRAS 	ADC_DMA_CANT_MUESTRAS
		#define DAC_DMA_CHANNEL 		0
	#endif

	#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
		#define	I2S_INT_POLLING		1
		#define I2S_DMA				(!(I2S_INT_POLLING))

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
	#if USE_ADC
		extern DMA_TransferDescriptor_t DMA_descriptor_ADC;
		extern volatile uint32_t dma_memory_adc[ADC_DMA_CANT_MUESTRAS];
		extern volatile uint8_t canal_adc;
	#endif

	#if USE_DAC
		extern DMA_TransferDescriptor_t DMA_descriptor_DAC;
		extern volatile uint32_t dma_memory_dac[DAC_DMA_CANT_MUESTRAS];
		extern volatile uint8_t canal_dac;
	#endif

	#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
		extern uint16_t adcFlag;
		extern int32_t data, cont, ch;
	#endif
// ********************************************** //


// ************* INICIALIZACION ************* //
	#include "adc_dac_init.h"
// ****************************************** //


#endif /* ADC_DAC_HEADER_H_ */
