/*
 * rtos_init.c
 *
 *  Created on: 20 de oct. de 2016
 *      Author: Pablo
 */



#include "header.h"



#if USE_RTOS
	void task_init()
	{
			// *** Habilito los botones
		Chip_IOCON_PinMux (LPC_IOCON, BUTTON0, MD_PLN, IOCON_FUNC0 );
		Chip_GPIO_SetDir(LPC_GPIO, BUTTON0, ENTRADA);
		Chip_IOCON_PinMux (LPC_IOCON, BUTTON1, MD_PLN, IOCON_FUNC0 );
		Chip_GPIO_SetDir(LPC_GPIO, BUTTON1, ENTRADA);
		Chip_IOCON_PinMux (LPC_IOCON, BUTTON2, MD_PLN, IOCON_FUNC0 );
		Chip_GPIO_SetDir(LPC_GPIO, BUTTON2, ENTRADA);
		Chip_IOCON_PinMux (LPC_IOCON, BUTTON3, MD_PLN, IOCON_FUNC0 );
		Chip_GPIO_SetDir(LPC_GPIO, BUTTON3, ENTRADA);


			// *** Semaforos
		#if USE_ADC_EXTERNO
			vSemaphoreCreateBinary(sem_adc_pre);
			vSemaphoreCreateBinary(sem_adc_proc);
			vSemaphoreCreateBinary(sem_adc_post);
		#endif


			// *** Tareas
		xTaskCreate(vTask_THD, "vTask_THD", 		configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
		xTaskCreate(vtask_ImAlive, "vtask_ImAlive", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);



			// *** Inicia scheduler
		vTaskStartScheduler();
	}
#endif
