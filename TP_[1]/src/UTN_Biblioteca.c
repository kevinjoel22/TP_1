/*
 * UTN_Biblioteca.c
 *
 *  Created on: 7 sep. 2021
 *      Author: KEVIN
 */
#include <stdio.h>
#include <stdlib.h>
#include "UTN_Biblioteca.h"
#include <string.h>
#include <ctype.h>
/**
*\ brief: La funcion pide un numero  int a travez de un bucle y lo valida
*\ param: pido el puntero para guardar el numero
*\ param: pido el puntero del mensaje y lo muestro
*\ return retorno, devuelvo una bandera de que la opcion 1, para informar que fue realizada la operacion1
*/
static int getInt (int* pResultado);
static int esNumerica (char* cadena);
static int myGetsC (char* cadena, int longitud);

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

static int myGetsC (char* cadena, int longitud)
{

	fflush(stdin);
		//stdin lee el archivo temporal de lo que ingresa el usuario por consola
					//longitud de hasta donde leer
	fgets (cadena, longitud, stdin); //esto sirve para reemplazar el scanf
	cadena [strlen (cadena) - 1] = '\0';

	return 0;

}
/**
 *\brief verifica si un dato es de tipo numerico o no
 *\param pResultado es la cadena de caracteres a ser analizada
 *\retorna 0 en caso de ser falso y 1 en caso de ser positivo
 */
static int esNumerica (char* cadena)
{
	int retorno = 1;
	int i=0;
	if (cadena [0] == '-') //si en la posicion 0 el usuario ingresa un - el array comienza a almacenar los numeros desde la pocision 1
	{
		i = 1;
	}
		for (;cadena [i] > '\0'; i++)
		{
			if (cadena [i] < '0' || cadena [i] > '9')  //solo se pueden ingresar numeros del 0 al 9
			{
				retorno = 0;
				break;
			}
		}
	return retorno;
}
/**
 *\brief funsion para transformar la cadena a una variable de tipo int
 *\param pResultado puntero al espacio en memoria donde se almacenara el resultado de la funsion
 *\return retorna 0 en el caso de que este todo bien y -1 en caso de error
 */
static int getInt (int* pResultado)
{
	int retorno;
	char buffer [7500];
	if (myGetsC(buffer, sizeof (buffer))== 0 && esNumerica(buffer))
	{
		retorno = 0;
		*pResultado = atoi(buffer); //se transforma el dato string a un tipo de dato int
	}
	return retorno;
}
/**
 *\brief solicita un numero al usuario, luego de verificarlo devuelve el resultado
 *\param pResultado es el punter al espacio en memoria donde se almacenara el resultado de la funsion
 *\param mensaje es el mensaje que se mostrara al usuario
 *\param mensajeError es el mensaje de error que se le mostrara al usuario en caso de que ingrese un dato no valido
 *\param minimo es el minimo que sera aceptado
 *\param maximo es el maximo que sera aceptado
 *\param reintentos son los reintentos que tendra el usuario para ingresar el dato correctamente
 *\return 0 si se optuvo el dato o -1 en el caso de que no
 */
int utn_getNumeroInt (int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int bufferInt = -1;
	int retorno;
	int i;

	if (minimo<maximo)
	{
		for (i = 0; i <= reintentos; i++)
		{
			if (pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos != 0)
			{
				printf ("%s", mensaje);
				if (getInt (&bufferInt) == 0 && bufferInt>=minimo && bufferInt<=maximo)
				{
					*pResultado = bufferInt;
					retorno = 0;
					break;
				}
				else
				{
					retorno = 1;
					printf ("%s\n",mensajeError);
				}
			}
		}
	}
	return retorno;
}





