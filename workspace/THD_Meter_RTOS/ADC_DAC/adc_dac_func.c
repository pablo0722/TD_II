/*
 * adc_dac_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"
#include "private/adc_dac_header_priv.h"



#if USE_ADC_EXTERNO
	void adc_ext_prepare(volatile uint32_t *buffer_A, 	// Prepara el buffer para poder recibir desde el ADC
					 	 volatile uint32_t *buffer_B)
	{
		dma_adc_ext_memory_A = buffer_A;
		dma_adc_ext_memory_B = buffer_B;

		// Preparo el descriptor para el BUFFER_A
		Chip_GPDMA_PrepareDescriptor(LPC_GPDMA,
									(DMA_TransferDescriptor_t *) &dma_adc_ext_descriptor_A,
									(uint32_t) GPDMA_CONN_I2S_Channel_1,
									(uint32_t) dma_adc_ext_memory_A,
									ADC_DMA_CANT_MUESTRAS,
									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
									NULL);
		dma_adc_ext_descriptor_A.src = GPDMA_CONN_I2S_Channel_1;

		// Preparo el descriptor para el BUFFER_B
		Chip_GPDMA_PrepareDescriptor(LPC_GPDMA,
									(DMA_TransferDescriptor_t *) &dma_adc_ext_descriptor_B,
									(uint32_t) GPDMA_CONN_I2S_Channel_1,
									(uint32_t) dma_adc_ext_memory_B,
									ADC_DMA_CANT_MUESTRAS,
									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
									NULL);
		dma_adc_ext_descriptor_B.src = GPDMA_CONN_I2S_Channel_1;

		dma_adc_ext_status = STATUS_ADC_IDLE;

		if(buffer_B)
			adc_ext_start();
	}

	void adc_ext_start()
	{
		if(dma_adc_ext_status == STATUS_ADC_IDLE)
		{
			// Inicio la transmición del ADC -> MEMORY usando el BUFFER_A
			Chip_GPDMA_SGTransfer(LPC_GPDMA,
									dma_adc_ext_canal,
									(DMA_TransferDescriptor_t *) &dma_adc_ext_descriptor_A,
									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
			dma_adc_ext_status = STATUS_ADC_TRANSFIRIENDO_A;
		}
	}

	void adc_ext_post_procesamiento()
	{
		if(dma_adc_ext_memory_B)
		{
			if(STATUS_ADC_ISERR(dma_adc_ext_status))
			{
				// Si termino de transferir antes de terminar procesamiento, se debe continuar con la transferencia
				Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_ext_canal,
										dma_adc_ext_descriptor,
										GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
			}

			dma_adc_ext_memory = NULL;
			dma_adc_ext_descriptor = NULL;

			STATUS_ADC_PROC2TRANS(dma_adc_ext_status);
		}
		else
		{
			dma_adc_ext_status = STATUS_ADC_IDLE;
		}
	}
#endif

#if USE_ADC_INTERNO
	void adc_int_prepare(volatile uint32_t *buffer_A, 	// Prepara el buffer para poder recibir desde el ADC
					 	 volatile uint32_t *buffer_B)
	{
		dma_adc_int_memory_A = buffer_A;
		dma_adc_int_memory_B = buffer_B;

		// Preparo el descriptor para el BUFFER_A
		Chip_GPDMA_PrepareDescriptor(LPC_GPDMA,
									(DMA_TransferDescriptor_t *) &dma_adc_int_descriptor_A,
									(uint32_t) GPDMA_CONN_I2S_Channel_1,
									(uint32_t) dma_adc_int_memory_A,
									ADC_DMA_CANT_MUESTRAS,
									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
									NULL);
		dma_adc_int_descriptor_A.src = GPDMA_CONN_I2S_Channel_1;

		// Preparo el descriptor para el BUFFER_B
		Chip_GPDMA_PrepareDescriptor(LPC_GPDMA,
									(DMA_TransferDescriptor_t *) &dma_adc_int_descriptor_B,
									(uint32_t) GPDMA_CONN_I2S_Channel_1,
									(uint32_t) dma_adc_int_memory_B,
									ADC_DMA_CANT_MUESTRAS,
									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA,
									NULL);
		dma_adc_int_descriptor_B.src = GPDMA_CONN_I2S_Channel_1;

		dma_adc_int_status = STATUS_ADC_IDLE;

		if(buffer_B)
			adc_int_start();
	}

	void adc_int_start()
	{
		if(dma_adc_int_status == STATUS_ADC_IDLE)
		{
			// Inicio la transmición del ADC -> MEMORY usando el BUFFER_A
			Chip_GPDMA_SGTransfer(LPC_GPDMA,
									dma_adc_int_canal,
									(DMA_TransferDescriptor_t *) &dma_adc_int_descriptor_A,
									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
			dma_adc_int_status = STATUS_ADC_TRANSFIRIENDO_A;
		}
	}

	void adc_int_post_procesamiento()
	{
		if(dma_adc_int_memory_B)
		{
			if(STATUS_ADC_ISERR(dma_adc_int_status))
			{
				// Si termino de transferir antes de terminar procesamiento, se debe continuar con la transferencia
				Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_adc_int_canal,
										dma_adc_int_descriptor,
										GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
			}

			dma_adc_int_memory = NULL;
			dma_adc_int_descriptor = NULL;

			STATUS_ADC_PROC2TRANS(dma_adc_int_status);
		}
		else
		{
			dma_adc_int_status = STATUS_ADC_IDLE;
		}
	}
#endif


#if USE_DAC_EXTERNO
	uint16_t dac_ext_set_data(uint32_t data)
	{
		return (data >> 8);
	}

	void dac_ext_prepare(volatile uint16_t *buffer)
	{
		dma_dac_ext_memory = buffer;

		// Preparo el descriptor para el BUFFER_A
		Chip_GPDMA_PrepareDescriptor(LPC_GPDMA,
									(DMA_TransferDescriptor_t *) &dma_dac_ext_descriptor,
									(uint32_t) dma_dac_ext_memory,
									(uint32_t) GPDMA_CONN_DAC,
									DAC_DMA_CANT_MUESTRAS,
									GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
									NULL);
		dma_dac_ext_descriptor.dst = GPDMA_CONN_DAC;
	}

	bool dac_ext_disponible()
	{
		if(dma_dac_ext_status == STATUS_DAC_IDLE)
			return true;
		return false;
	}

	void dac_ext_send()
	{
			// acomodar el dato antes de enviar por DAC
		for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
		{
			dma_dac_ext_memory[i] = dac_ext_set_data(dma_dac_ext_memory[i]);
		}

		while(!dac_ext_disponible());	// Espera hasta que el dac este disponible para enviar

			// Si el DAC esta disponible para enviar, envia el buffer y pone 'status = STATUS_DAC_TRANSFIRIENDO'
		Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_dac_ext_canal,
								&dma_dac_ext_descriptor,
								GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);

		dma_dac_ext_status = STATUS_DAC_TRANSFIRIENDO;
	}
#endif


#if USE_DAC_INTERNO
	uint16_t dac_int_set_data(uint32_t data)
	{
		return (data >> 8);
	}

	void dac_int_prepare(volatile uint16_t *buffer)
	{
		dma_dac_int_memory = buffer;

		// Preparo el descriptor para el BUFFER_A
		Chip_GPDMA_PrepareDescriptor(LPC_GPDMA,
									(DMA_TransferDescriptor_t *) &dma_dac_int_descriptor,
									(uint32_t) dma_dac_int_memory,
									(uint32_t) GPDMA_CONN_DAC,
									DAC_DMA_CANT_MUESTRAS,
									GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
									NULL);
		dma_dac_int_descriptor.dst = GPDMA_CONN_DAC;
	}

	bool dac_int_disponible()
	{
		if(dma_dac_int_status == STATUS_DAC_IDLE)
			return true;
		return false;
	}

	void dac_int_send()
	{
			// acomodar el dato antes de enviar por DAC
		for(int i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
		{
			//dma_dac_int_memory[i] = dac_int_set_data(dma_dac_int_memory[i]);
		}

		//xSemaphoreTake(sem_dac_int_finish, portMAX_DELAY);

		while(!dac_int_disponible());	// Espera hasta que el dac este disponible para enviar

			// Si el DAC esta disponible para enviar, envia el buffer y pone 'status = STATUS_DAC_TRANSFIRIENDO'
		Chip_GPDMA_SGTransfer(LPC_GPDMA, dma_dac_int_canal,
								&dma_dac_int_descriptor,
								GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);

		dma_dac_int_status = STATUS_DAC_TRANSFIRIENDO;
	}
#endif

