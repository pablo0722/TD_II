/*
 * adc_dac_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"


uint16_t dac_int_set_data(uint32_t data)
{
	if(data < 0)
		data = (data >> 8);
	else
	{
		data = data >> 8 ;
//		data &= (0x00FFFFFF);
	}

	if(data < 16777216)		// 2^24
		data = data + 8388608;
	else
		data = data - 8388608;

	data &= (0x00FFFFFF);

	return (data >> 8);
}

#if USE_ADC_EXTERNO
	void main_adc()
	{
		if(PINGPONG_ISPROC(dma_adc_ext_status)) // Si ya recibi del ADC, proceso la senal
		{
			uint32_t *dma_adc_ext_memory;
			DMA_TransferDescriptor_t *dma_adc_ext_descriptor;
			uint16_t *dma_dac_int_memory;
			DMA_TransferDescriptor_t *dma_dac_int_descriptor;

			if(dma_adc_ext_status == PINGPONG_TRANS_B_PROC_A)
			{
				// proceso buffer A
				dma_adc_ext_memory = dma_adc_ext_memory_A;
				dma_adc_ext_descriptor = &dma_adc_ext_descriptor_A;
				dma_dac_int_memory = dma_dac_int_memory_A;
				dma_dac_int_descriptor = &dma_dac_int_descriptor_A;
			}
			else if(dma_adc_ext_status == PINGPONG_TRANS_A_PROC_B)
			{
				// proceso buffer B
				dma_adc_ext_memory = dma_adc_ext_memory_B;
				dma_adc_ext_descriptor = &dma_adc_ext_descriptor_B;
				dma_dac_int_memory = dma_dac_int_memory_B;
				dma_dac_int_descriptor = &dma_dac_int_descriptor_B;
			}

				// Shiftear el dato antes procesar (porque recibo 24 bits)
			for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
			{
				dma_adc_ext_memory[i] = dma_adc_ext_memory[i] >> 8;
			}


			// *** PROCESO SENAL 'dma_adc_ext_memory' *** //

			// *** ********* FIN DE PROCESO ********* *** //


				// acomodar el dato antes de enviar por DAC
			for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
			{
				dma_dac_int_memory[i] = dac_int_set_data(dma_adc_ext_memory[i]);
			}

			Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_dac_int_canal,
									dma_dac_int_descriptor,
									GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);

			if(PINGPONG_ISERR(dma_adc_ext_status))
			{
				// Si termino de transferir antes de terminar procesamiento, se debe continuar con la transferencia
				Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_ext_canal,
										&dma_adc_ext_descriptor,
										GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
			}

			PINGPONG_PROC2TRANS(dma_adc_ext_status);
		}
	}
#endif

#if USE_DAC_INTERNO
	void main_dac()
	{
			// Shiftear el dato antes de enviar por DAC
		for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
		{
			dma_dac_int_memory[i] = set_data(dma_adc_ext_memory[i]);
		}

			// Cuando interrumpe el ADC, envia al DAC
		#if USE_DAC_INTERNO
			Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_dac_int_canal,
									dma_dac_int_descriptor,
									GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
		#endif
	}
#endif

