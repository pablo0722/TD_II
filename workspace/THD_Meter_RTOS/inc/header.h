/*
 * header.h
 *
 *  Created on: 18 de ago. de 2016
 *      Author: pablo
 */


#ifndef HEADER_H_
#define HEADER_H_


	#include "FreeRTOS.h"
	#include "task.h"
	#include "board.h"
	#include "chip.h"
	#include "semphr.h"
	#include "queue.h"

	#include <string.h>	// Funcion memset
	#include <math.h>	// Funcion sqrt

		// CMSIS
	#include "arm_math.h"



	#ifndef ON
		#define ON	1
	#endif
	#ifndef OFF
		#define OFF	0
	#endif


// ***** PERIFERICOS (init) ***** //
	#define USE_UART	ON
	#define USE_ADC		OFF
	#define USE_DAC		OFF
	#define USE_FFT		ON
	#define USE_RTOS	OFF
// ****************************** //


// ***** UTILIDADES (main while) ***** //
	#define UART_LOOPBACK		OFF
	#define UART_BYTE_BY_BYTE	OFF	// Lee byte por byte, avisa apenas recibe un byte. Util para strings de largo indefinido (no es compatible con el siguiente define "UART_BY_VECTOR")
	#define UART_BY_VECTOR		ON	// Lee byte por byte, pero avisa cuando se lleno un vector. Util cuando se quiere recibir una senial y procesarla varias veces "en paralelo" (no es compatible con el anterior define "UART_BYTE_BY_BYTE")
	#define FFT_TO_UART 		ON
	#define FFT_FROM_UART 		ON
// *********************************** //


// ***** FUNCIONES ****** //
	void main_init();

	#if USE_FFT
		void fft_function();
	#endif

	#if USE_UART
		void main_uart();
	#endif

	#if USE_RTOS
		void vTask_THD( void *pvParameters );
	#endif
// ********************** //


// Corroboracion de errores //

#if (UART_BYTE_BY_BYTE) && (UART_BY_VECTOR)
	#error defines incompatibles activados simultaneamente: "UART_BYTE_BY_BYTE" y "UART_BY_VECTOR"
#endif
// ************************ //


// ***** VARIABLES GLOBALES ***** //
	#if USE_FFT
		#define     FFT_SIZE    	           	512	// Tamanio del vector del modulo de la FFT (Es un cuarto (1/2) del tamanio original por estar espejado)
		#define 	FFT_TYPE_SIZE				4					// Es el tamanio (en bytes) del tipo de los datos para fft (q31_t => 4, q15_t => 2, etc)

			// Cantidad de veces que se usara la FFT
		#define 	FFT_DONE_MAX				FFT_TO_UART

			// Cantidad de veces que se usara lo leido por UART
		#define UART_RX_FFT_DONE_MAX 	UART_LOOPBACK + \
										USE_FFT


		extern arm_rfft_instance_q31 fft_inst_q31;					// Estructura para aplicar FFT
		extern arm_cfft_radix4_instance_q31 fft_inst_q31_complex;	// Estructura para aplicar FFT

		extern volatile q31_t fft_out[FFT_SIZE*2];			// Espectro de la senal transformada (el "*2" es porque es real e imaginario)
		extern volatile q31_t fft_in[FFT_SIZE];				// Senal de entrada. Es vector complejo.

		extern uint8_t fft_done;							// Cantidad de veces que se uso la FFT
		extern uint8_t uart_rx_fft_done;					// Cantidad de veces que se uso lo que lei por uart
	#endif


	#if USE_RTOS
			//Colas
		#define QUEUE_LEN_IN	1
		#define QUEUE_LEN_REM	QUEUE_LEN_IN
		#define QUEUE_LEN_THD	1

		#if USE_FFT
			#define QUEUE_ITEM_SIZE_IN	(sizeof(short int)*FFT_SIZE)
		#else
			#define QUEUE_ITEM_SIZE_IN	(sizeof(short int)*512)
		#endif

		#define QUEUE_ITEM_SIZE_REM	QUEUE_ITEM_SIZE_IN
		#define QUEUE_ITEM_SIZE_THD	(sizeof(float))

		extern xQueueHandle xQueue_in;
		extern xQueueHandle xQueue_rem;
		extern xQueueHandle xQueue_THD;
	#endif


	#if USE_UART
		#define LPC_UARTN 			LPC_UART0					// Numero de UART a utilizar
		#define UARTN_IRQn 			UART0_IRQn					// Numero de UART a utilizar
		#define UARTN_IRQHandler 	UART0_IRQHandler			// Numero de UART a utilizar

		#if USE_FFT
			#define UART_SIZE 			FFT_SIZE*FFT_TYPE_SIZE	// Tamanio de UART buffer. El "*FFT_TYPE_SIZE" es porq son de algun tipo de dato de varios bytes y recibo de a 1 byte
		#else
			#define UART_SIZE 			1						// Tamanio de UART buffer
		#endif


		#define UART_BAUDRATE 		9600					// Baud rate de la UART

			// Transmit and receive ring buffer sizes
		#define UART_SRB_SIZE 	UART_SIZE	// Send
		#define UART_RRB_SIZE 	UART_SIZE	// Receive

			// Transmit and receive buffers
		extern uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

			// Transmit and receive ring buffers
		extern RINGBUFF_T txring, rxring;
	#endif


	#if USE_ADC
		#define ADC_FREQ 20000
		#define ADC_DMA_CANT_MUESTRAS 1
		#define ADC_DMA_CHANNEL 0

		//extern DMA_TransferDescriptor_t DMA_descriptor_ADC;
		extern volatile uint32_t dma_memory_adc[ADC_DMA_CANT_MUESTRAS];
	#endif


	#if USE_DAC
		#define DAC_FREQ ADC_FREQ
		#define DAC_DMA_CANT_MUESTRAS ADC_DMA_CANT_MUESTRAS
		#define DAC_DMA_CHANNEL 1

		//extern DMA_TransferDescriptor_t DMA_descriptor_DAC;
		extern volatile uint16_t dma_memory_dac[DAC_DMA_CANT_MUESTRAS];
	#endif
// ****************************** //


#endif /* HEADER_H_ */
