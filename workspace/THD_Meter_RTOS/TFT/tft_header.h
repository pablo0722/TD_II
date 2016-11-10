/*
 * tft_header.h
 *
 *  Created on: 6 de nov. de 2016
 *      Author: Pablo
 */

#ifndef TFT_HEADER_H_
#define TFT_HEADER_H_


#include "header.h"


// *** CONSTANTES *** //
	/**
	 * Orientation
	 * Used private
	 */
	typedef enum
	{
		TFT_ORIENTATION_LANDSCAPE,
		TFT_ORIENTATION_PORTRAIT,
		TFT_ORIENTATION_PORTRAIT_1,
		TFT_ORIENTATION_PORTRAIT_2,
		TFT_ORIENTATION_LANDSCAPE_1,
		TFT_ORIENTATION_LANDSCAPE_2
	} tft_Orientation;
// ****************** //


// *** ESTRUCTURAS *** //
	typedef struct
	{
		unsigned char FontWidth;
		unsigned char FontHeight;
		const uint16_t *data;
	} tft_font_t;

	/**
	 * LCD options
	 * Used private
	 */
	typedef struct
	{
		unsigned short int width;

		unsigned short int height;
		tft_Orientation orientation; // 1 = portrait; 0 = landscape
	} tft_Options_t;
// ******************* //


// *** VARIABLES GLOBALES *** //
	extern const int signal[300];

	extern uint16_t tft_x;
	extern uint16_t tft_y;
	extern tft_Options_t tft_Opts;

	extern tft_font_t tft_Font_7x10;
	extern tft_font_t tft_Font_11x18;
	extern tft_font_t tft_Font_16x26;
// ************************** //

// *** FUNCIONES *** //
	// *** INICIALIZACION *** //
		void tft_init();
	// ********************** //

	// *** PRIMITIVAS *** //
		void tft_Delay(volatile unsigned long int delay);
		void tft_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
		void tft_Fill(uint16_t color);
		void tft_Rotate(tft_Orientation orientation);
		void tft_Puts(uint16_t x, uint16_t y, char *str, tft_font_t *font, uint16_t foreground, uint16_t background);
		void tft_GetStringSize(char *str, tft_font_t *font, uint16_t *width, uint16_t *height);
		void tft_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
		void tft_DrawFilledRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
		void tft_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
		void tft_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	// ****************** //
// ***************** //


