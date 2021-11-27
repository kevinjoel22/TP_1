/*
 ============================================================================
 Name        : Trabajo.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "UTN_Biblioteca.h"


int main(void) {
	setbuf(stdout, NULL);

	int opcion;
	int numero1;
	int numero2;
	int calculo1;
	int calculo2;
	int calculo3;
	int calculo4;
	int calculo5;
	int calculo6;
	float resultado;
	int factorials;
	int factorial2;
	int flagUno=-1;

	do
	{
		printf("1)Ingrese primer numero: \n");
		printf("2)Ingrese segundo numero: \n");
		printf("3)Calcular todas las operaciones.\n");
		printf("4)Mostras todos los resultados.\n");
		printf("5)Salir.\n");
		scanf("%d", &opcion);

		switch(opcion)
		{
		//Ingresar numero 1
		case 1:
			//verifica si Ingreso numero 1
			if(utn_getNumeroInt (&numero1,"Ingrese un numero\n", "Error, ingrese un numero\n", 0, 100000, 2)==0)
			{
				flagUno=0;
			}
			break;
		//Ingresar numero2
		case 2:
			//verifica si numero 1 fue ingresado
			//les informa que necesitan ingresar el numero para continuar
			if(flagUno ==-1)
			{
				printf("Error, Ingrese primer numero 1:\n");
				break;
			}
			//verifica si Ingreso numero 2
			if(utn_getNumeroInt (&numero2,"Ingrese un numero\n", "Error, ingrese un numero\n", 0, 100000, 2)==0)
			{
				flagUno=0;
			}

			break;
			//Hago todas las cuentas
		case 3:
			//verifica si numero 1 y numero 2 fueron ingresados.
			//les informa que necesitan ingresar el numero para continuar
			if(flagUno ==-1)
			{
				printf("Error, Ingrese primero numero :\n");
				break;
			}
			//hago todas las cuentas con los numero 1 y 2
			calculo1 = suma(numero1, numero2);
			calculo2 = resta(numero1,numero2);
			calculo3 = multiplicacion(numero1,numero2);
			calculo4 = division(numero1,numero2,&resultado);
			calculo5 = factorial(numero1,&factorials);
			calculo6 = factorial(numero2,&factorial2);

			printf("Se hicieron todos los calulos\n");
			break;
			//muestro todos los resultados de los calculos
		case 4:
			//verifica si numero 1 y numero 2 fueron ingresados.
			//les informa que necesitan ingresar el numero para continuar
			if(flagUno ==-1)
			{
				printf("Error, Ingrese primero numero 1:\n");
				break;
			}
			printf("resultados:\n");
			printf("Suma: %d\n",calculo1);
			printf("resta: %d\n",calculo2);
			printf("multiplicacion: %d\n",calculo3);
			if(calculo4==0)
			{
				printf("divicion: %f \n",resultado);
			}
			else
			{
				printf("No se puede divir por 0\n.");
			}

			printf("el factorial de numero 1 es: %d\n",factorials);
				if(calculo5<0)
				{
					printf("No hay factorial negativo.\n");
				}
			printf("el factorial de numero 2 es: %d\n",factorial2);
				if(calculo6<0)
				{
					printf("No hay factorial negativo.\n");
				}
			break;
		//Fin de la calculadora y reinicio los estados
		case 5:
			flagUno=-1;
			printf("Fin\n");
			break;
		}
	}while(opcion !=5);

	return EXIT_SUCCESS;
}
