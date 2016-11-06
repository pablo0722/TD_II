#include "header.h"
#include "tft_private_func.h"


// *** PROTOTIPOS FUNCIONES PRIVADAS *** //
	static void tft_gpio_init_priv();
	static void tft_LCD_Init_priv();
	static void MenuInit();
// ************************************* //


// *** PUBLIC FUNCTIONS *** //
void tft_init()
{
	tft_gpio_init_priv();
	tft_LCD_Init_priv();

	tft_x = tft_y = 0;
	tft_Opts.width = TFT_WIDTH;
	tft_Opts.height = TFT_HEIGHT;
	tft_Opts.orientation = TFT_ORIENTATION_PORTRAIT;

	tft_Fill(TFT_COLOR_WHITE);

	MenuInit();

	playBL(60, 1);

	#if (USE_RTOS)
			// *** Tareas
		xTaskCreate(vTask_tft_BL, "vTask_tft_BL", 		configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
		xTaskCreate(vtask_tft_display, "vtask_tft_display", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
	#endif
}
// ************************ //


// *** FUNCIONES PRIVADAS *** //
static void MenuInit()
{
	extern tft_font_t TM_Font_11x18;
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

	tft_DrawRectangle(2,2,60,40, TFT_COLOR_WHITE);
	tft_Puts(5, 5,	"ECG", 			&TM_Font_11x18,  TFT_FOREGROUND_BLUE2, TFT_BACKGROUND_BLACK);
	tft_Puts(5, 70, 	"Cargando", 	&TM_Font_11x18,  TFT_FOREGROUND_BLUE2, TFT_BACKGROUND_BLACK);
	tft_Puts(5, 130, "Version 15.0", &TM_Font_11x18,  TFT_FOREGROUND_BLUE2, TFT_BACKGROUND_BLACK);
	tft_DrawFilledCircle(10,		160, 10, TFT_COLOR_YELLOW);
	tft_DrawFilledCircle(50,		160, 10, TFT_COLOR_GREEN);
	tft_DrawFilledCircle(90,		160, 10, TFT_COLOR_WHITE);
	tft_DrawFilledCircle(130,	160, 10, TFT_COLOR_ORANGE);
}

static void tft_gpio_init_priv()
{
	Chip_IOCON_PinMux(LPC_IOCON, DB0, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB0);	// Expansion 0 -> P 2 , 6
	Chip_GPIO_SetPinState(LPC_GPIO, DB0,0);

	Chip_IOCON_PinMux(LPC_IOCON, DB1, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB1);	// Expansion 1 -> P 1 , 29
    Chip_GPIO_SetPinState(LPC_GPIO, DB1,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB2, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB2);	// Expansion 2 -> P 4 , 28
    Chip_GPIO_SetPinState(LPC_GPIO, DB2,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB3, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB3);// Expansion 3 -> P 1 , 23
    Chip_GPIO_SetPinState(LPC_GPIO, DB3,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB4, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB4);// Expansion 4 -> P 1 , 20
    Chip_GPIO_SetPinState(LPC_GPIO, DB4,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB5, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB5);// Expansion 5 -> P 0 , 19
    Chip_GPIO_SetPinState(LPC_GPIO, DB5,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB6, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB6);// Expansion 6 -> P 3 , 26
    Chip_GPIO_SetPinState(LPC_GPIO, DB6,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB7, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB7);// Expansion 7 -> P 1 , 25
    Chip_GPIO_SetPinState(LPC_GPIO, DB7,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB8, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB8);// Expansion 8 -> P 1 , 22
    Chip_GPIO_SetPinState(LPC_GPIO, DB8,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB9, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB9);// Expansion 9 -> P 1 , 19
    Chip_GPIO_SetPinState(LPC_GPIO, DB9,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB10, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB10);// Expansion 10 -> P 0 , 20
    Chip_GPIO_SetPinState(LPC_GPIO, DB10,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB11, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB11);// Expansion 11 -> P 3 , 25
    Chip_GPIO_SetPinState(LPC_GPIO, DB11,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB12, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB12);//LCD_RESET
    Chip_GPIO_SetPinState(LPC_GPIO,DB12,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB13, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB13);// Expansion 13 -> P 1 , 24
    Chip_GPIO_SetPinState(LPC_GPIO, DB13,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB14, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB14);// Expansion 14 -> P 1 , 21
    Chip_GPIO_SetPinState(LPC_GPIO, DB14,0);

    Chip_IOCON_PinMux(LPC_IOCON, DB15, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB15);// Expansion 15 -> P 1 , 18 CN4
    Chip_GPIO_SetPinState(LPC_GPIO, DB15,0);

    Chip_IOCON_PinMux(LPC_IOCON, CS, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, CS); // MOSI
    Chip_GPIO_SetPinState(LPC_GPIO, CS,1); // Activa en Bajo

    Chip_IOCON_PinMux(LPC_IOCON, RS, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, RS); // MISO
    Chip_GPIO_SetPinState(LPC_GPIO, RS,0);

    Chip_IOCON_PinMux(LPC_IOCON, WR, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, WR); // SCK
    Chip_GPIO_SetPinState(LPC_GPIO, WR,1);  // Activa en Bajo

    Chip_IOCON_PinMux(LPC_IOCON, READ_DATA, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, READ_DATA); // SSEL
    Chip_GPIO_SetPinState(LPC_GPIO, READ_DATA,1);//ACTIVA EN BAJO

    Chip_IOCON_PinMux(LPC_IOCON, REST, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, REST); // LCD_D7
    Chip_GPIO_SetPinState(LPC_GPIO, REST,1);	// Activa en Bajo

    Chip_IOCON_PinMux(LPC_IOCON, BL, IOCON_MODE_INACT, IOCON_FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, BL); // LCD_D6
    Chip_GPIO_SetPinState(LPC_GPIO,BL,0);
}

static void tft_LCD_Init_priv()
{
		Chip_GPIO_SetPinState(LPC_GPIO, REST,0);
		Chip_GPIO_SetPinState(LPC_GPIO, REST,1);

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
