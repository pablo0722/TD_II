/*
===============================================================================
 Name        : THD_Meter.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <cr_section_macros.h>

#include "header.h"



#define     LENGTH_SAMPLES             2048					// Tamanio de los vectores de muestras (son complejos, doble tamano)
#define     FFT_SIZE    	           LENGTH_SAMPLES/2

int16_t spectrum[FFT_SIZE/2];		// Espectro de la senal transformada (solo la mitad, por estar espejado)
int16_t mSignalIn[LENGTH_SAMPLES], mFFTOut[LENGTH_SAMPLES];     	// Senal  de entrada y salida. Son vectores complejos.

uint8_t signalin_flag = 0;



/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE LENGTH_SAMPLES	/* Send */
#define UART_RRB_SIZE 2*50	/* Receive */

/* Transmit and receive buffers */
static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

/* Transmit and receive ring buffers */
STATIC RINGBUFF_T txring, rxring;

	//Colas
#define QUEUE_LEN_IN	1
#define QUEUE_LEN_REM	QUEUE_LEN_IN
#define QUEUE_LEN_THD	1

#define QUEUE_ITEM_SIZE_IN	(sizeof(short int)*LENGTH_SAMPLES)
#define QUEUE_ITEM_SIZE_REM	QUEUE_ITEM_SIZE_IN
#define QUEUE_ITEM_SIZE_THD	(sizeof(float))


xQueueHandle xQueue_in;
xQueueHandle xQueue_rem;
xQueueHandle xQueue_THD;




void FFTInit()
{
		// Asigno la direccion en memoria
		//mSignalIn     = (int16_t *) 0x2007C000;
		//mFFTOut       = (int16_t *)(0x2007C000 + LENGTH_SAMPLES * sizeof(int16_t));

		memset(mSignalIn, 	0, sizeof(int16_t) * LENGTH_SAMPLES );	//Inicializo en 0 la entrada
		memset(mFFTOut, 	0, sizeof(int16_t) * LENGTH_SAMPLES);		//Inicializo en 0 la salida

//		// Seno -- // Arma el seno de prueba (completa solo la parte real)
//		for(indice=0; indice < FFT_SIZE ; indice++)
//			mSignalIn[indice*2] = seno[indice];

}

void fft_function()
{
	int16_t i;
	int16_t real,imaginaria;
	// Segun la cantidad de muestras de la fft (definidas en FFT_SIZE) se llama a la funcion correspondiente
	#if FFT_SIZE == 64
		vF_dspl_fftR4b16N64(mFFTOut, mSignalIn);
	#elif FFT_SIZE == 256
		vF_dspl_fftR4b16N256(mFFTOut, mSignalIn);
	#elif FFT_SIZE == 1024
		vF_dspl_fftR4b16N1024(mFFTOut, mSignalIn);
	#elif FFT_SIZE == 4096
		vF_dspl_fftR4b16N4096(mFFTOut, mSignalIn);
	#else
	#endif

	// Se arma el espectro en frecuencia, a partir del modulo de la transformada
	// Se toman solamente la primer mitad de los puntos, ya que el espectro esta espejado
	for(i = 0; i < FFT_SIZE/2; i++)
	{
		// Se toman la parte real e imaginaria de cada punto
		real 		= mFFTOut[ i*2 ];
		imaginaria 	= mFFTOut[ i*2 + 1];

		// Se calcula cada punto del espectro obteniendo el modulo
		spectrum[i] = (int16_t) sqrt( (real * real) + ( imaginaria * imaginaria) );
	}
}
/*
void vTask_THD( void *pvParameters )
{
	short int buf_rem[QUEUE_LEN_IN];

	if(xQueueReceive(xQueue_in, mSignalIn, 0) == pdTRUE)
	{
		fft_function();

		signalin_flag = 0;

		xQueueSend(xQueue_rem, spectrum, 0);
	}
}*/

void main_init()
{
	SystemCoreClockUpdate();

	Board_Init();

	Board_UART_Init((uint32_t)LPC_UART0, 9600);

	/* Before using the ring buffers, initialize them using the ring
	   buffer init function */
	RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
	RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(LPC_UART0, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(UART0_IRQn, 1);
	NVIC_EnableIRQ(UART0_IRQn);

	const char Uart_init_msg[] = "\r\nHola mundo:\r\n";

	/* Envia mensaje inicial por UART*/
	Chip_UART_SendRB(LPC_UART0, &txring, Uart_init_msg, sizeof(Uart_init_msg));

	FFTInit();

	/*
		// Inicializacion de colas
	xQueue_in = xQueueCreate(QUEUE_LEN_IN, QUEUE_ITEM_SIZE_IN);
	xQueue_rem = xQueueCreate(QUEUE_LEN_REM, QUEUE_ITEM_SIZE_REM);
	xQueue_THD = xQueueCreate(QUEUE_LEN_THD, QUEUE_ITEM_SIZE_THD);

	xTaskCreate(vTask_THD, "vTask_THD", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);

	// Start the scheduler so the created tasks start executing.
	vTaskStartScheduler();
	*/
}

void main_uninit()
{
	/* DeInitialize UART1 peripheral */
	NVIC_DisableIRQ(UART0_IRQn);
	Chip_UART_DeInit(LPC_UART0);
}

/**
 * @brief	UART 1 interrupt handler using ring buffers
 * @return	Nothing
 */
void UART0_IRQHandler(void)
{
	static uint16_t idx=0;
	uint8_t read_char = 0;

	Chip_UART_IRQRBHandler(LPC_UART0, &rxring, &txring);

	int bytes = Chip_UART_ReadRB(LPC_UART0, &rxring, &read_char, 1);

	if(bytes>0)
	{
		char *SignalIn_p = (char *) mSignalIn;
		SignalIn_p[idx] = read_char;
		idx++;
		idx %= LENGTH_SAMPLES*2; //el "*2" es porq son int_16 y recibo de a int_8

		if(idx==0)
		{
			signalin_flag = 1;
		}
	}
}

int main(void)
{
	uint16_t i,j;

	main_init();

	while(1)
	{
		if (signalin_flag == 1)
		{
			/* Wrap value back around */
			//Chip_UART_SendRB(LPC_UART0, &txring, (const uint8_t *) &key, 1);

			fft_function();

			char *spec_p = (char *) spectrum;
			for(i=0; i<FFT_SIZE/2; i++)
			{
				Chip_UART_SendRB(LPC_UART0, &txring, (const uint8_t *) &spec_p[i*2], 1);
				Chip_UART_SendRB(LPC_UART0, &txring, (const uint8_t *) &spec_p[i*2+1], 1);

				for (j=1000; j>0; j--){};
			}

			signalin_flag = 0;

		}
	}

	main_uninit();

	while(1);

    return 0 ;
}