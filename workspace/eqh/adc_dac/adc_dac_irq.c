/*
 * adc_dac_irq.c
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */



//uint8_t buffer_A[234];
//uint8_t buffer_B[234];
//uint8_t *buffer=NULL;



#include "header.h"



volatile uint32_t volumen = 0;
volatile uint32_t direccion = 0;

q31_t fft_thd;



//uint8_t buffer_ready = 0;
#if USE_DMA

volatile uint32_t counter = 0;

	void DMA_IRQHandler(void)
	{

		#if USE_RTOS
				portBASE_TYPE HPTW = pdFALSE;
				int buffer_ready = 0;
				int i = 0;
		#else
				int i = 0;
		#endif

		#if (USE_ADC)
			#if (USE_BUFFER_SERIE)


				uint32_t aux = 0;



				if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc)) // Se fija si interrumpio el ADC
				{

					// Shiftear el dato antes de enviar por DAC

//						if(flag_volumen_up = 1)
//							direccion = 1;

//						for( int i=0; i<ADC_DMA_CANT_MUESTRAS; i++)
//						{
//							if(direccion == 1)
//							{
								//distorsion(dma_memory_adc_BUFF, dma_memory_dac_BUFF, ADC_DMA_CANT_MUESTRAS, 2);
//								(q31_t) aux = distorsion((q15_t)aux,(q15_t)0.5);
//								aux = eco_iir((q31_t) aux, (q31_t) 0x10000000, (uint8_t) 4);
//								aux = reverb( aux, (q31_t) 1, (uint8_t) 1);
//								aux = flanger((q31_t) aux, (q31_t) 0, (uint16_t) 0.6, (uint8_t) 1);
//							}
					/*
						for(int i=0; i<ADC_DMA_CANT_MUESTRAS; i++)
						{
							dma_memory_dac_BUFF[i] = dma_memory_adc_BUFF[i];
						}
						*/


//							counter = 256 + counter;
//							if(counter > 8388608)	counter == 0;
//							dma_memory_dac_BUFF[i] = (counter << 8);

//					}


						q31_t fft_max;
						uint32_t fft_max_idx;
						q31_t fft_max_efectivo = 0;
						q31_t fft_arm_efectivo = 0;
						q63_t memory_aux[FFT_SIZE];

						arm_dot_prod_q31(dma_memory_adc_BUFF, fft_window, FFT_SIZE, memory_aux);
						for(uint32_t i=0; i<FFT_SIZE; i++)
						{
							dma_memory_dac_BUFF[i] = memory_aux[i] >> 32;
						}
						fft_toCmplx(dma_memory_dac_BUFF, dma_memory_dac_BUFF);
						fft_toDep(dma_memory_dac_BUFF, dma_memory_dac_BUFF);
						arm_max_q31(dma_memory_dac_BUFF, FFT_SIZE/2, &fft_max, &fft_max_idx);

						if(fft_max_idx > 6)
						{
							fft_max_efectivo = 	dma_memory_dac_BUFF[fft_max_idx-6] +
												dma_memory_dac_BUFF[fft_max_idx-5] +
												dma_memory_dac_BUFF[fft_max_idx-4] +
												dma_memory_dac_BUFF[fft_max_idx-3] +
												dma_memory_dac_BUFF[fft_max_idx-2] +
												dma_memory_dac_BUFF[fft_max_idx-1] +
												dma_memory_dac_BUFF[fft_max_idx]   +
												dma_memory_dac_BUFF[fft_max_idx+1] +
												dma_memory_dac_BUFF[fft_max_idx+2] +
												dma_memory_dac_BUFF[fft_max_idx+3] +
												dma_memory_dac_BUFF[fft_max_idx+4] +
												dma_memory_dac_BUFF[fft_max_idx+5] +
												dma_memory_dac_BUFF[fft_max_idx+6];
						}

						for(uint32_t i=fft_max_idx*2; i+6<FFT_SIZE/2; i+=fft_max_idx)
						{
							fft_arm_efectivo +=	dma_memory_dac_BUFF[i-6] +
												dma_memory_dac_BUFF[i-5] +
												dma_memory_dac_BUFF[i-4] +
												dma_memory_dac_BUFF[i-3] +
												dma_memory_dac_BUFF[i-2] +
												dma_memory_dac_BUFF[i-1] +
												dma_memory_dac_BUFF[i]   +
												dma_memory_dac_BUFF[i+1] +
												dma_memory_dac_BUFF[i+2] +
												dma_memory_dac_BUFF[i+3] +
												dma_memory_dac_BUFF[i+4] +
												dma_memory_dac_BUFF[i+5] +
												dma_memory_dac_BUFF[i+6];
						}

						arm_sqrt_q31(fft_arm_efectivo/fft_max, &fft_thd);


						// Transmito el BUFFER
						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_dac,
												&DMA_descriptor_DAC_BUFFER,
												GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
	//				}

				}
				if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac)) // Se fija si interrumpio el DAC
				{
					Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
											&DMA_descriptor_ADC_BUFFER,
											GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
				}
			#endif

			#if (USE_BUFFER_PARALELO)

				if( LPC_GPDMA->INTTCSTAT == 0x3 )
					CONT_B = 7;


				switch(ESTADO_BUFFERS)
				{
//				case IDLE_BUFF :
//					break;
				case BUSY_BUFF_A_ADC_DAC :								// BUFFER A			---			ADC		=		!!!!			---			DAC		=		!!!!


					CONT_BUSY_BUFF_A_ADC_DAC ++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		!!!!
					{
//						BUFFER_ADC_A = READY;
						ESTADO_BUFFERS = BUSY_BUFF_A_DAC;
					}
					else if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		!!!!			---			DAC		=		READY
					{
//						BUFFER_DAC_A = READY;
						if(ESTADO_BUFFERS == BUSY_BUFF_A_ADC)
							ESTADO_BUFFERS = READY_BUFF_A;
						else
							ESTADO_BUFFERS = BUSY_BUFF_A_ADC;
					}
					else
						while(1);
					break;
				case BUSY_BUFF_A_DAC :									// BUFFER A			---			ADC		=		READY			---			DAC		=		!!!!


					CONT_BUSY_BUFF_A_DAC ++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		READY			---			DAC		=		READY
					{
						buffer_ready = BUFFER_A;
						ESTADO_BUFFERS = READY_BUFF_A;
					}
					break;
				case BUSY_BUFF_A_ADC :									// BUFFER A			---			ADC		=		!!!!			---			DAC		=		READY


					CONT_BUSY_BUFF_A_ADC++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		READY
					{
						buffer_ready = BUFFER_A;
						ESTADO_BUFFERS = READY_BUFF_A;
					}
					else
						while(1);
					break;
				case BUSY_BUFF_B_ADC_DAC :								// BUFFER B			---			ADC		=		!!!!			---			DAC		=		!!!!


					CONT_BUSY_BUFF_B_ADC_DAC++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		!!!!
					{
//						BUFFER_ADC_B = READY;
						ESTADO_BUFFERS = BUSY_BUFF_B_DAC;
					}
					else if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		!!!!			---			DAC		=		READY
					{
//						BUFFER_DAC_B = READY;
						if(ESTADO_BUFFERS == BUSY_BUFF_B_ADC)
							ESTADO_BUFFERS = READY_BUFF_B;
						else
							ESTADO_BUFFERS = BUSY_BUFF_B_ADC;
					}
					else
						while(1);
					break;
				case BUSY_BUFF_B_DAC :									// BUFFER B			---			ADC		=		READY			---			DAC		=		!!!!


					CONT_BUSY_BUFF_B_DAC++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		READY			---			DAC		=		READY
					{
						buffer_ready = BUFFER_B;
						ESTADO_BUFFERS = READY_BUFF_B;
					}
					else
						while(1);
					break;
				case BUSY_BUFF_B_ADC :									// BUFFER B			---			ADC		=		!!!!			---			DAC		=		READY


					CONT_BUSY_BUFF_B_ADC++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		READY
					{
						buffer_ready = BUFFER_B;
						ESTADO_BUFFERS = READY_BUFF_B;
					}
					break;
				default:
					break;
				}

				if (ESTADO_BUFFERS == READY_BUFF_A) 					// BUFFER A			---			ADC		=		READY			---			DAC		=		READY
				{


					CONT_READY_BUFF_A++;


					ESTADO_BUFFERS = BUSY_BUFF_B_ADC_DAC;
					#if USE_RTOS
						// Aviso a la tarea que puede procesar los buffer A del ADC y DAC
						xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_ready, &HPTW);
						portEND_SWITCHING_ISR(HPTW);
					#else
						// Transmito los buffer B del ADC y DAC
						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
												&DMA_descriptor_ADC_BUFFER_B,
												GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);

						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_dac,
												&DMA_descriptor_DAC_BUFFER_B,
												GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);

						// Procesamiento de buffer A del ADC->DAC
						for(i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
							dma_memory_dac_BUFF_A[i] =  set_data (dma_memory_adc_BUFF_A[i]);
					#endif
				}
				else if ( ESTADO_BUFFERS == READY_BUFF_B )					// BUFFER B			---			ADC		=		READY			---			DAC		=		READY
				{

					CONT_READY_BUFF_B++;


					ESTADO_BUFFERS = BUSY_BUFF_A_ADC_DAC;
					#if USE_RTOS
						// Aviso a la tarea que puede procesar los buffer A del ADC y DAC
						xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_ready, &HPTW);
						portEND_SWITCHING_ISR(HPTW);
					#else
						// Transmito los buffer B del ADC y DAC
						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
												&DMA_descriptor_ADC_BUFFER_A,
												GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);

						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_dac,
												&DMA_descriptor_DAC_BUFFER_A,
												GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);

						// Procesamiento de buffer A del ADC->DAC
						for(i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
							dma_memory_dac_BUFF_B[i] =  set_data (dma_memory_adc_BUFF_B[i]);
					#endif
				}
			#endif
		#endif
	}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// NEW DMA_IRQ : ONLY RTOS - BUFFER PARALELO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	void DMA_IRQHandler(void)
