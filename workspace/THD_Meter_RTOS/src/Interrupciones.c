/*
 * Interrupciones.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


#if USE_UART
	/**
	 * @brief	UART N interrupt handler using ring buffers
	 * @return	Nothing
	 */
	#if USE_UART0
		void UART0_IRQHandler(void)
		{
			Chip_UART_IRQRBHandler(LPC_UART0, &rxring, &txring);

			#if UART_BY_VECTOR
				uint8_t error = 0;
				static uint16_t idx=0;
				static char pingpong_AB = 0; // dice si se tiene q llenar el buffer A (=0) o el B (=1);
				uint8_t read_char = 0;
				int bytes = Chip_UART_ReadRB(LPC_UART0, &rxring, &read_char, 1);

				if(bytes > 0)
				{
					char *uart_in_p;
					if(!pingpong_AB)
						uart_in_p = (char *) uart_in_A;	// uso puntero a char para guardar byte por byte desde la uart al vector de ping-pong A
					else
						uart_in_p = (char *) uart_in_B;	// uso puntero a char para guardar byte por byte desde la uart al vector de ping-pong B

					uart_in_p[idx] = read_char;
					idx++;
					idx %= UART_SIZE;

					if(idx==0)
					{
						if(uart_rx_done)
						{
							if(!error)
								error = 1;	// Si se lleno el bufer antes que se termine de usar, error
							#if DEBUG_MODE
								printf("[error] UART0_IRQ: \r\n");
								printf("\t \"%s\", %d \r\n", __FILE__, __LINE__);
							#endif
						}
						uart_rx_done = UART_RX_DONE_MAX;
						if(!pingpong_AB)
							uart_in = uart_in_A;
						else
							uart_in = uart_in_B;

						#if DEBUG_MODE
							printf("[info] UART0_IRQ: \r\n");
							printf("\t recibido: \"%.*s\" \r\n", UART_SIZE, (char *)uart_in);
						#endif
					}
				}
			#endif
		}
	#endif
#endif


#if (USE_ADC) || (USE_DAC)
	void DMA_IRQHandler(void)
	{
		Status transf_success;


		#if USE_ADC
			transf_success = Chip_GPDMA_Interrupt(LPC_GPDMA, ADC_DMA_CHANNEL);
			if (transf_success == SUCCESS)
			{
					// Copiar buffer del adc al del dac
				for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
				{
					dma_memory_dac[i] = /*ADC_DR_RESULT*/((dma_memory_adc[i] & 0xFFFFFFFF) >> 0) & 0xFFFFFFFF;
				}

					// Cuando interrumpe el ADC, envia al DAC
				transf_success = Chip_GPDMA_Transfer(LPC_GPDMA, DAC_DMA_CHANNEL,
						(uint32_t) dma_memory_dac, (uint32_t) (GPDMA_CONN_DAC),
						GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, DAC_DMA_CANT_MUESTRAS);
				if(transf_success == ERROR)
				{
					transf_success = SUCCESS;
				}
			}
			Chip_GPDMA_ClearIntPending (LPC_GPDMA, GPDMA_STATCLR_INTTC, ADC_DMA_CHANNEL);
		#endif


		#if USE_DAC
			transf_success = Chip_GPDMA_Interrupt(LPC_GPDMA, DAC_DMA_CHANNEL);
			if (transf_success == SUCCESS)
			{
					// Cuando interrumpe el DAC, recibo desde el ADC
				transf_success = Chip_GPDMA_Transfer(LPC_GPDMA, ADC_DMA_CHANNEL,
						(uint32_t) (GPDMA_CONN_ADC), (uint32_t) dma_memory_adc,
						GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, ADC_DMA_CANT_MUESTRAS);
				if(transf_success == ERROR)
				{
					transf_success = SUCCESS;
				}
			}
			Chip_GPDMA_ClearIntPending (LPC_GPDMA, GPDMA_STATCLR_INTTC, DAC_DMA_CHANNEL);
		#endif
	}
#endif

