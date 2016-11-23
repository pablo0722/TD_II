/*
 * tft_private_func.h
 *
 *  Created on: 6 de nov. de 2016
 *      Author: Pablo
 */

#ifndef TFT_HEADER_PRIV_H_
#define TFT_HEADER_PRIV_H_


// *** PROTOTIPOS FUNCIONES "PRIVADAS" (solo para funciones internas de TFT) *** //
	void tft_Delay_priv(volatile unsigned long int delay);
	void tft_SendCommand_priv(uint16_t data);
	void tft_SendData_priv(uint16_t data);
// ************************************* //


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

	// *** PIN MODE *** //
			#define ENTRADA 	0
			#define SALIDA 		1
	// **************** //

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


#endif /* TFT_HEADER_PRIV_H_ */