//	{
//		portBASE_TYPE HPTW = pdFALSE;
//		int_state_t buffer_state = INT_ERROR;
//
//
//		irq_cont++;
//
//
//		volatile uint8_t stat_int = 0, stat_interr = 0, stat_inttc = 0, stat_rawinttc = 0, stat_warinterr = 0,  stat_enbldchns = 0;
//		volatile uint8_t regs[6];
//
////		/* check status of DMA channel interrupts */
////		regs[0] = LPC_GPDMA->INTSTAT;
////
////
////		/* check terminal count interrupt request status for DMA */
////		regs[1] = LPC_GPDMA->INTTCSTAT;
////
////
////		/* check interrupt status for DMA channels */
////		regs[2] = LPC_GPDMA->INTERRSTAT;
////
////
////		/* check status of the terminal count interrupt for DMA channels */
////		regs[3] = LPC_GPDMA->RAWINTTCSTAT;
////
////
////
////		/* check status of the error interrupt for DMA channels */
////		regs[4] = LPC_GPDMA->RAWINTERRSTAT;
////
////
////		/* check enable status for DMA channels */
////		regs[5] = LPC_GPDMA->ENBLDCHNS;
//
//
////		if(regs[0] == 3 || regs[1] == 3 || regs[2] == 3 || regs[3] != 3 || regs[4] != 0 || regs[5] != 0)
////		{
////			xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_state, &HPTW);
////			portEND_SWITCHING_ISR(HPTW);
////		}
//
////		if(Chip_GPDMA_IntGetStatus(LPC_GPDMA, GPDMA_STAT_INTERR, canal_adc) && Chip_GPDMA_IntGetStatus(LPC_GPDMA, GPDMA_STAT_RAWINTERR, canal_dac))
////		{
////			buffer_state = INT_ERROR;
////
////		}
//
//
//		if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		!!!!
//		{
//			buffer_state = INT_ADC;
//		}
////		else
////		{
////			buffer_state = INT_ERROR;
////
////		}
//
//		if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		!!!!			---			DAC		=		READY
//		{
//			if (buffer_state == INT_ADC)
//				buffer_state = INT_BOTH;
//			else
//				buffer_state = INT_DAC;
//		}
////		else if (buffer_state != ( INT_ADC || INT_ERROR ) )
////		{
////			buffer_state = INT_ERROR;
////
////		}
//
//		if(buffer_state == INT_ERROR)
//		{
//			buffer_state = INT_ERROR;
//
//		}
//			//stat_enbldchns = LPC_GPDMA->ENBLDCHNS;
//
//
//		xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_state, &HPTW);
//		portEND_SWITCHING_ISR(HPTW);
//	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










