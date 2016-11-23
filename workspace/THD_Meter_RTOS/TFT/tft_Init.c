#include "header.h"
#include "tft_header_priv.h"


// *** PROTOTIPOS FUNCIONES PRIVADAS *** //
	static void tft_gpio_init_priv();
	static void tft_LCD_Init_priv();
	static void MenuInit();
// ************************************* //


// *** PUBLIC FUNCTIONS *** //
void tft_init()
{
	#if DEBUG_MODE
		printf("[info] init TFT: \r\n");
		printf("\t frecuencia de back-light: %d \r\n", BACKLIGHT_FREC);
	#endif

	tft_gpio_init_priv();
	tft_LCD_Init_priv();

	tft_x = tft_y = 0;
	tft_Opts.width = TFT_WIDTH;
	tft_Opts.height = TFT_HEIGHT;
	tft_Opts.orientation = TFT_ORIENTATION_PORTRAIT;

	timer_BL_init(100, BACKLIGHT_FREC);

	tft_Fill(TFT_COLOR_WHITE);

	MenuInit();
}
// ************************ //


// *** FUNCIONES PRIVADAS *** //
static void MenuInit()
{
	//TM_ILI9341_Orientation peperota=TM_ILI9341_Landscape ;
		/* MODOS DE ORIENTACION (funcion TM_ILI9341_Rotate())
		 * 0: MAL
		 * 1: MAL
		 * 2: Vertical con pines arriba
		 * 3: Vertical con pines abajo
		 * 4: Apaisado con pines hacia la izquierda
		 * 5: Apaisado con pines hacia la derecha
		 */
	tft_Rotate(4);

	tft_Fill(TFT_COLOR_BLACK);

	tft_Puts(5, 5,		"ECG", 			&tft_Font_11x18,  TFT_FOREGROUND_RED, 	TFT_BACKGROUND_BLACK);
	tft_Puts(5, 70, 	"Cargando", 	&tft_Font_11x18,  TFT_FOREGROUND_GREEN, TFT_BACKGROUND_BLACK);
	tft_Puts(5, 130, 	"Version 15.0", &tft_Font_11x18,  TFT_FOREGROUND_BLUE, 	TFT_BACKGROUND_BLACK);
}

static void tft_gpio_init_priv()
{
	pin_gpio_init(DB0, 		 IOCON_MODE_INACT, SALIDA); // Expansion 0 -> P 2 , 6
	pin_gpio_init(DB1, 		 IOCON_MODE_INACT, SALIDA); // Expansion 1 -> P 1 , 29
	pin_gpio_init(DB2, 		 IOCON_MODE_INACT, SALIDA); // Expansion 2 -> P 4 , 28
	pin_gpio_init(DB3, 		 IOCON_MODE_INACT, SALIDA); // Expansion 3 -> P 1 , 23
	pin_gpio_init(DB4, 		 IOCON_MODE_INACT, SALIDA); // Expansion 4 -> P 1 , 20
	pin_gpio_init(DB5, 		 IOCON_MODE_INACT, SALIDA); // Expansion 5 -> P 0 , 19
	pin_gpio_init(DB6, 		 IOCON_MODE_INACT, SALIDA); // Expansion 6 -> P 3 , 26
	pin_gpio_init(DB7, 		 IOCON_MODE_INACT, SALIDA); // Expansion 7 -> P 1 , 25
	pin_gpio_init(DB8, 		 IOCON_MODE_INACT, SALIDA); // Expansion 8 -> P 1 , 22
	pin_gpio_init(DB9, 		 IOCON_MODE_INACT, SALIDA); // Expansion 9 -> P 1 , 19
	pin_gpio_init(DB10, 	 IOCON_MODE_INACT, SALIDA); // Expansion 10 -> P 0 , 20
	pin_gpio_init(DB11, 	 IOCON_MODE_INACT, SALIDA); // Expansion 11 -> P 3 , 25
	pin_gpio_init(DB12, 	 IOCON_MODE_INACT, SALIDA); // LCD_RESET
	pin_gpio_init(DB13, 	 IOCON_MODE_INACT, SALIDA); // Expansion 13 -> P 1 , 24
	pin_gpio_init(DB14, 	 IOCON_MODE_INACT, SALIDA); // Expansion 14 -> P 1 , 21
	pin_gpio_init(DB15, 	 IOCON_MODE_INACT, SALIDA); // Expansion 15 -> P 1 , 18 CN4
	pin_gpio_init(CS, 		 IOCON_MODE_INACT, SALIDA); // MOSI
    pin_gpio_init(RS, 		 IOCON_MODE_INACT, SALIDA); // MISO
    pin_gpio_init(WR, 		 IOCON_MODE_INACT, SALIDA); // SCK
    pin_gpio_init(READ_DATA, IOCON_MODE_INACT, SALIDA); // SSEL
    pin_gpio_init(REST, 	 IOCON_MODE_INACT, SALIDA); // LCD_D7
    pin_gpio_init(BL, 		 IOCON_MODE_INACT, SALIDA); // LCD_D6

    pin_set(CS,1); 			// Activa en Bajo
    pin_set(WR,1);  		// Activa en Bajo
    pin_set(READ_DATA,1);	// Activa en Bajo
    pin_set(REST,1);		// Activa en Bajo
}

