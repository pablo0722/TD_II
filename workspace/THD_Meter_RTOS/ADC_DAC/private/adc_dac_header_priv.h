/*
 * adc_dac_func_priv.h
 *
 *  Created on: 7 de nov. de 2016
 *      Author: Pablo
 */

#ifndef ADC_DAC_HEADER_PRIV_H_
#define ADC_DAC_HEADER_PRIV_H_


#include "header.h"


// *** FUNCIONES PRIVADAS *** //
	void adc_ext_pre_procesamiento();	// Funcion que debe ejecutar luego de recibir los datos, antes de procesar
// ************************** //


// ***************** DEFINES PRIVADAS ***************** //
	// *** PIN-OUT *** //
		#if (USE_DAC)
			#define AOUT				0,26
		#endif

		#if (USE_ADC_EXTERNO)
			// PARA EL ADC POR I2S
				#define RX_CONFIG0		0	// El nuestro
				#define RX_CONFIG1		1	// El de Agustin Diaz Antuña (ADA)
			#define RX_CONFIG	RX_CONFIG0

			#if (RX_CONFIG == RX_CONFIG0)
				#define I2SRX_CLK			0,4, MD_PLN, IOCON_FUNC1	// Se puede usar el mismo CLK para RX y TX
				#define I2SRX_WS			0,5, MD_PLN, IOCON_FUNC1
				#define I2SRX_SDA			0,6, MD_PLN, IOCON_FUNC1
			#endif

			#if (RX_CONFIG == RX_CONFIG1)
				#define I2SRX_CLK			0,23, MD_PLN, IOCON_FUNC2	// Se puede usar el mismo CLK para RX y TX
				#define I2SRX_WS			0,24, MD_PLN, IOCON_FUNC2
				#define I2SRX_SDA			0,25, MD_PLN, IOCON_FUNC2
			#endif

			#define RX_MCLK				4, 28, MD_PLN, IOCON_FUNC1
		#endif


		#if (USE_DAC_EXTERNO)
			// PARA EL DAC POR I2S
				#define TX_CONFIG0		0	// El nuestro
				#define TX_CONFIG1		1	// El de Agustin Diaz Antuña (ADA)
			#define TX_CONFIG	TX_CONFIG0

			#if (TX_CONFIG == TX_CONFIG0)
				#define I2STX_CLK			0, 7,  MD_PLN, IOCON_FUNC1	// Se puede usar el mismo CLK para RX y TX
				#define I2STX_WS			0, 8,  MD_PLN, IOCON_FUNC1
				#define I2STX_SDA			0, 9,  MD_PLN, IOCON_FUNC1
			#endif

			#if (TX_CONFIG == TX_CONFIG1)
				#define I2STX_CLK			2, 11, MD_PLN, IOCON_FUNC3	// Se puede usar el mismo CLK para RX y TX
				#define I2STX_WS			2, 12, MD_PLN, IOCON_FUNC3
				#define I2STX_SDA			2, 13, MD_PLN, IOCON_FUNC3
			#endif

			#define TX_MCLK				4, 29, MD_PLN, IOCON_FUNC1
		#endif
	// *************** //

	// *** MAQUINA DE ESTADOS - ADC *** //
			/* maquina de estados (adc):
			 * 1 - En la inicializacion del ADC, transfiere buffer A, y se pone 'status = PINGPONG_ADC_TRANSFIRIENDO_A'
			 * 2 - Cuando recibe interrupcion del buffer A del ADC, se pone 'status = PINGPONG_ADC_TRANS_B_PROC_A',
			 * 		se transfiere el buffer B del ADC y se procesa el buffer A.
			 * 3 - Cuando se termina de procesar, se pone 'status = PINGPONG_ADC_TRANSFIRIENDO_B'
			 * 4 - Cuando recibe interrupcion del buffer B del ADC, se pone 'status = PINGPONG_ADC_TRANS_A_PROC_B',
			 * * se transfiere el buffer A del ADC y se procesa el buffer B.
			 * 5 - Cuando se termina de procesar, se pone 'status = PINGPONG_ADC_TRANSFIRIENDO_A'
			 * 6 - se repite desde el paso 2
			 * nota: si recibe interrupcion de buffer X antes de terminar de procesar buffer Y,
			 * 		se pone 'status = PINGPONG_ADC_TRANS_X_PROC_Y_ERR', se de tiene la transferencia de los buffers del ADC
			 * 		y se reanuda la transferencia cuando se termina de procesar.
			 */
				// Estados del DMA del ADC
			#define STATUS_ADC_IDLE					-1		// Esperando
			#define STATUS_ADC_TRANSFIRIENDO_A		0x00	// Solo transfiriendo buffer A de ping-pong
			#define STATUS_ADC_TRANSFIRIENDO_B		0x01	// Solo transfiriendo buffer B de ping-pong
			#define STATUS_ADC_TRANS_A_PROC_B		0x02	// transfiriendo buffer A y procesando buffer B de ping-pong
			#define STATUS_ADC_TRANS_B_PROC_A		0x03	// transfiriendo buffer B y procesando buffer A de ping-pong
			#define STATUS_ADC_TRANS_B_PROC_A_ERR	0x04	// ERROR: termino de transferir buffer B pero no termino de procesar A
			#define STATUS_ADC_TRANS_A_PROC_B_ERR	0x05	// ERROR: termino de transferir buffer A pero no termino de procesar B

		#define STATUS_ADC_ISPROC(status)			((status & 0x06)) 	// Analiza si 'status' es PINGPONG_TRANS_X_PROC_Y o STATUS_ADC_TRANS_X_PROC_Y_ERR
		#define STATUS_ADC_ISERR(status)			(status & 0x04) 	// Analiza si 'status' es PINGPONG_TRANS_X_PROC_Y_ERR

		#define STATUS_ADC_PROC2ERR(status)			status += 2 	// Convierte 'status' de PINGPONG_TRANS_X_PROC_Y a PINGPONG_TRANS_X_PROC_Y_ERR
		#define STATUS_ADC_PROC2TRANS(status)		status &= 0x01 	// Convierte 'status' de (PINGPONG_TRANS_X_PROC_Y o PINGPONG_TRANS_Y_PROC_X_ERR) a PINGPONG_TRANSFIRIENDO_X
	// *** ********************** *** //