//
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// NEW DMA_IRQ : ONLY RTOS - BUFFER PARALELO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	void DMA_IRQHandler(void)
//	{
//		portBASE_TYPE HPTW = pdFALSE;
//		int_state_t buffer_state = INT_ERROR;
//
//
//		volatile uint8_t stat_int = 0, stat_interr = 0, stat_inttc = 0, stat_rawinttc = 0, stat_warinterr = 0,  stat_enbldchns = 0;
//		volatile uint8_t regs[6];
//
////		/* check status of DMA channel interrupts */
////		regs[0] = LPC_GPDMA->INTSTAT;
////
////
////		/* check terminal count interrupt request status for DMA */
////		regs[1] = LPC_GPDMA->INTTCSTAT;
////
////
////		/* check interrupt status for DMA channels */
////		regs[2] = LPC_GPDMA->INTERRSTAT;
////
////
////		/* check status of the terminal count interrupt for DMA channels */
////		regs[3] = LPC_GPDMA->RAWINTTCSTAT;
////
////
////
////		/* check status of the error interrupt for DMA channels */
////		regs[4] = LPC_GPDMA->RAWINTERRSTAT;
////
////
////		/* check enable status for DMA channels */
////		regs[5] = LPC_GPDMA->ENBLDCHNS;
//
//
////		if(regs[0] == 3 || regs[1] == 3 || regs[2] == 3 || regs[3] != 3 || regs[4] != 0 || regs[5] != 0)
////		{
////			xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_state, &HPTW);
////			portEND_SWITCHING_ISR(HPTW);
////		}
//
////		if(Chip_GPDMA_IntGetStatus(LPC_GPDMA, GPDMA_STAT_INTERR, canal_adc) && Chip_GPDMA_IntGetStatus(LPC_GPDMA, GPDMA_STAT_RAWINTERR, canal_dac))
////		{
////			buffer_state = INT_ERROR;
////
////		}
//
//
//		if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		!!!!
//		{
//			buffer_state = INT_ADC;
//		}
////		else
////		{
////			buffer_state = INT_ERROR;
////
////		}
//
//		if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		!!!!			---			DAC		=		READY
//		{
//			if (buffer_state == INT_ADC)
//				buffer_state = INT_BOTH;
//			else
//				buffer_state = INT_DAC;
//		}
//
//		for(int i=0; i<8; i++)
//		{
//			if(Chip_GPDMA_Interrupt(LPC_GPDMA, i))
//			{
//				i = 9;
//			}
//		}
////		else if (buffer_state != ( INT_ADC || INT_ERROR ) )
////		{
////			buffer_state = INT_ERROR;
////
////		}
//
//		if(buffer_state == INT_ERROR)
//		{
//			buffer_state = INT_ERROR;
//
//		}
//			//stat_enbldchns = LPC_GPDMA->ENBLDCHNS;
//
//
//		xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_state, &HPTW);
//		portEND_SWITCHING_ISR(HPTW);
//	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//



//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// NEW DMA_IRQ : ONLY RTOS - Nuevo metodo de procesamiento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	void DMA_IRQHandler(void)
//	{
//		portBASE_TYPE HPTW = pdFALSE;
//		int_state_t buffer_state = INT_ERROR;
//
//
////		volatile uint8_t stat_int = 0, stat_interr = 0, stat_inttc = 0, stat_rawinttc = 0, stat_warinterr = 0,  stat_enbldchns = 0;
////		volatile uint8_t regs[6];
//
//
//		if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		!!!!
//		{
//			buffer_state = INT_ADC;
//		}
//
//
//		if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		!!!!			---			DAC		=		READY
//		{
//			buffer_state = INT_DAC;
//		}
//
//
//		for(int i=0; i<8; i++)
//		{
//			if(Chip_GPDMA_Interrupt(LPC_GPDMA, i))
//			{
//				i = 9;
//			}
//		}
//
//
//		xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_state, &HPTW);
//		portEND_SWITCHING_ISR(HPTW);
//	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//









#endif
