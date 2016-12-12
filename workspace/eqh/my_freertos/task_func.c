/*
 * task_func.c
 *
 *  Created on: 6 de nov. de 2016
 *      Author: agustin
 */


#include "header.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SEÑALES DE PRUEBA
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t CONT_A = 0, CONT_B = 0;
uint32_t CONT_BUSY_BUFF_A_ADC_DAC = 0, CONT_BUSY_BUFF_A_DAC = 0, CONT_BUSY_BUFF_A_ADC = 0, CONT_BUSY_BUFF_B_ADC_DAC = 0, CONT_BUSY_BUFF_B_DAC = 0, CONT_BUSY_BUFF_B_ADC = 0;
uint32_t CONT_READY_BUFF_A = 0;
uint32_t CONT_READY_BUFF_B = 0;
uint32_t CONT_ERROR = 0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


volatile uint8_t flag_volumen_up = 0;
volatile uint8_t flag_volumen_down = 0;


#if (USE_RTOS)
	#if(USE_GPIO)
		// LED ALIVE
		void vTaskLED_alive(void *pvParameters)
		{
			while (1)
			{
				vTaskDelay( 1000 / portTICK_RATE_MS );
				Chip_GPIO_SetPinToggle(LPC_GPIO, LED_Alive);
			}
		}
	#endif


	#if (USE_BOTONES)
		// Debouncer
		void vDEBOUNCETask(void *pvParameters)
		{
			int EstadoDebounce = WAIT_0, tecla_actual = 0, tecla_anterior = 0;

			while (1)
			{
				switch(EstadoDebounce)
				{
				case WAIT_0:
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW1 ) == 0 )
//								tecla_actual=1;
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW2 ) == 0 )
//								tecla_actual=2;
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW3 ) == 0 )
//								tecla_actual=3;
					if( Chip_GPIO_GetPinState( LPC_GPIO , SW4 ) == 0 )
							tecla_actual=4;

					if( tecla_actual != 0)
						EstadoDebounce = VALIDATE_0;
					tecla_anterior = tecla_actual;
					break;
				case VALIDATE_0:
					vTaskDelay(50/portTICK_RATE_MS);

//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW1 ) == 0 )
//								tecla_actual=1;
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW2 ) == 0 )
//								tecla_actual=2;
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW3 ) == 0 )
//								tecla_actual=3;
					if( Chip_GPIO_GetPinState( LPC_GPIO , SW4 ) == 0 )
							tecla_actual=4;
					if( tecla_anterior == tecla_actual)
					{
						EstadoDebounce = WAIT_1;
						// Transmitimos la tecla validada
						if(tecla_actual == 4)
							flag_volumen_up = 1;
//							else if(tecla_actual == SW2)
//								flag_volumen_down = 1;
//							xQueueSendToBack( TeclaQueue, &tecla_actual, portMAX_DELAY );
					}
					else
						EstadoDebounce = WAIT_0;
					tecla_actual = 0;
					break;
				case WAIT_1:
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW1 ) == 1 )
//								tecla_actual=1;
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW2 ) == 1 )
//								tecla_actual=2;
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW3 ) == 1 )
//								tecla_actual=3;
					if( Chip_GPIO_GetPinState( LPC_GPIO , SW4 ) == 1 )
							tecla_actual=4;
					if( tecla_actual != 0 )
						EstadoDebounce = VALIDATE_1;
					tecla_actual = 0;
					break;
				case VALIDATE_1:
					vTaskDelay(50/portTICK_RATE_MS);

