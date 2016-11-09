/*
 * adc_dac_main.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"
#include "adc_dac_header_priv.h"


#if (USE_DMA)
	void dma_init()
	{
		/* *** Caracteristicas del DMA:
		 * !!!!!!!!! EL DMA ES UNICAMENTE EN MODO BURST (NO MODO SINGLE) !!!!!!!!!
		 *
		 * Eight DMA channels. Each channel can support an unidirectional transfer.
		 *
		 * Memory-to-memory, memory-to-peripheral, and peripheral-to-memory transfers are supported.
		 *
		 * GPDMA supports the SSP, I2S, UART, A/D Converter, and D/A Converter peripherals.
		 *
		 * DMA can also be triggered by a timer match condition.
		 *
		 * Memory-to-memory transfers and transfers to or from GPIO are also supported.
		 *
		 * 32-bit AHB master bus width.
		 *
		 * Supports 8-bit, 16-bit, and 32-bit wide transactions.
		 *
		 * Internal four-word FIFO per channel.
		 *
		 * Programmable DMA burst size. The DMA burst size can be programmed to more efficiently transfer data.
		 *
		 * DMA can operate in Sleep mode. (Note that in Sleep mode the GPDMA cannot access the flash memory).
		 *
		 * Big-endian and little-endian support. The DMA Controller defaults to little-endian mode on reset.
		 * * Internally the DMA Controller treats all data as a stream of bytes instead of 16-bit or 32-bit
		 * * quantities. This means that when performing mixed-endian activity, where the endianness
		 * * of the source and destination are different, byte swapping of the data within the 32-bit data
		 * * bus is observed.
		 *
		 * AHB master interface is capable of dealing with all types of AHB transactions, including:
		 * * Split, retry, and error responses from slaves.
		 * * (If a peripheral performs a split or retry, the DMA Controller stalls and waits until the transaction can complete)
		 * * Locked transfers for source and destination of each stream.
		 * * Setting of protection bits for transfers on each stream.
		 *
		 * An interrupt to the processor can be generated on a DMA completion or when a DMA error has occurred.
		 * * [error] An error during a DMA transfer is flagged directly by the peripheral by asserting an Error
		 * * response on the AHB bus during the transfer. The DMA Controller automatically disables
		 * * the DMA stream after the current transfer has completed, and can optionally generate an
		 * * error interrupt to the CPU. This error interrupt can be masked.
		 * * [completion] A combined interrupt output is generated as an OR function of the individual interrupt
		 * * requests of the DMA Controller and is connected to the interrupt controller.
		 *
		 * DMA channel priority is fixed. DMA channel 0 has the highest priority and DMA channel 7
		 * * has the lowest priority.
		 * * If the DMA Controller is transferring data for the lower priority channel and then the higher
		 * * priority channel goes active, it completes the number of transfers delegated to the master
		 * * interface by the lower priority channel before switching over to transfer data for the higher
		 * * priority channel. Transfers delegated to the master interface are staged in the DMA
		 * * channel FIFO, so the amount of data that needs to transfer could be as large as a 4
		 * * words.
		 * * It is recommended that memory-to-memory transactions use the lowest priority channel.
		 *
		 * Registros:
		 * * DMACBREQ[15:0] — Burst request signals. These cause a programmed burst number of data to be transferred.
		 * * DMACSREQ[15:0] — Single transfer request signals. These cause a single data to be transferred. The DMA controller transfers a single transfer to or from the peripheral.
		 * * DMACLBREQ[15:0] — Last burst request signals.
		 * * DMACLSREQ[15:0] — Last single transfer request signals.
		 * * * Note that peripherals on this device do not support “last” request types, and many do not support both single and burst request types.
		 * * DMACCLR[15:0] — DMA clear or acknowledge signals. The DMACCLR signal is used by the DMA controller to acknowledge a DMA request from the peripheral.
		 * * DMACTC[15:0] — DMA terminal count signals. The DMACTC signal can be used by the DMA controller to indicate to the peripheral that the DMA transfer is complete.
		 */

		#if DEBUG_MODE
			printf("[info] Init DMA \r\n");
		#endif

		Chip_GPDMA_Init(LPC_GPDMA);

			// Setting GPDMA interrupt
		NVIC_DisableIRQ(DMA_IRQn);
		NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));
		NVIC_EnableIRQ(DMA_IRQn);


		#if (USE_ADC_EXTERNO)
			#if DEBUG_MODE
				printf("\t init buffers ADC externo \r\n");
			#endif

			// Pido un canal disponible al GPDMA para el ADC
			dma_adc_ext_canal = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);

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

			// Inicio la transmición del ADC -> MEMORY usando el BUFFER_A
			Chip_GPDMA_SGTransfer(LPC_GPDMA,
									dma_adc_ext_canal,
									(DMA_TransferDescriptor_t *) &dma_adc_ext_descriptor_A,
									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
			dma_adc_ext_status = PINGPONG_ADC_TRANSFIRIENDO_A;
		#elif (USE_ADC_INTERNO)
		#endif

		#if (USE_DAC_EXTERNO)
		#elif (USE_DAC_INTERNO)
			#if DEBUG_MODE
				printf("\t init buffers DAC interno \r\n");
			#endif

			// Pido un canal disponible al GPDMA para el DAC
			dma_dac_int_canal = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);

			// Preparo el descriptor para el BUFFER_A
			Chip_GPDMA_PrepareDescriptor(LPC_GPDMA,
										(DMA_TransferDescriptor_t *) &dma_dac_int_descriptor_A,
										(uint32_t) dma_dac_int_memory_A,
										(uint32_t) GPDMA_CONN_DAC,
										DAC_DMA_CANT_MUESTRAS,
										GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
										NULL);
			dma_dac_int_descriptor_A.dst = GPDMA_CONN_DAC;

			// Preparo el descriptor para el BUFFER_B
			Chip_GPDMA_PrepareDescriptor(LPC_GPDMA,
										(DMA_TransferDescriptor_t *) &dma_dac_int_descriptor_B,
										(uint32_t) dma_dac_int_memory_B,
										(uint32_t) GPDMA_CONN_DAC,
										DAC_DMA_CANT_MUESTRAS,
										GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
										NULL);
			dma_dac_int_descriptor_B.dst = GPDMA_CONN_DAC;
		#endif
	}
#endif


#if USE_DAC_INTERNO
	STATIC INLINE uint16_t dac_int_set_data(uint32_t data)
	{
		return (data >> 8);
	}
#endif


#if USE_ADC_EXTERNO
	void adc_post_procesamiento()
	{
			// acomodar el dato antes de enviar por DAC
		#if USE_DAC_INTERNO
			if(dac_send)
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

