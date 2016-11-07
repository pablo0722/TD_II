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
				if(dma_adc_ext_status == PINGPONG_ADC_TRANSFIRIENDO_A)	// Si SOLO estaba transfiriendo buffer A, ya termino de transferir. Hago transfer B y proceso A
				{
					dma_adc_ext_status = PINGPONG_ADC_TRANS_B_PROC_A;

					dma_adc_ext_memory = dma_adc_ext_memory_A;
					dma_adc_ext_descriptor = &dma_adc_ext_descriptor_A;

					Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_ext_canal,
											&dma_adc_ext_descriptor_B,
											GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
				}
				else if(dma_adc_ext_status == PINGPONG_ADC_TRANSFIRIENDO_B)	// Si SOLO estaba transfiriendo buffer B, ya termino de transferir. Hago transfer A y proceso B
				{
					dma_adc_ext_status = PINGPONG_ADC_TRANS_A_PROC_B;

					dma_adc_ext_memory = dma_adc_ext_memory_B;
					dma_adc_ext_descriptor = &dma_adc_ext_descriptor_B;

					Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_ext_canal,
											&dma_adc_ext_descriptor_A,
											GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
				}
				else
				{
					// Si termino de transferir antes de terminar procesamiento, doy una senal con PINGPONG_PROC2ERR para que
					// se continue con la transferencia luego de terminar procesamiento
					PINGPONG_ADC_PROC2ERR(dma_adc_ext_status);

					#if DEBUG_MODE
						printf("[warning] ADC externo interrumpio antes de terminar procesamiento\r\n");
					#endif
				}

				adc_pre_procesamiento();
			}
		#endif

		#if USE_DAC_INTERNO
			if(Chip_GPDMA_Interrupt(LPC_GPDMA, dma_dac_int_canal)) // Se fija si interrumpio el DAC interno
			{
				if(dma_dac_int_status == PINGPONG_DAC_RECIBIDO_A_ERR)
				{
					// si 'status == PINGPONG_DAC_RECIBIDO_A_ERR', envia por el DAC el buffer A procesado
					Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_dac_int_canal,
											(DMA_TransferDescriptor_t *) &dma_dac_int_descriptor_A,
											GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
				}
				else if(dma_dac_int_status == PINGPONG_DAC_RECIBIDO_B_ERR)
				{
					// si 'status == PINGPONG_DAC_RECIBIDO_B_ERR', envia por el DAC el buffer B procesado
					Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_dac_int_canal,
											(DMA_TransferDescriptor_t *) &dma_dac_int_descriptor_B,
											GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
				}

				dma_dac_int_status = PINGPONG_DAC_IDLE;
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
