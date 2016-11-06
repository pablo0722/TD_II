/*
 * tft_tareas.c
 *
 *  Created on: 6 de nov. de 2016
 *      Author: Pablo
 */


#include "header.h"


#if (USE_RTOS)
	void vTask_tft_BL( void *pvParameters )
	{
		xSemaphoreTake(sem_timer1_match0, 0);
		xSemaphoreTake(sem_timer1_match1, 0);

		while(1)
		{
			xSemaphoreTake(sem_timer1_match0, 0);

			Chip_GPIO_SetPinOutHigh(LPC_GPIO, BL);

			xSemaphoreTake(sem_timer1_match1, 0);

			Chip_GPIO_SetPinOutLow(LPC_GPIO, BL);
		}
	}

	void vtask_tft_display(void *pvParameters)
	{
		vTaskDelay(1000/ portTICK_RATE_MS);
		tft_Fill(TFT_COLOR_BLACK);

		tft_Puts(0, 0, 		"TECNICAS DIGITALES",	&tft_Font_16x26, 	TFT_FOREGROUND_GREEN, 	TFT_BACKGROUND_BLACK);
		tft_Puts(120, 25, 	"II",					&tft_Font_16x26, 	TFT_FOREGROUND_GREEN, 	TFT_BACKGROUND_BLACK);
		tft_Puts(0, 50, 	"PROCESAMIENTO DE",		&tft_Font_16x26, 	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
		tft_Puts(100, 75, 	"AUDIO",				&tft_Font_16x26, 	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
		tft_Puts(0, 100, 	"MENU",					&tft_Font_16x26,	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
		tft_Puts(50, 125, 	"Reverb",				&tft_Font_16x26,	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
		tft_Puts( 50, 150, 	"Echo",					&tft_Font_16x26, 	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
		tft_Puts(50, 175, 	"High Pass Filter",		&tft_Font_16x26,  	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
		tft_Puts(50, 200, 	"Low Pass Filter",		&tft_Font_16x26,  	TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);

		tft_DrawFilledCircle(30, 135, 7, TFT_COLOR_BLUE);
		tft_DrawFilledCircle(30, 160, 7, TFT_COLOR_BLUE);
		tft_DrawFilledCircle(30, 185, 7, TFT_COLOR_BLUE);
		tft_DrawFilledCircle(30, 210, 7, TFT_COLOR_BLUE);

		while(1)
		{
			vTaskDelay(1000/portTICK_RATE_MS);
		}
	}
#endif
