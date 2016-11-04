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
		#if USE_ADC_EXTERNO
			if(Chip_GPDMA_Interrupt(LPC_GPDMA, dma_adc_ext_canal)) // Se fija si interrumpio el ADC externo
			{
				uint32_t *dma_adc_ext_memory;
				DMA_TransferDescriptor_t *dma_adc_ext_descriptor;

				if(dma_adc_ext_status == PINGPONG_TRANSFIRIENDO_A)	// Si SOLO estaba transfiriendo buffer A, ya termino de transferir. Hago transfer B y proceso A
				{
					dma_adc_ext_status = PINGPONG_TRANS_B_PROC_A;

					Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_ext_canal,
											&dma_adc_ext_descriptor,
											GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
				}
				else if(dma_adc_ext_status == PINGPONG_TRANSFIRIENDO_B)	// Si SOLO estaba transfiriendo buffer A, ya termino de transferir. Hago transfer B y proceso A
				{
					dma_adc_ext_status = PINGPONG_TRANS_A_PROC_B;

					Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_ext_canal,
											&dma_adc_ext_descriptor,
											GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
				}
				else
				{
					// Si termino de transferir antes de terminar procesamiento, doy una senal con PINGPONG_PROC2ERR para que
					// se continue con la transferencia luego de terminar procesamiento
					PINGPONG_PROC2ERR(dma_adc_ext_status);

					#if DEBUG_MODE
						printf("[warning] ADC externo interrumpio antes de terminar procesamiento\r\n");
					#endif
				}
			}
		#endif

		#if USE_DAC_INTERNO
			if(Chip_GPDMA_Interrupt(LPC_GPDMA, dma_dac_int_canal)) // Se fija si interrumpio el DAC interno
			{
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
