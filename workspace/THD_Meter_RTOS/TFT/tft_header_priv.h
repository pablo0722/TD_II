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


#endif /* TFT_HEADER_PRIV_H_ */
