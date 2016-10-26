
#define NUMSAMP 2048
// espectro que vino de la fft al cuadrado
//void arm_dot_prod_q31	(	q31_t * 	espectro, q31_t * 	espectro, uint32_t 	NUMSAMP, q63_t * 	DEP)

void arm_dot_prod_q31(*espectro,*espectro,NUMSAMP,*DEP); // DEVUELVE LA DENSIDAD ESPECTRAL DE POTENCIA

// busco el maximo

/*void arm_max_q31	(	q31_t * 	DEP,
uint32_t 	NUMSAMP,
q31_t * 	pResult,
uint32_t * 	pIndex 
)*/


void arm_max_q31(*DEP,NUMSAMP,*pResult,*pIndex);// DEVUELVE EL MAXIMO	

// armo las cuentas

f0=AUXdep[pIndex];//f0 al cuadrado
invf0=1/f0;

q63_t auxnum=0;
int index=pIndex;
//sumatoria de armonicos
while(index<2048)
{
    auxnum=DEP[index]+auxnum;
    index=index*2;
}

/*
arm_status arm_sqrt_q31	(	q31_t 	in,
q31_t * 	pOut 
)	
*/

pre=(auxnum*invf0);


status=arm_sqrt_q31	(pre,*THD); 


//THD+N   
q63_t auxnumerador=0;
for(i=0;i<2048;i++)
{
    auxnumerador=auxnumerador+DEP[i];
}

auxnumerador=auxnumerador-f0;

preN=(auxnumerador*invf0);

status=arm_sqrt_q31	(preN,*THDN); 
