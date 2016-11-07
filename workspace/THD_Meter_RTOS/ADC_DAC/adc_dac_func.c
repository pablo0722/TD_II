/*
 * adc_dac_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_ADC_EXTERNO
	STATIC INLINE uint32_t adc_ext_set_data(uint32_t data)
	{
			// Shiftea 8 veces para acomodar los 24 bits adquiridos en la parte baja del uint32_t. asi tengo 8 bits de overflow.
			// 		Nota: Al ser uint32_t, se hace un shifteo logico (completa con ceros).
			// Luego, invierte el bit de signo para convertir de 'signed' (como toma el adc) a unsigned
		return ((data >> 8) ^ 0x00800000);
	}
#endif

#if USE_DAC_INTERNO
	STATIC INLINE uint16_t dac_int_set_data(uint32_t data)
	{
		return (data >> 8);
	}
#endif


#if USE_ADC_EXTERNO
	void adc_pre_procesamiento()
	{
		if(PINGPONG_ADC_ISPROC(dma_adc_ext_status)) // Si ya recibi del ADC, proceso la senal
		{
				// Acomodar el dato del ADC antes de procesar
			for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
			{
				dma_adc_ext_memory[i] = adc_ext_set_data(dma_adc_ext_memory[i]);
			}

			#if USE_RTOS
				xSemaphoreGive(sem_adc_proc);
			#endif
		}
	}


	void adc_post_procesamiento()
	{
			// acomodar el dato antes de enviar por DAC
		#if USE_DAC_INTERNO
			if(flag_use_dac)
			{
				volatile uint16_t *dma_dac_int_memory;
				DMA_TransferDescriptor_t *dma_dac_int_descriptor;
				uint8_t pingpong_dac_transfiriendo;

				if(dma_adc_ext_status == PINGPONG_ADC_TRANS_B_PROC_A)
				{
						// proceso buffer A
					dma_dac_int_memory = dma_dac_int_memory_A;
					dma_dac_int_descriptor = &dma_dac_int_descriptor_A;
					pingpong_dac_transfiriendo = PINGPONG_DAC_TRANSFIRIENDO_A;
				}
				else if(dma_adc_ext_status == PINGPONG_ADC_TRANS_A_PROC_B)
				{
						// proceso buffer B
					dma_dac_int_memory = dma_dac_int_memory_B;
					dma_dac_int_descriptor = &dma_dac_int_descriptor_B;
					pingpong_dac_transfiriendo = PINGPONG_DAC_TRANSFIRIENDO_B;
				}


				for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
				{
					dma_dac_int_memory[i] = dac_int_set_data(dma_adc_ext_memory[i]);
				}

				if(dma_dac_int_status == PINGPONG_DAC_IDLE)
				{
					// si 'status == PINGPONG_DAC_IDLE', envia por el DAC el buffer X procesado y pone 'status = PINGPONG_DAC_TRANSFIRIENDO_X'
					Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_dac_int_canal,
											dma_dac_int_descriptor,
											GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);

					dma_dac_int_status = pingpong_dac_transfiriendo;
				}
				else
				{
					// si 'status == PINGPONG_DAC_TRANSFIRIENDO_Y' pone 'status = PINGPONG_DAC_RECIBIDO_X_ERR'
					dma_dac_int_status = PINGPONG_DAC_TRANS2ERR(pingpong_dac_transfiriendo);
				}
			}
		#endif

		if(PINGPONG_ADC_ISERR(dma_adc_ext_status))
		{
			// Si termino de transferir antes de terminar procesamiento, se debe continuar con la transferencia
			Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_ext_canal,
									dma_adc_ext_descriptor,
									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
		}

		dma_adc_ext_memory = NULL;
		dma_adc_ext_descriptor = NULL;

		PINGPONG_ADC_PROC2TRANS(dma_adc_ext_status);
	}
#endif

