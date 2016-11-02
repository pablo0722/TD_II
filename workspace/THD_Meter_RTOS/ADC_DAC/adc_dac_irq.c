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
		#if DEBUG_MODE
			Status transf_success;
		#endif

		#if USE_ADC
			if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc)) // Se fija si interrumpio el ADC
			{
				uint32_t *dma_memory_adc = NULL;
				DMA_TransferDescriptor_t *DMA_descriptor_DAC
				if(adc_buffer == BUFFER_A_PINGPONG)
				{
					dma_memory_adc = dma_memory_adc_A;
					DMA_descriptor_DAC = &DMA_descriptor_DAC_A;
				}
				else
				{
					uint32_t *dma_memory_adc = dma_memory_adc_B;
					DMA_descriptor_DAC = &DMA_descriptor_DAC_B;
				}

					// Shiftear el dato antes de enviar por DAC
				for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
				{
					dma_memory_dac[i] = set_data(dma_memory_adc[i]);
				}

					// Cuando interrumpe el ADC, envia al DAC
				#if DEBUG_MODE
					transf_success =
				#endif

				#if USE_DAC
					Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_dac,
											DMA_descriptor_DAC,
											GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
				#else
					Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
											&DMA_descriptor_DAC,
											GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
				#endif

				#if DEBUG_MODE
					if(transf_success == ERROR)
					{
						printf("[error] interrupcion DMA:");
						printf("%d, %s", __LINE__, __FILE__);
					}
				#endif
			}
		#endif

		#if USE_DAC
			if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac)) // Se fija si interrumpio el DAC
			{
					// Cuando interrumpe el DAC, recibo desde el ADC
				#if DEBUG_MODE
					transf_success =
				#endif

				Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
										&DMA_descriptor_ADC,
										GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);

				#if DEBUG_MODE
					if(transf_success == ERROR)
					{
						printf("[error] interrupcion DMA:");
						printf("%d, %s", __LINE__, __FILE__);
					}
				#endif
			}
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