static void tft_LCD_Init_priv()
{
		pin_set(REST,0);
		pin_set(REST,1);

		tft_SendCommand_priv(ILI9341_RESET);
		tft_Delay_priv(2000000);

		tft_SendCommand_priv(ILI9341_POWERA);
		tft_SendData_priv(0x39);
		tft_SendData_priv(0x2C);					//Codigo de fer pose
		tft_SendData_priv(0x00);
		tft_SendData_priv(0x34);
		tft_SendData_priv(0x02);
		tft_SendCommand_priv(ILI9341_POWERB);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0xC1);
		tft_SendData_priv(0x30);
		tft_SendCommand_priv(ILI9341_DTCA);
		tft_SendData_priv(0x85);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0x78);
		tft_SendCommand_priv(ILI9341_DTCB);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0x00);
		tft_SendCommand_priv(ILI9341_POWER_SEQ);
		tft_SendData_priv(0x64);
		tft_SendData_priv(0x03);
		tft_SendData_priv(0x12);
		tft_SendData_priv(0x81);
		tft_SendCommand_priv(ILI9341_PRC);
		tft_SendData_priv(0x20);
		tft_SendCommand_priv(ILI9341_POWER1);
		tft_SendData_priv(0x23);
		tft_SendCommand_priv(ILI9341_POWER2);
		tft_SendData_priv(0x10);
		tft_SendCommand_priv(ILI9341_VCOM1);
		tft_SendData_priv(0x3E);
		tft_SendData_priv(0x28);
		tft_SendCommand_priv(ILI9341_VCOM2);
		tft_SendData_priv(0x86);
		tft_SendCommand_priv(ILI9341_MAC);
		tft_SendData_priv(0x48);
		tft_SendCommand_priv(ILI9341_PIXEL_FORMAT);
		tft_SendData_priv(0x55);
		tft_SendCommand_priv(ILI9341_FRC);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0x18);
		tft_SendCommand_priv(ILI9341_DFC);
		tft_SendData_priv(0x08);
		tft_SendData_priv(0x82);
		tft_SendData_priv(0x27);
		tft_SendCommand_priv(ILI9341_3GAMMA_EN);
		tft_SendData_priv(0x00);
		tft_SendCommand_priv(ILI9341_COLUMN_ADDR);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0xEF);
		tft_SendCommand_priv(ILI9341_PAGE_ADDR);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0x01);
		tft_SendData_priv(0x3F);
		tft_SendCommand_priv(ILI9341_GAMMA);
		tft_SendData_priv(0x01);
		tft_SendCommand_priv(ILI9341_PGAMMA);
		tft_SendData_priv(0x0F);
		tft_SendData_priv(0x31);
		tft_SendData_priv(0x2B);
		tft_SendData_priv(0x0C);
		tft_SendData_priv(0x0E);
		tft_SendData_priv(0x08);
		tft_SendData_priv(0x4E);
		tft_SendData_priv(0xF1);
		tft_SendData_priv(0x37);
		tft_SendData_priv(0x07);
		tft_SendData_priv(0x10);
		tft_SendData_priv(0x03);
		tft_SendData_priv(0x0E);
		tft_SendData_priv(0x09);
		tft_SendData_priv(0x00);
		tft_SendCommand_priv(ILI9341_NGAMMA);
		tft_SendData_priv(0x00);
		tft_SendData_priv(0x0E);
		tft_SendData_priv(0x14);
		tft_SendData_priv(0x03);
		tft_SendData_priv(0x11);
		tft_SendData_priv(0x07);
		tft_SendData_priv(0x31);
		tft_SendData_priv(0xC1);
		tft_SendData_priv(0x48);
		tft_SendData_priv(0x08);
		tft_SendData_priv(0x0F);
		tft_SendData_priv(0x0C);
		tft_SendData_priv(0x31);
		tft_SendData_priv(0x36);
		tft_SendData_priv(0x0F);
		tft_SendCommand_priv(ILI9341_WCD);
		tft_SendData_priv(0x2C);
		tft_SendCommand_priv(0xC0);
		tft_SendData_priv(0x09);
		tft_SendCommand_priv(ILI9341_SLEEP_OUT);

		tft_Delay_priv(1000000);

		tft_SendCommand_priv(ILI9341_DISPLAY_ON);
		tft_SendCommand_priv(ILI9341_GRAM);
}
// ************************** //
