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

			// Estados del DMA (para una maquina de estados)
		#define PINGPONG_IDLE					-1		// Esperando (adc y dac)
		#define PINGPONG_TRANSFIRIENDO_A		0x00	// Solo transfiriendo buffer A de ping-pong (adc)
		#define PINGPONG_TRANSFIRIENDO_B		0x01	// Solo transfiriendo buffer B de ping-pong (adc)
		#define PINGPONG_TRANS_A_PROC_B			0x02	// transfiriendo buffer A y procesando buffer B de ping-pong (adc)
		#define PINGPONG_TRANS_B_PROC_A			0x03	// transfiriendo buffer B y procesando buffer A de ping-pong (adc)
		#define PINGPONG_TRANS_A_PROC_B_ERR		0x04	// ERROR: termino de transferir buffer A pero no termino de procesar B (adc)
		#define PINGPONG_TRANS_B_PROC_A_ERR		0x05	// ERROR: termino de transferir buffer B pero no termino de procesar A (adc)
		#define PINGPONG_RECIBIDO_A				0x06	// Buffer A de ping-pong recibido (dac)
		#define	PINGPONG_RECIBIDO_B				0x07	// Buffer B de ping-pong recibido (dac)

			// Analiza si 'status' es PINGPONG_TRANS_X_PROC_Y
		#define PINGPONG_ISPROC(status)		((status & 0x06) == 0x02)
			// Analiza si 'status' es PINGPONG_TRANS_X_PROC_Y_ERR
		#define PINGPONG_ISERR(status)		((status & 0x06) == 0x04)

			// Convierte de 'status' PINGPONG_TRANS_X_PROC_Y a PINGPONG_TRANS_X_PROC_Y_ERR
		#define PINGPONG_PROC2ERR(status)		status |= 0x04
			// Convierte de 'status' (PINGPONG_TRANS_X_PROC_Y o PINGPONG_TRANS_X_PROC_Y_ERR) a PINGPONG_TRANSFIRIENDO_X
		#define PINGPONG_PROC2TRANS(status)		status &= 0x01
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_ADC_EXTERNO
		extern volatile DMA_TransferDescriptor_t dma_adc_ext_descriptor_A;		// Descriptor del buffer A del Ping-Pong del ADC
		extern volatile DMA_TransferDescriptor_t dma_adc_ext_descriptor_B;		// Descriptor del buffer B del Ping-Pong del ADC

		extern volatile uint32_t dma_adc_ext_memory_A[ADC_DMA_CANT_MUESTRAS];	// Buffer A del Ping-Pong del ADC
		extern volatile uint32_t dma_adc_ext_memory_B[ADC_DMA_CANT_MUESTRAS];	// Buffer B del Ping-Pong del ADC

		extern volatile uint8_t dma_adc_ext_canal;

		extern volatile uint8_t dma_adc_ext_status = BUFFER_A_PINGPONG;
	#endif

	#if USE_DAC_INTERNO
		extern DMA_TransferDescriptor_t dma_dac_int_descriptor_A;				// Descriptor del buffer A del Ping-Pong del DAC
		extern DMA_TransferDescriptor_t dma_dac_int_descriptor_B;				// Descriptor del buffer B del Ping-Pong del DAC

		extern volatile uint16_t dma_dac_int_memory_A[DAC_DMA_CANT_MUESTRAS];	// Buffer A del Ping-Pong del DAC
		extern volatile uint16_t dma_dac_int_memory_B[DAC_DMA_CANT_MUESTRAS];	// Buffer B del Ping-Pong del DAC

		extern volatile uint8_t dma_dac_int_canal;

		extern volatile uint8_t dma_dac_int_status = BUFFER_A_PINGPONG;
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
