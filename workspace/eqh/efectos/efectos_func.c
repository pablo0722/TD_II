/*
 * efectos_func.c
 *
 *  Created on: 8 de dic. de 2016
 *      Author: agustin
 */


#include "header.h"


#if (USE_EFECTOS)


volatile static q31_t delay_line[DELAY_LENGTH] __attribute__ ((section (".bss.$RamAHB32"))) = {0} ;


//efecto muestra a muestra

void distorsion(q31_t *in, q31_t *out, uint16_t length, q31_t dist)
{
	for(int i=0; i<length; i++)
	{
		if(in[i] > (q31_t) 0x20000000)
		{
			out[i] = (q31_t) 0x20000000;
		}
		else if(in[i] < (q31_t) 0xE0000000)
		{
			out[i] = (q31_t) 0xE0000000;
		}
		else
		{
			out[i] = in[i];
		}
			out[i] *= 3;
	}
}

void overdrive(q31_t *in, q31_t *out, uint16_t length, q31_t dist)
{
    for(int i=0; i<length; i++)
    {
    	in[i] *= dist;

    	if(in[i] > 0)
    	{
    		arm_sqrt_q31(in[i], &out[i]);
    	}
    	else
    	{
    		arm_abs_q31(&in[i], &out[i], 1);
    		arm_sqrt_q31(out[i], &out[i]);
    		out[i] *= -1;
    	}
    }
}


q31_t eco_iir(q31_t in, q31_t auxiliar, uint8_t densidad)
{
    static uint16_t delay_in_idx = 0;   // Indice para agregar muestra al delay_line
    static uint16_t delay_out_idx = 1;  // Indice para sumar al eco una muestra de la delay_line
    static uint8_t densidad_cont = 0;   // Sirve para agregar al delay_line una muestra de cada 'densidad' elementos (suma al eco 'densidad' veces la misma muestra)


    //prueba
    q31_t profundidad = 0x7F000000;
    densidad = 8;
    ////////



    q31_t eco = 0; // Eco IIR


    //eco = in - (profundidad*delay_line[delay_out_idx]); // Calcula el eco sumando una muestra anterior guardada en la delay_line
    eco = in + (profundidad*delay_line[delay_out_idx]); // Calcula el eco sumando una muestra anterior guardada en la delay_line


        // Una de cada 'densidad' muestras, agrega el eco a la delay_line
    densidad_cont++;
    densidad_cont %= densidad;

    if(!densidad_cont)
    {
        delay_line[delay_in_idx] = eco;

        delay_in_idx++;
        delay_in_idx %= DELAY_LENGTH;
        delay_out_idx++;
        delay_out_idx %= DELAY_LENGTH;
    }

    //prueba
    eco = delay_line[delay_out_idx];
	////////

    return eco;
}


q31_t reverb(q31_t in, q31_t profundidad, uint8_t densidad)
{
    static uint16_t delay_in_idx = 1;                   // Indice para agregar muestra al delay_line
    static uint16_t delay_out_idx[CANT_REVERB] = {0};   // Indice para sumar al eco una muestra de la delay_line
    static uint8_t densidad_cont = 0;                   // Sirve para agregar al delay_line una muestra de cada 'densidad' elementos (suma al eco 'densidad' veces la misma muestra)

    q31_t reverb = 0; // Reverb


    reverb = in;

    for(int i=0; i<CANT_REVERB; i++)
    	reverb += (profundidad*delay_line[delay_out_idx[i]]); // Calcula el eco sumando una muestra anterior guardada en la delay_line


    // Una de cada 'densidad' muestras, agrega el eco a la delay_line
    densidad_cont++;
    densidad_cont %= densidad;

    if(!densidad_cont)
    {
        delay_in_idx++;
        delay_in_idx %= DELAY_LENGTH;

        for(int i=0; i<CANT_REVERB; i++)
        {
            delay_out_idx[i]++;
            delay_out_idx[i] %= DELAY_LENGTH;
        }

        delay_line[delay_in_idx] = reverb;
    }

    return reverb;
}


q31_t flanger(q31_t in, q31_t profundidad, uint16_t cos_f, uint8_t densidad)
{
    static uint16_t delay_in_idx = 1;   // Indice para agregar muestra al delay_line
    static uint16_t delay_out_idx = 0;  // Indice para sumar al eco una muestra de la delay_line
    static uint16_t cos_n = 0;          // numero de muestra de la funcion coseno
    static uint8_t densidad_cont = 0;   // Sirve para agregar al delay_line una muestra de cada 'densidad' elementos (suma al eco 'densidad' veces la misma muestra)

    q31_t flanger = 0;
    uint16_t flanger_idx;               // Para calcular el indice del delay_line segun una funcion coseno


    cos_n++;
    if( (2*PI*cos_f*TS - 1) == 0 )
    {
        cos_n = 0;
    }

    flanger_idx = ((DELAY_LENGTH/2)-1)*cos(2*PI*cos_f*TS*cos_n) - (DELAY_LENGTH/2);
    flanger_idx = delay_out_idx - flanger_idx;

    if(flanger_idx > DELAY_LENGTH)
    {
        flanger_idx = DELAY_LENGTH - (pow(2,16)-flanger_idx);
    }

    flanger = in + (profundidad*delay_line[flanger_idx]); // Calcula el eco sumando una muestra anterior guardada en la delay_line

        // Una de cada 'densidad' muestras, agrega el eco a la delay_line
    densidad_cont++;
    densidad_cont %= densidad;

    if(!densidad_cont)
    {
        delay_in_idx++;
        delay_in_idx %= DELAY_LENGTH;
        delay_out_idx++;
        delay_out_idx %= DELAY_LENGTH;

        delay_line[delay_in_idx] = flanger;
    }

    return flanger;
}


#endif

