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
	void adc_pre_procesamiento();	// Funcion que debe ejecutar luego de recibir los datos, antes de procesar
// ************************** //


// ***************** DEFINES PRIVADAS ***************** //
	// *** MAQUINA DE ESTADOS - ADC *** ///
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
		#define PINGPONG_ADC_IDLE					-1		// Esperando
		#define PINGPONG_ADC_TRANSFIRIENDO_A		0x00	// Solo transfiriendo buffer A de ping-pong
		#define PINGPONG_ADC_TRANSFIRIENDO_B		0x01	// Solo transfiriendo buffer B de ping-pong
		#define PINGPONG_ADC_TRANS_A_PROC_B			0x02	// transfiriendo buffer A y procesando buffer B de ping-pong
		#define PINGPONG_ADC_TRANS_B_PROC_A			0x03	// transfiriendo buffer B y procesando buffer A de ping-pong
		#define PINGPONG_ADC_TRANS_A_PROC_B_ERR		0x04	// ERROR: termino de transferir buffer A pero no termino de procesar B
		#define PINGPONG_ADC_TRANS_B_PROC_A_ERR		0x05	// ERROR: termino de transferir buffer B pero no termino de procesar A

	#define PINGPONG_ADC_ISPROC(status)					((status & 0x06) == 0x02) // Analiza si 'status' es PINGPONG_TRANS_X_PROC_Y
	#define PINGPONG_ADC_ISERR(status)					((status & 0x06) == 0x04) // Analiza si 'status' es PINGPONG_TRANS_X_PROC_Y_ERR

	#define PINGPONG_ADC_PROC2ERR(status)				status |= 0x04 // Convierte 'status' de PINGPONG_TRANS_X_PROC_Y a PINGPONG_TRANS_X_PROC_Y_ERR
	#define PINGPONG_ADC_PROC2TRANS(status)				status &= 0x01 // Convierte 'status' de (PINGPONG_TRANS_X_PROC_Y o PINGPONG_TRANS_X_PROC_Y_ERR) a PINGPONG_TRANSFIRIENDO_X
	// *** ********************** *** ///

	// *** MAQUINA DE ESTADOS - DAC *** ///
		/* maquina de estados (dac):
		 * 1 - En la inicializacion del DAC, se pone 'status = PINGPONG_DAC_IDLE'
		 * 2 - cuando el ADC termina de procesar buffer A,
		 * 		si 'status == PINGPONG_DAC_IDLE', envia por el DAC el buffer A procesado y pone 'status = PINGPONG_DAC_TRANSFIRIENDO_A'
		 * 3 - Cuando interrumpe el DAC,
		 * 		si 'status == PINGPONG_DAC_TRANSFIRIENDO_A' se pone 'status = PINGPONG_DAC_IDLE'
		 * 4 - cuando el ADC termina de procesar buffer B,
		 * 		si 'status == PINGPONG_DAC_IDLE', envia por el DAC el buffer B procesado y pone 'status = PINGPONG_DAC_TRANSFIRIENDO_B'
		 * 		si 'status == PINGPONG_DAC_TRANSFIRIENDO_A' pone 'status = PINGPONG_DAC_RECIBIDO_B_ERR'
		 * 5 - Cuando interrumpe el DAC,
		 * 		si 'status == PINGPONG_DAC_TRANSFIRIENDO_B' se pone 'status = PINGPONG_DAC_IDLE'
		 * 		si 'status == PINGPONG_DAC_RECIBIDO_B_ERR', envia por el DAC el buffer B procesado y pone 'status = PINGPONG_DAC_TRANSFIRIENDO_B'
		 * 2' - cuando el ADC termina de procesar buffer A,
		 * 		si 'status == PINGPONG_DAC_IDLE', envia por el DAC el buffer A procesado y pone 'status = PINGPONG_DAC_TRANSFIRIENDO_A'
		 * 		si 'status == PINGPONG_DAC_TRANSFIRIENDO_B' pone 'status = PINGPONG_DAC_RECIBIDO_A_ERR'
		 * 3' - Cuando interrumpe el DAC,
		 * 		si 'status == PINGPONG_DAC_TRANSFIRIENDO_A' se pone 'status = PINGPONG_DAC_IDLE'
		 * 		si 'status == PINGPONG_DAC_RECIBIDO_A_ERR', envia por el DAC el buffer A procesado y pone 'status = PINGPONG_DAC_IDLE'
		 * 8 - repite desde paso 4
		 */
			// Estados del DMA del DAC (para una maquina de estados)
		#define PINGPONG_DAC_IDLE					-1		// Esperando
		#define PINGPONG_DAC_RECIBIDO_A				0x00	// Buffer A de ping-pong recibido
		#define	PINGPONG_DAC_RECIBIDO_B				0x01	// Buffer B de ping-pong recibido
		#define PINGPONG_DAC_RECIBIDO_A_ERR			0x02	// ERROR: si no termino de transferir B y ya tiene buffer A para transferir
		#define PINGPONG_DAC_RECIBIDO_B_ERR			0x03	// ERROR: si no termino de transferir A y ya tiene buffer B para transferir
		#define PINGPONG_DAC_TRANSFIRIENDO_A		0x04	// Transfiriendo buffer B de ping-pong
		#define	PINGPONG_DAC_TRANSFIRIENDO_B		0x05	// Transfiriendo buffer B de ping-pong

	#define PINGPONG_DAC_ISTRANS(status)			((status & 0x04) == 0x04) // Analiza si 'status' es PINGPONG_TRANS_X_PROC_Y_ERR

	#define PINGPONG_DAC_TRANS2ERR(status)			status -= 0x02 // Convierte 'status' de PINGPONG_DAC_TRANSFIRIENDO_X a PINGPONG_DAC_RECIBIDO_X_ERR
// **************************************************** //


// ************* VARIABLES PRIVADAS ************* //
	#if USE_ADC_EXTERNO
		extern DMA_TransferDescriptor_t *dma_adc_ext_descriptor;		// Apunta al descriptor del buffer actual (el que se puede procesar) del Ping-Pong del ADC
		extern DMA_TransferDescriptor_t dma_adc_ext_descriptor_A;		// Descriptor del buffer A del Ping-Pong del ADC
		extern DMA_TransferDescriptor_t dma_adc_ext_descriptor_B;		// Descriptor del buffer B del Ping-Pong del ADC

		extern volatile uint32_t dma_adc_ext_memory_A[ADC_DMA_CANT_MUESTRAS];	// Buffer A del Ping-Pong del ADC
		extern volatile uint32_t dma_adc_ext_memory_B[ADC_DMA_CANT_MUESTRAS];	// Buffer B del Ping-Pong del ADC

		extern uint8_t dma_adc_ext_canal;

		extern volatile uint8_t dma_adc_ext_status;
	#endif

	#if USE_DAC_INTERNO
		extern DMA_TransferDescriptor_t dma_dac_int_descriptor_A;				// Descriptor del buffer A del Ping-Pong del DAC
		extern DMA_TransferDescriptor_t dma_dac_int_descriptor_B;				// Descriptor del buffer B del Ping-Pong del DAC

		extern volatile uint16_t dma_dac_int_memory_A[DAC_DMA_CANT_MUESTRAS];	// Buffer A del Ping-Pong del DAC
		extern volatile uint16_t dma_dac_int_memory_B[DAC_DMA_CANT_MUESTRAS];	// Buffer B del Ping-Pong del DAC

		extern uint8_t dma_dac_int_canal;

		extern volatile uint8_t dma_dac_int_status;
	#endif
// ********************************************** //


#endif /* ADC_DAC_HEADER_PRIV_H_ */
