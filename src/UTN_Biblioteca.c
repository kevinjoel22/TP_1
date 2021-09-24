/*
 * UTN_Biblioteca.c
 *
 *  Created on: 7 sep. 2021
 *      Author: KEVIN
 */



#include <stdio.h>
#include <stdlib.h>
/**
*\ brief: La funcion pide un numero  int a travez de un bucle y lo valida
*\ param: pido el puntero para guardar el numero
*\ param: pido el puntero del mensaje y lo muestro
*\ return retorno, devuelvo una bandera de que la opcion 1, para informar que fue realizada la operacion1
*/

int utn_pedirNumero(int* pResultado, char* mensaje)
{
	int aux;
	int retorno=-1;

	if(pResultado!=NULL && mensaje != NULL)
	{
			printf("%s", mensaje);
			scanf("%d",&aux);
				*pResultado=aux;
				 retorno=0;
	}
	return retorno;
}

/**
*\ brief: La funcion para sumar
*\ param: pido el primer numero
*\ param: pido el segundo numero
*\ return: int, retorno el resultado de la operacion suma
*/
int suma(int numero1, int numero2)
{
	int suma;
			suma= numero1 + numero2;
	return suma;
}
/**
*\ brief: La funcion para restar
*\ param: pido el primer numero
*\ param: pido el segundo numero
*\ return: int, retorno el resultado de la operacion resta
*/
int resta(int numero1, int numero2)
{
	int resta;
	resta= numero1 - numero2;

	return resta;
}
/**
*\ brief: La funcion para multiplicar
*\ param: pido el primer numero
*\ param: pido el segundo numero
*\ return: int, retorno el resultado de la operacion multiplicacion
*/
int multiplicacion(int numero1, int numero2)
{
	int multiplicacion;
	multiplicacion= numero1 *numero2;
	return multiplicacion;
}
/**
*\ brief: La funcion para dividir
*\ param: pido el primer numero
*\ param: pido el segundo numero
*\ param: pido el puntero donde se guardara el resultado de la operacion
*\ return: int, retorno el estado de la operacion dividir
*/
int division(int numero1, int numero2, float *pResultado)
{
	int resultado;
	int estado=-1;


		if(numero2!=0)
		{
			resultado =(float) numero1 /numero2;
			estado=0;
			*pResultado = resultado;
		}
	return estado;
}
/**
*\ brief: La funcion para hacer el factorail
*\ param: pido el primer numero
*\ param: pido el segundo numero
*\ param: pido el puntero donde se guardara el resultado de la operacion
*\ return: int, retorno el estado de la operacion factorial
*/
int factorial(int numero, int *pFactorial)
{
	int factorial = 1;
	int estado=-1;

	if(numero>0)
	{
	for(int i=1; i<=numero; i++)
	{
		factorial = factorial*i;
	}
		estado=0;
		*pFactorial=factorial;
	}
	else
	{
			printf("No se puede hacer el factorial de un numero negativo");
	}
	return estado;
}
