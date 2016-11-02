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
		uint32_t set_data (uint32_t data);
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

		#define BUFFER_A_PINGPONG	0
		#define	BUFFER_B_PINGPONG	1
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_ADC
		extern volatile DMA_TransferDescriptor_t DMA_descriptor_ADC_A;		// Descriptor del buffer A del Ping-Pong del ADC
		extern volatile DMA_TransferDescriptor_t DMA_descriptor_ADC_B;		// Descriptor del buffer B del Ping-Pong del ADC

		extern volatile uint32_t dma_memory_adc_A[ADC_DMA_CANT_MUESTRAS];	// Buffer A del Ping-Pong del ADC
		extern volatile uint32_t dma_memory_adc_B[ADC_DMA_CANT_MUESTRAS];	// Buffer B del Ping-Pong del ADC

		extern volatile uint8_t canal_adc;

		extern volatile uint8_t adc_buffer = BUFFER_A_PINGPONG;
	#endif

	#if USE_DAC
		extern DMA_TransferDescriptor_t DMA_descriptor_DAC_A;				// Descriptor del buffer A del Ping-Pong del DAC
		extern DMA_TransferDescriptor_t DMA_descriptor_DAC_B;				// Descriptor del buffer B del Ping-Pong del DAC

		extern volatile uint16_t dma_memory_dac_A[DAC_DMA_CANT_MUESTRAS];	// Buffer A del Ping-Pong del DAC
		extern volatile uint16_t dma_memory_dac_B[DAC_DMA_CANT_MUESTRAS];	// Buffer B del Ping-Pong del DAC

		extern volatile uint8_t canal_dac;

		extern volatile uint8_t dac_buffer = BUFFER_A_PINGPONG;
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
