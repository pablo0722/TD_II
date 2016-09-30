/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#include "semphr.h"

/*****************************************************************************
 * Private defines
 ****************************************************************************/
#define LED_port		0
#define LED_pin			22
#define LED_on			1
#define LED_off			0
#define TIMER_match0	0

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

xSemaphoreHandle SEM_led;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();

	// Configuramos los pines para todos los puntos.
	// Led del stick P0,22
	Chip_IOCON_PinMux(LPC_IOCON, LED_port, LED_pin, MD_PLN, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, LED_port, LED_pin);

	// Configuramos un timer para el punto (B).
	// Inicializamos, energizamos el periférico.
	Chip_TIMER_Init(LPC_TIMER0);
	// Le damos una frecuencia.
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_TIMER0, SYSCTL_CLKDIV_1);
	Chip_TIMER_PrescaleSet(LPC_TIMER0, 0);
	// Configuramos el match.
	// PUNTO (B)
//	Chip_TIMER_SetMatch(LPC_TIMER0, TIMER_match0, SystemCoreClock / 100000);	// 10uS * Main Clock
//	Chip_TIMER_SetMatch(LPC_TIMER0, TIMER_match0, SystemCoreClock / 10);		// 100mS * Main Clock para verlo visualmente
	// PUNTO (C)
	Chip_TIMER_SetMatch(LPC_TIMER0, TIMER_match0, SystemCoreClock / 1);			// 1S * Main Clock
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, TIMER_match0);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, TIMER_match0);
	Chip_TIMER_StopOnMatchDisable(LPC_TIMER0, TIMER_match0);
	Chip_TIMER_ExtMatchControlSet(LPC_TIMER0, 0, TIMER_EXTMATCH_DO_NOTHING, 0);
	// Disparamos el timer.
	Chip_TIMER_Enable(LPC_TIMER0);
	// Habilitamos las interrupciones.
	NVIC_EnableIRQ(TIMER0_IRQn);
}

/* Interrupción del timer0 */
void TIMER0_IRQHandler(void)
{
	portBASE_TYPE pxHigherPriorityTaskWoken = pdFALSE;

	// Nos fijamos si fue interrupción por el match
	if(Chip_TIMER_MatchPending(LPC_TIMER0, TIMER_match0))
	{

		/* PUNTO (B)
		// Hacemos togglear el led
		Chip_GPIO_SetPinToggle(LPC_GPIO, LED_port, LED_pin);
		*/

		// PUNTO (C)
		// Esto es para el caso de inversión de prioridades. Ejemplo: Una tarea de prioridad alta está bloqueada
		// y una de prioridad baja está ejecutándose con un semáforo tomado. Llega la interrupción y tiene que hacer
		// un cambio de contexto para la tarea de mayor prioridad. En la variable extra nos devuelve ese valor de prioridad.
		// La inicializamos en false, si el OS la cambia a true, es que hubo un cambio de contexto.
		xSemaphoreGiveFromISR(SEM_led, &pxHigherPriorityTaskWoken);
		// Función encargada de verificar si se levantó una tarea de mayor prioridad y de ejecutar un cambio de contexto.
		portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken);


		// Borramos el match
		Chip_TIMER_ClearMatch(LPC_TIMER0, TIMER_match0);

	}
}

/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters) {

	// Estado inicial
	Chip_GPIO_SetPinState(LPC_GPIO, LED_port, LED_pin, 0);

	while (1) {
		// OTRA FORMA DE HACER EL A)
		/* About a 3Hz on/off toggle rate */
//		Chip_GPIO_SetPinState(LPC_GPIO, LED_port, LED_pin, 0);
//		vTaskDelay(configTICK_RATE_HZ / 6);
//		Chip_GPIO_SetPinState(LPC_GPIO, LED_port, LED_pin, 1);
//		vTaskDelay(configTICK_RATE_HZ / 6);

		/*	 El scheduler la saca del estado running, la vuelve a ese estado cuando vence el tiempo del delay.
			 vTaskDelay y todo el OS trabaja como unidad los TICKS, entonces para hacerlo amigable, usamos esos
		 	 defines para pasarlo a segundos.
		 	 El número por el que dividimos es el período.
		*/

		/* PUNTO (A) parpadea cada 1 segundo.
		vTaskDelay( 1000 / portTICK_RATE_MS );
		Chip_GPIO_SetPinToggle(LPC_GPIO, LED_port, LED_pin);
		*/

		/* PUNTO (B) 1 micro segundo, pero NO FUNCIONA porque esos tiempos son muy pequeños en comparación con el tick.
		vTaskDelay( portTICK_RATE_MS / 100 );
		Chip_GPIO_SetPinToggle(LPC_GPIO, LED_port, LED_pin);
		*/

		/* PUNTO (B.1) para que parpadee cada 1uS durante 5S y durante otros 5S deje de hacerlo
//		Chip_GPIO_SetPinState(LPC_GPIO, LED_port, LED_pin, LED_off);
		NVIC_EnableIRQ(TIMER0_IRQn);
		vTaskDelay(5000 / portTICK_RATE_MS);
		NVIC_DisableIRQ(TIMER0_IRQn);
		vTaskDelay(5000 / portTICK_RATE_MS);
		*/

		/* PUNTO (C)
		 * La tarea toma el semáforo, ejecuta el código a continuación, sigue en el while(1) y cuando quiere
		 * volver a tomarlo, como ya está tomado, se bloquea, esperando a que el mismo sea liberado por la
		 * interrupción.
		*/

		// Tomamos el semáforo, y ponemos el delay máximo, el tiempo que le damos al semáforo, si no lo liberan
		// en ese tiempo, entonces la taera continua con la ejecución de la siguiente línea.
		xSemaphoreTake(SEM_led, portMAX_DELAY);

		Chip_GPIO_SetPinToggle(LPC_GPIO, LED_port, LED_pin);

	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{

	// PUNTO (C)
	// Creamos el semáforo.
	vSemaphoreCreateBinary(SEM_led);

	prvSetupHardware();


	/* LED1 toggle thread */
	/* Parámetros: Nombre de la tarea, es el puntero a función donde está la tarea
				   Nombre de la tarea para debuggear.
				   Espacio asignado al stack correspondiente para la tarea, para sus registros y variables.
				   Parámetros que recibe la tarea al momento de su creación.
				   Prioridad de la tarea.
				   Manejador de la tarea en caso de que queramos hacerle alguna modificación.
	*/
	xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