// **************************************************** //


// ************* VARIABLES PRIVADAS ************* //
	#if USE_ADC_EXTERNO
		extern DMA_TransferDescriptor_t *dma_adc_ext_descriptor;		// Apunta al descriptor del buffer actual (el que se puede procesar) del Ping-Pong del ADC
		extern DMA_TransferDescriptor_t dma_adc_ext_descriptor_A;		// Descriptor del buffer A del Ping-Pong del ADC
		extern DMA_TransferDescriptor_t dma_adc_ext_descriptor_B;		// Descriptor del buffer B del Ping-Pong del ADC

		extern volatile uint32_t *dma_adc_ext_memory_A;	// Buffer A del Ping-Pong del ADC
		extern volatile uint32_t *dma_adc_ext_memory_B;	// Buffer B del Ping-Pong del ADC

		extern uint8_t dma_adc_ext_canal;

		extern volatile int8_t dma_adc_ext_status;
	#endif

	#if USE_DAC_EXTERNO
		extern DMA_TransferDescriptor_t dma_dac_ext_descriptor;	// Descriptor del buffer A del Ping-Pong del DAC

		extern volatile uint32_t *		dma_dac_ext_memory;		// Buffer A del Ping-Pong del DAC

		extern uint8_t 					dma_dac_ext_canal;		// Canal del DAC en el DMA
	#endif

	#if USE_DAC_INTERNO
		extern DMA_TransferDescriptor_t dma_dac_int_descriptor;	// Descriptor del buffer A del Ping-Pong del DAC

		extern volatile uint16_t *		dma_dac_int_memory;		// Buffer A del Ping-Pong del DAC

		extern uint8_t 					dma_dac_int_canal;		// Canal del DAC en el DMA
	#endif
// ********************************************** //

// *** INICIALIZACION *** //
	#include "adc_dac_init_priv.h"
// ********************** //


#endif /* ADC_DAC_HEADER_PRIV_H_ */
