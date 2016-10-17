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
	uint8_t uart_rx_fft_done = 0;
#endif


#if USE_UART
	/* Transmit and receive buffers */
	uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

	/* Transmit and receive ring buffers */
	RINGBUFF_T txring, rxring;
#endif


#if USE_ADC
	//DMA_TransferDescriptor_t DMA_descriptor_ADC;
	volatile uint32_t dma_memory_adc[ADC_DMA_CANT_MUESTRAS];
#endif


#if USE_DAC
	//DMA_TransferDescriptor_t DMA_descriptor_DAC;
	volatile uint16_t dma_memory_dac[DAC_DMA_CANT_MUESTRAS];
#endif
