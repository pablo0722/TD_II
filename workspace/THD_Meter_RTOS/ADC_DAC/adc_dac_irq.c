/*
 * Interrupciones.c
 *
 *  Created on: 7 de oct. de 2016
 *      Author: Pablo
 */


#include "header.h"
#include "private/adc_dac_header_priv.h"


#if USE_DMA
	void DMA_IRQHandler(void)
	{
		#if USE_ADC_EXTERNO
			if(Chip_GPDMA_Interrupt(LPC_GPDMA, dma_adc_ext_canal)) // Se fija si interrumpio el ADC externo
			{
				if(dma_adc_ext_status == STATUS_ADC_TRANSFIRIENDO_A)	// Si SOLO estaba transfiriendo buffer A, ya termino de transferir.
				{
					dma_adc_ext_memory = dma_adc_ext_memory_A;

					if(dma_adc_ext_memory_B)								// Si hay para transferir por B, transfiero B y proceso A
					{
						dma_adc_ext_status = STATUS_ADC_TRANS_B_PROC_A;

						dma_adc_ext_descriptor = &dma_adc_ext_descriptor_A;

						Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_ext_canal,
												&dma_adc_ext_descriptor_B,
												GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
					}
					else													// Si NO hay para transferir por B, solo proceso A
					{
						dma_adc_ext_status = STATUS_ADC_TRANS_B_PROC_A_ERR;
					}
				}
				else if(dma_adc_ext_status == STATUS_ADC_TRANSFIRIENDO_B)	// Si SOLO estaba transfiriendo buffer B, ya termino de transferir.
				{
					dma_adc_ext_memory = dma_adc_ext_memory_B;
					dma_adc_ext_descriptor = &dma_adc_ext_descriptor_B;

					if(dma_adc_ext_memory_B)								// Si hay para transferir por A, transfiero A y proceso B
					{
						dma_adc_ext_status = STATUS_ADC_TRANS_A_PROC_B;

						Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_ext_canal,
												&dma_adc_ext_descriptor_A,
												GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
					}
					else													// Si NO hay para transferir por A, solo proceso B
					{
						dma_adc_ext_status = STATUS_ADC_TRANS_A_PROC_B_ERR;
					}
				}
				else
				{
					// Si termino de transferir antes de terminar procesamiento, doy una senal con PINGPONG_PROC2ERR para que
					// se continue con la transferencia luego de terminar procesamiento
					STATUS_ADC_PROC2ERR(dma_adc_ext_status);

					#if DEBUG_MODE
						printf("[warning] ADC externo interrumpio antes de terminar procesamiento\r\n");
					#endif
				}

				adc_ext_pre_procesamiento();
			}
		#endif

		#if USE_DAC_EXTERNO
			if(Chip_GPDMA_Interrupt(LPC_GPDMA, dma_dac_ext_canal)) // Se fija si interrumpio el DAC interno
			{
				BaseType_t pxHigherPiorityTaskWoken = pdFALSE;
				xSemaphoreGiveFromISR(sem_dac_ext_finish, &pxHigherPiorityTaskWoken);

				dma_dac_ext_status = STATUS_DAC_IDLE;

				portEND_SWITCHING_ISR(pxHigherPiorityTaskWoken);
			}
		#endif

		#if USE_DAC_INTERNO
			if(Chip_GPDMA_Interrupt(LPC_GPDMA, dma_dac_int_canal)) // Se fija si interrumpio el DAC interno
			{
				BaseType_t pxHigherPiorityTaskWoken = pdFALSE;
				xSemaphoreGiveFromISR(sem_dac_int_finish, &pxHigherPiorityTaskWoken);

				dma_dac_int_status = STATUS_DAC_IDLE;

				portEND_SWITCHING_ISR(pxHigherPiorityTaskWoken);
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
