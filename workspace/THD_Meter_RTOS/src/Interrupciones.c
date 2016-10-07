/*
 * Interrupciones.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"


#ifdef USE_UART
	/**
	 * @brief	UART 1 interrupt handler using ring buffers
	 * @return	Nothing
	 */
	void UART0_IRQHandler(void)
	{
		static uint16_t idx=0;
		uint8_t read_char = 0;

		Chip_UART_IRQRBHandler(LPC_UART0, &rxring, &txring);

		int bytes = Chip_UART_ReadRB(LPC_UART0, &rxring, &read_char, 1);

		if(bytes > 0)
		{
			char *SignalIn_p = (char *) mSignalIn;
			SignalIn_p[idx] = read_char;
			idx++;
			idx %= LENGTH_SAMPLES*4; //el "*4" es porq son int_32 y recibo de a int_8

			if(idx==0)
			{
				signalin_flag = 1;
			}
		}
	}
#endif


#if defined(USE_ADC) || defined(USE_DAC)
	void DMA_IRQHandler(void)
	{
		Status transf_success;


		#ifdef USE_ADC
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


		#ifdef USE_DAC
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