//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW1 ) == 1 )
//								tecla_actual=1;
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW2 ) == 1 )
//								tecla_actual=2;
//						if( Chip_GPIO_GetPinState( LPC_GPIO , SW3 ) == 1 )
//								tecla_actual=3;
					if( Chip_GPIO_GetPinState( LPC_GPIO , SW4 ) == 1 )
							tecla_actual=4;

					if( 0 != tecla_actual)
						EstadoDebounce = WAIT_0;
					else
						EstadoDebounce = WAIT_1;
					tecla_actual = 0;
					break;
				default:
					break;
				}
			}
		}
	#endif


	#if (USE_ADC && USE_DAC)
		// SIGNAL PROCESSING
		void vTaskSIGNAL_PROC(void *pvParameters)
		{
			#if (USE_DISPLAY)

				TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
				TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);

			#endif

			while (1)
			{
				#if (USE_DISPLAY)

					char thd_str[10];

					sprintf(thd_str, "%d", fft_thd);
					TM_ILI9341_Puts(0, 0, "THD:", &TM_Font_16x26, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
					TM_ILI9341_Puts(60, 0, thd_str, &TM_Font_16x26, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);

				#endif

				vTaskDelay(1000/ portTICK_RATE_MS);
			}
		}
	#endif


	#if (USE_DISPLAY)

		void vDisplayTask(void *pvParameters)
		{
			while(1);
			/*

			//portBASE_TYPE xStatus;
			//uint16_t cursor_x = WINDOWHEIGTHX1+1;
			//uint32_t buffer;
			//uint32_t buffer_anterior = 0;
			extern TM_FontDef_t TM_Font_16x26;
			//char datos[16]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
			//uint32_t first_sample=0;

			vTaskDelay(1000/ portTICK_RATE_MS);
			TM_ILI9341_Fill(ILI9341_COLOR_RED);
			//Dibujo el rectangulo donde se imprimirá la señal
			TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);

			//TM_ILI9341_DrawRectangle(WINDOWHEIGTHX1,WINDOWWIDTHX1,WINDOWHEIGTHX2,WINDOWWIDTHX2,ILI9341_COLOR_WHITE);

			TM_ILI9341_Puts(0, 0, "TECNICAS DIGITALES", &TM_Font_16x26,  ILI9341_COLOR_GREEN,ILI9341_COLOR_BLACK);

//			TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
//			TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_1);
//			TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);

			TM_ILI9341_Puts(120, 25, "II", &TM_Font_16x26,  ILI9341_COLOR_GREEN,ILI9341_COLOR_YELLOW);
			TM_ILI9341_Puts(0, 50, "PROCESAMIENTO DE", &TM_Font_16x26,  ILI9341_COLOR_GREEN2,ILI9341_COLOR_YELLOW);
			TM_ILI9341_Puts(100, 75, "AUDIO", &TM_Font_16x26,  ILI9341_COLOR_GREEN2,ILI9341_COLOR_YELLOW);

			TM_ILI9341_Puts( 0, 100, "MENU", &TM_Font_16x26,  ILI9341_COLOR_GREEN2,ILI9341_COLOR_YELLOW);
			TM_ILI9341_DrawFilledCircle(30,135,7,ILI9341_COLOR_BLUE);
			TM_ILI9341_Puts( 50, 125, "Reverb", &TM_Font_16x26,  ILI9341_COLOR_GREEN2,ILI9341_COLOR_YELLOW);
			TM_ILI9341_DrawFilledCircle(30,160,7,ILI9341_COLOR_BLUE);
			TM_ILI9341_Puts( 50, 150, "Echo", &TM_Font_16x26,  ILI9341_COLOR_GREEN2,ILI9341_COLOR_YELLOW);
			TM_ILI9341_DrawFilledCircle(30,185,7,ILI9341_COLOR_BLUE);
			TM_ILI9341_Puts( 50, 175, "High Pass Filter", &TM_Font_16x26,  ILI9341_COLOR_GREEN2,ILI9341_COLOR_YELLOW);
			TM_ILI9341_DrawFilledCircle(30,210,7,ILI9341_COLOR_BLUE);
			TM_ILI9341_Puts	(50, 200, "Low Pass Filter", &TM_Font_16x26,  ILI9341_COLOR_GREEN2,ILI9341_COLOR_YELLOW);
			//TM_ILI9341_Fill(ILI9341_COLOR_BLUE);
		//	for(int i=0; i<300; i++)
		//	{
		//		TM_ILI9341_DrawPixel(i, signal[i]+40, ILI9341_COLOR_BLACK);
		//	}
		//	for(int i=0; i<300; i++)
		//	{
		//		TM_ILI9341_DrawPixel(i, signal[i]+10, ILI9341_COLOR_BLACK);
		//	}
		//	for(int i=0; i<300; i++)
		//	{
		//		TM_ILI9341_DrawPixel(i, signal[i]+20, ILI9341_COLOR_BLACK);
		//	}



			//TM_ILI9341_Puts(50, 25, "Hz", &TM_Font_16x26,  ILI9341_COLOR_BLUE2,ILI9341_COLOR_BLUE);
			//sprintf (datos,"%d,%d", (int)frecuencia, abs((int)((((int)frecuencia) - frecuencia) * 100.0)));
		//	TM_ILI9341_Puts(0, 25, datos, &TM_Font_11x18,  ILI9341_COLOR_BLUE2,ILI9341_COLOR_BLACK);
			//Imprimo primero todo el texto y luego actualizo solo la frecuencia cardiaca.
			//TM_ILI9341_DrawCircle(50,50,100,ILI9341_COLOR_RED);
			//int i;
			while(1){

				vTaskDelay(1000/portTICK_RATE_MS);
			//		TM_ILI9341_Fill(ILI9341_COLOR_RED);

		//			for( i =0 ; i<200 ; i++ )
		//			{
		//				TM_ILI9341_DrawFilledRectangle(i , i , i , i , ILI9341_COLOR_BLUE);
		//
		////				TM_ILI9341_DrawPixel(i,i,200);
		//			}


		//		if((frecuencia != 0))
		//		{
		//			sprintf (datos,"%d,%d", (int)frecuencia, abs((int)((((int)frecuencia) - frecuencia) * 100.0)));
		//			TM_ILI9341_Puts(0, 25, datos, &TM_Font_11x18,  ILI9341_COLOR_BLUE2,ILI9341_COLOR_BLACK);
		//			frecuencia = 0;
		//		}
		//		// Espero indefinitivamente lo datos a imprimir.
		//		// Hasta que aparezca algun dato por la cola.
		//		xStatus = xQueueReceive(Display_Queue, &buffer, portMAX_DELAY);
		//
		//		// Si recibi los datos correctamente
		//		if(xStatus == pdPASS){
		//				if(first_sample==0)
		//				{	buffer_anterior=buffer;
		//					first_sample=1;
		//				}
		//				// Dibujo las lines
		//					TM_ILI9341_DrawLine(cursor_x,11+((buffer_anterior*(WINDOWMULTIPLIER))/(ILI9341_HFACTOR)),cursor_x+1,11+((buffer*(WINDOWMULTIPLIER))/(ILI9341_HFACTOR)),ILI9341_COLOR_GREEN);
		//					TM_ILI9341_DrawLine(cursor_x+1,WINDOWWIDTHX1+1,cursor_x+1,WINDOWWIDTHX2-1,ILI9341_COLOR_BLACK);
		//					//TM_ILI9341_DrawLine(cursor_x+2,WINDOWWIDTHX1+1,cursor_x+2,WINDOWWIDTHX2-1,ILI9341_COLOR_BLACK);
		//					//Que dibuje una linea menos, Asi obtengo una mayor velocidad a la hora de graficar
		//
		//				if (cursor_x==(WINDOWHEIGTHX2-3)){
		//					TM_ILI9341_DrawLine(WINDOWHEIGTHX1+1,WINDOWWIDTHX1+1,WINDOWHEIGTHX1+1,WINDOWWIDTHX2-1,ILI9341_COLOR_BLACK);
		//					//Linea negra para dar el efecto de una nueva señal
		//					cursor_x=WINDOWHEIGTHX1+1;
		//
		//				}else{
		//					cursor_x++;
		//				}
		//				buffer_anterior = buffer;
		//		}
		//
			}
			*/
		}

	#endif
#endif




