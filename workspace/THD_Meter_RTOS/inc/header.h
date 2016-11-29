/*
 * header.h
 *
 *  Created on: 18 de ago. de 2016
 *      Author: pablo
 */


#ifndef HEADER_H_
#define HEADER_H_

	#include "utilidades.h"
	#include "basics_header.h"
	#include "fft_header.h"
	#include "uart_header.h"
	#include "adc_dac_header.h"
	#include "timer_header.h"
	#include "tft_header.h"
	#include "timer_header.h"
	#include "rtos_header.h"



// ********* TAREAS ********** //
	void vTask_teclado(void *pvParameters);
	void vTask_tft(void *pvParameters);
	void vTask_THD(void *pvParameters);
// ****************************** //


// ************* VARIABLES GLOBALES ************* //
	#if USE_RTOS
		extern Bool flag_dac_send;	// Envia senial por DAC
		extern Bool flag_do_thd;	// Calcula THD
		extern Bool flag_do_rem;	// Calcula senal remanente

		extern q31_t THD;
		extern q31_t fft_max;
		extern uint32_t fft_max_idx;
		extern q31_t fft_min;
	#endif
// ********************************************** //


// *** BUFFERS *** //
	extern uint32_t buffer_complex	[FFT_SIZE*2];
	extern uint16_t buffer_dac_out	[FFT_SIZE*2];
	extern uint32_t buffer_dep		[FFT_SIZE];
	extern uint32_t buffer_dac		[FFT_SIZE/2];
// *************** //


// *** BOTONES *** //
		// Pin 88 - Boton 0
	#define	BUTTON0_INIT	1, 15, MD_PUP, ENTRADA
	#define	BUTTON0			1, 15
		// Pin 89 - Boton 1
	#define	BUTTON1_INIT	1, 14, MD_PUP, ENTRADA
	#define	BUTTON1			1, 14
		// Pin 90 - Boton 2
	#define	BUTTON2_INIT	1, 10, MD_PUP, ENTRADA
	#define	BUTTON2			1, 10
		// Pin 91 - Boton 3
	#define	BUTTON3_INIT	1, 9,  MD_PUP, ENTRADA
	#define	BUTTON3			1, 9
// *************** //


// *** LEDS *** //
		// Pin 95 - Led 0 (led testigo)
	#define LED_IM_ALIVE_INIT		1, 0, MD_PLN, SALIDA
	#define LED_IM_ALIVE			1, 0

		// Pin - Led 1
	#define LED_1_INIT				1, 1, MD_PLN, SALIDA
	#define LED_1					1, 1

		// Pin - Led 2
	#define LED_2_INIT				1, 4, MD_PLN, SALIDA
	#define LED_2					1, 4

		// Pin - Led 3
	#define LED_3_INIT				1, 8, MD_PLN, SALIDA
	#define LED_3					1, 8
// *************** //


// *** GPIOS DEL ADC*** //
		// Pin 77 - OSR del ADC (I2STX-WS)
	#define ADC_OSR_INIT	0, 8, MD_PLN, SALIDA
	#define ADC_OSR			0, 8
		// Pin 77 - OSR del ADC (I2STX-WS)
	#define ADC_FSYNC_INIT	0, 7, MD_PLN, SALIDA
	#define ADC_FSYNC		0, 7
// *************** //


// *** GPIOS DEL DAC*** //
		// Pin 87 - Mute del DAC (0=mute off, 1=mute on)
	#define DAC_MUTE_INIT	1, 16, MD_PLN, SALIDA
	#define DAC_MUTE		1, 16
		// Pin 86 - ZeroA del DAC
	#define DAC_ZEROA_INIT	1, 17, MD_PLN, ENTRADA
	#define DAC_ZEROA		1, 17
		// Pin 76 - Data del DAC
	#define DAC_DATA_INIT	0, 9, MD_PLN, SALIDA
	#define DAC_DATA		0, 9
// *************** //


/* *** MEMORIA *** //
 *  MFlash512  (xr-) : 	ADDR = 0x0000 0000 -> 0x0007 FFFF,	LENGTH = 0x0008 0000 (512K bytes)
 *  RamLoc32   (xrw) : 	ADDR = 0x1000 0000 -> 0x1000 7FFF,	LENGTH = 0x0000 8000 (32K bytes)
 *  Boot ROM   (x--) :	ADDR = 0x1FFF 0000 -> 0x1FFF 1FFF,	LENGTH = 0x0000 2000 (8K bytes)  - 8 kB Boot ROM with flash services.
 *  RamAHB32_0 (xrw) : 	ADDR = 0x2007 C000 -> 0x2007 FFFF, 	LENGTH = 0x0000 4000 (16K bytes) - AHB SRAM - bank 0
 *  RamAHB32_1 (xrw) : 	ADDR = 0x2008 0000 -> 0x2008 3FFF, 	LENGTH = 0x0000 4000 (16K bytes) - AHB SRAM - bank 1
 *
 *  The LPC1769 contains 64 kB of on-chip static RAM (SRAM) memory. 32 kB of
 *  SRAM, accessible by the CPU and all three DMA controllers are on a higher-speed bus.
 *  The LPC1769 have two additional 16 kB SRAM blocks, each
 *  situated on separate slave ports on the AHB multilayer matrix.
 *
 *
 * *** REGIONES DE MEMORIA *** //
 * text - shows the code and read-only data in your application (in decimal)
 * data - shows the read-write data in your application (in decimal)
 * bss - show the zero initialized ('bss' and 'common') data in your application (in decimal)
 * dec - total of 'text' + 'data' + 'bss' (in decimal)
 * hex - hexidecimal equivalent of 'dec'
 *
 * .text 			= 	MFlash512
 * .data.$RAM2		= 	RamLoc32 (NO inicializa)
 * .bss.$RAM2		= 	RamLoc32 (inicializa en 0)
 * .data.$RamAHB32	=	RamAHB32 (NO inicializa)
 * .bss.$RamAHB32	=	RamAHB32 (inicializa en 0)
 *
 *
 * *** NOTAS *** //
 * the flash consumption of your application will then be (text)
 * the RAM consumption of your application will then be (data + bss)
 *
 * Ejemplo para especificar la seccion de memoria a utilizar para una variable
 * int variable[1024] __attribute__ ((section (".bss.$RamAHB32")));
 *
 * las variables 'const' se guardan en la 'RamLoc32' por default
 *
 *
 * en:
 * C/C++ Build -> settings -> Tool Settings -> Miscellaneous
 * agregar:
 * -print-memory-usage
 *
 * en:
 * C/C++ Build -> settings -> Build steps -> Post-build steps -> Command
 * agregar:
 * arm-none-eabi-nm -S --size-sort -s "${BuildArtifactFileName}"
 */



#endif /* HEADER_H_ */