// *** DEFINES *** //
	// *** DIMENSIONES *** //
		#define WINDOWWIDTHX2				230		// DISTANCIA DESDE EL SUPERIOR
		#define WINDOWHEIGTHX2				310		// DISTANCIA DESDE LA DERECHA
		#define WINDOWHEIGTHX1				85		// DISTANCIA DESDE LA IZQUIERDA
		#define WINDOWWIDTHX1				30		// DISTANCIA DESDE EL INFERIOR
		#define WINDOWMULTIPLIER    		190
		#define RECTHEIGHT 					WINDOWHEIGTHX2-WINDOWHEIGTHX1

		#define TFT_WIDTH 					240		// Alto del display
		#define TFT_HEIGHT					320		// Ancho del display
		#define TFT_PIXEL					76800	// Cantidad de pixels en pantalla
		#define TFT_HFACTOR					4095 	// Cantidad de cuentas del ADC (12bits)
	// ******************* //

	// *** PIN-OUT *** //
		#define DB0 						2,7		// Expansion0
		#define DB1 						1,29	// Expansion1
		#define DB2 						4,28	// Expansion2
		#define DB3 						1,23	// Expansion3
		#define DB4 						1,20	// Expansion4
		#define DB5 						0,19	// Expansion5
		#define DB6 						3,26	// Expansion6
		#define DB7 						1,25	// Expansion7
		#define DB8 						1,22	// Expansion8
		#define DB9 						1,19	// Expansion9
		#define DB10 						0,20	// Expansion10
		#define DB11 						3,25	// Expansion11
		#define DB12 						2,6		// LCD_RESET SI FUNCA
		#define DB13 						1,24	// Expansion13
		#define DB14 						1,21	// Expansion14
		#define DB15 						1,18	// Expansion15

		#define CS 							0,9		// MOSI
		#define RS 							0,8 	// MISO
		#define WR 							0,7 	// SCK
		#define READ_DATA 					0,6 	// SSEL
		#define REST 						2,5 	// LCD_d7

		#define BL 							2,4 	// LCD_D6
	// *************** //

	// *** PIN MODE *** //
			#define ENTRADA 	0
			#define SALIDA 		1
	// **************** //

	// *** COLORES *** //
		#define TFT_COLOR_WHITE			0xFFFF
		#define TFT_COLOR_BLACK			0x0000
		#define TFT_COLOR_RED			0xF800
		#define TFT_COLOR_GREEN			0x07E0
		#define TFT_COLOR_GREEN2		0xB723
		#define TFT_COLOR_BLUE			0x001F
		#define TFT_COLOR_BLUE2			0x051D
		#define TFT_COLOR_YELLOW		0xFFE0
		#define TFT_COLOR_ORANGE		0xFBE4
		#define TFT_COLOR_CYAN			0x07FF
		#define TFT_COLOR_MAGENTA		0xA254
		#define TFT_COLOR_GRAY			0x7BEF
		#define TFT_COLOR_BROWN			0xBBCA

		#define TFT_FOREGROUND_WHITE	TFT_COLOR_WHITE
		#define TFT_FOREGROUND_BLACK	TFT_COLOR_BLACK
		#define TFT_FOREGROUND_RED		TFT_COLOR_RED
		#define TFT_FOREGROUND_GREEN	TFT_COLOR_GREEN
		#define TFT_FOREGROUND_GREEN2	TFT_COLOR_GREEN2
		#define TFT_FOREGROUND_BLUE		TFT_COLOR_BLUE
		#define TFT_FOREGROUND_BLUE2	TFT_COLOR_BLUE2
		#define TFT_FOREGROUND_YELLOW	TFT_COLOR_YELLOW
		#define TFT_FOREGROUND_ORANGE	TFT_COLOR_ORANGE
		#define TFT_FOREGROUND_CYAN		TFT_COLOR_CYAN
		#define TFT_FOREGROUND_MAGENTA	TFT_COLOR_CYAN
		#define TFT_FOREGROUND_GRAY		TFT_COLOR_MAGENTA
		#define TFT_FOREGROUND_BROWN	TFT_COLOR_GRAY

		#define TFT_BACKGROUND_WHITE	TFT_COLOR_WHITE
		#define TFT_BACKGROUND_BLACK	TFT_COLOR_BLACK
		#define TFT_BACKGROUND_RED		TFT_COLOR_RED
		#define TFT_BACKGROUND_GREEN	TFT_COLOR_GREEN
		#define TFT_BACKGROUND_GREEN2	TFT_COLOR_GREEN2
		#define TFT_BACKGROUND_BLUE		TFT_COLOR_BLUE
		#define TFT_BACKGROUND_BLUE2	TFT_COLOR_BLUE2
		#define TFT_BACKGROUND_YELLOW	TFT_COLOR_YELLOW
		#define TFT_BACKGROUND_ORANGE	TFT_COLOR_ORANGE
		#define TFT_BACKGROUND_CYAN		TFT_COLOR_CYAN
		#define TFT_BACKGROUND_MAGENTA	TFT_COLOR_CYAN
		#define TFT_BACKGROUND_GRAY		TFT_COLOR_MAGENTA
		#define TFT_BACKGROUND_BROWN	TFT_COLOR_GRAY
	// *************** //

	// *** COMANDOS *** //
		#define ILI9341_RESET				0x01
		#define ILI9341_SLEEP_OUT			0x11
		#define ILI9341_GAMMA				0x26
		#define ILI9341_DISPLAY_OFF			0x28
		#define ILI9341_DISPLAY_ON			0x29
		#define ILI9341_COLUMN_ADDR			0x2A
		#define ILI9341_PAGE_ADDR			0x2B
		#define ILI9341_GRAM				0x2C
		#define ILI9341_MAC					0x36
		#define ILI9341_PIXEL_FORMAT		0x3A
		#define ILI9341_WDB					0x51	// Write Display Brightness (WDB)
		#define ILI9341_WCD					0x53	// Write CTRL Display (WCD)
		#define ILI9341_WCABC				0x55	// Write Content Adaptative Brightness Control (WCABC)
		#define ILI9341_RGB_INTERFACE		0xB0
		#define ILI9341_FRC					0xB1
		#define ILI9341_BPC					0xB5
		#define ILI9341_DFC					0xB6
		#define ILI9341_POWER1				0xC0
		#define ILI9341_POWER2				0xC1
		#define ILI9341_VCOM1				0xC5
		#define ILI9341_VCOM2				0xC7
		#define ILI9341_POWERA				0xCB
		#define ILI9341_POWERB				0xCF
		#define ILI9341_PGAMMA				0xE0
		#define ILI9341_NGAMMA				0xE1
		#define ILI9341_DTCA				0xE8
		#define ILI9341_DTCB				0xEA
		#define ILI9341_POWER_SEQ			0xED
		#define ILI9341_3GAMMA_EN			0xF2
		#define ILI9341_INTERFACE			0xF6
		#define ILI9341_PRC					0xF7
	// **************** //
// *************** //


#endif /* TFT_HEADER_H_ */
