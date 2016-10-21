/*
 * Interrupciones.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"



#if USE_DMA
	void DMA_IRQHandler(void)
	{
		Status transf_success;
		int i;

		#if USE_ADC_EXTERNO
			transf_success = Chip_GPDMA_Interrupt(LPC_GPDMA, ADC_DMA_CHANNEL);
			if (transf_success == SUCCESS) // Se fija si interrumpio el ADC
			{
					// Copiar buffer del adc al del dac
				for(i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
				{
					dma_memory_dac[i] = /*ADC_DR_RESULT*/(dma_memory_adc[i] << 8);
				}

					// Cuando interrumpe el ADC, envia al DAC
				transf_success = Chip_GPDMA_Transfer(LPC_GPDMA, canal_dac,
						(uint32_t) dma_memory_dac, (uint32_t) (GPDMA_CONN_I2S_Channel_1),
						GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, DAC_DMA_CANT_MUESTRAS);
				if(transf_success == ERROR)
				{
					transf_success = SUCCESS;
				}
			}
			Chip_GPDMA_ClearIntPending (LPC_GPDMA, GPDMA_STATCLR_INTTC, ADC_DMA_CHANNEL);
		#endif

		#if USE_DAC_EXTERNO
			transf_success = Chip_GPDMA_Interrupt(LPC_GPDMA, DAC_DMA_CHANNEL);
			if (transf_success == SUCCESS) // Se fija si interrumpio el DAC
			{
					// Cuando interrumpe el DAC, recibo desde el ADC
				transf_success = Chip_GPDMA_Transfer(LPC_GPDMA, canal_adc,
						(uint32_t) (GPDMA_CONN_I2S_Channel_1), (uint32_t) dma_memory_adc,
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


#if (USE_ADC_EXTERNO_INTERRUPCION)||(USE_DAC_EXTERNO_INTERRUPCION)
	void I2S_IRQHandler(void)
	{
		if(Chip_I2S_GetRxLevel(LPC_I2S))
		{
			data = Chip_I2S_Receive(LPC_I2S);
			adcFlag=1;
		}

		Chip_I2S_Send(LPC_I2S, (data << 6) );
	}
#endif
