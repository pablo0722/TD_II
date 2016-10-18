/*
 * Variables_globales.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"



#if USE_RTOS
	xQueueHandle xQueue_in;
	xQueueHandle xQueue_rem;
	xQueueHandle xQueue_THD;
#endif


#if USE_FFT
	arm_rfft_instance_q31 fft_inst_q31;
	arm_cfft_radix4_instance_q31 fft_inst_q31_complex;

	volatile q31_t fft_out[FFT_SIZE*2];	// Espectro de la senal transformada
	volatile q31_t fft_in[FFT_SIZE];	// Senal  de entrada. Es vector complejo.

	uint8_t fft_done = 0;
#endif


#if USE_UART
	/* Transmit and receive buffers */
	uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

	/* Transmit and receive ring buffers */
	RINGBUFF_T txring, rxring;
	uint8_t uart_rx_done = 0;
	#if UART_BY_VECTOR
		volatile int32_t uart_in_A[UART_SIZE/4];			// Senal de entrada A (primer vector del ping-pong)
		volatile int32_t uart_in_B[UART_SIZE/4];			// Senal de entrada B (segundo vector del ping-pong)
		volatile int32_t *uart_in;						// Senal de entrada.
	#elif UART_BYTE_BY_BYTE
		volatile uint8_t uart_in;						// Senal de entrada.
	#endif

#endif


#if USE_ADC_INTERNO
	DMA_TransferDescriptor_t DMA_descriptor_ADC;
	volatile uint32_t dma_memory_adc[ADC_DMA_CANT_MUESTRAS];
	uint8_t canal_adc;
	uint8_t canal_adc;
#endif

#if USE_DAC_INTERNO
	DMA_TransferDescriptor_t DMA_descriptor_DAC;
	volatile uint32_t dma_memory_dac[DAC_DMA_CANT_MUESTRAS];

	uint8_t canal_dac;
#endif


#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
	uint16_t adcFlag = 1;
	int32_t data, cont = 0, ch = 0;
#endif
