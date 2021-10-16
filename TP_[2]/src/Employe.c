/*
 * Employe.c
 *
 *  Created on: 11 oct. 2021
 *      Author: KEVIN
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employe.h"
#include "Biblioteca.h"

//prototipos de globales
static int dameUnIdNuevo(void);
static int selecionarcampoaModificar(int*selectedField);
static int getANombreEmpleados (char empleadoNombre[]);
static int getAApellidoEmpleados(char empleadosApellido[]);
static int getEmpleadoSector(int *sectorEmpleado);
static int getEmpleadoSalario(float *salarioEmpleado);
static int selecionarModificar(void);

#define OCUPADO 0
#define VACIO 1
#define INTENTOS 3
#define NAME_AND_ADDRESS_LEN 128


//se inicializa por que hay basura en el array, y lo igualamos a 0 o lo dejamos libre.
//se inicializa la bandera flagEmpty
int Inicializar(Employes listadoDeEmpleados[],int len)
{
	int index;
	int bandera = -1;

	if(listadoDeEmpleados != NULL && len > 0)
	{
		for(index=0; index < len; index++)
		{
			listadoDeEmpleados[index].isEmpty = 1;
		}
		bandera=1;
	}
	return bandera;
}

//cargo los empleados
//llamo a la funcion pedir,numero,texto y floar
//devuelvo el resultado por puntero
//cambio el valor de la bandera a 0
int cargarEmpleados(Employes* list, int len, int id, char name[],char lastName[],float salary,int sector)
{
	int retorno=-1;
	int sectorAux;
	float salarioAux;
	char nombreAux[128];
	char apellidoAux[60];

	if(list!=NULL)
	{
		if(utn_getText(nombreAux, 128 , "Ingrese el nombre: ", "Error\n",3)==0)
		{
			if(utn_getText(apellidoAux,60, "Ingrese el apellido: ", "Error\n",3)==0)
			{
				if(utn_getNumeroInt(&sectorAux, "Ingrese el sector:  ", "Error\n",1, 1000, 3)==0)
				{
					if(utn_getNumeroFloat(&salarioAux, "Ingrese salario:  ", "Error\n",1, 100000, 3)==0)
					{
						list-> sector= sectorAux;
						list->salario = salarioAux;
						list->id = dameUnIdNuevo();
						strncpy(list->nombre,nombreAux,sizeof(list->nombre));
						strncpy(list->apellido,apellidoAux,sizeof(list->apellido));
						list->isEmpty = 0;
						retorno=0;
					}
				}
			}
		}
	}
	return retorno;
}

//funcion privada del archivo
//genero un id
//retorno el id
static int dameUnIdNuevo(void) //privada del archivo
{
	static int contador=0;
	contador++;//es global : mantiene su valor
	return contador;
}
//de las posiciones que esten con la bandera en 0
//imprimo los valores
int imprimir_empleados(Employes* pEmpleados)
{
	if(pEmpleados->isEmpty ==0)
	{
		printf("id: %d - %s - %d - %f - %s\n",pEmpleados->id, pEmpleados->nombre, pEmpleados->sector, pEmpleados->salario, pEmpleados->apellido);
	}
	return 1;
}
//recorro el array
//verifico que id exista
//retorno la posicion
int buscadorPorID(Employes* pEmpleados, int len, int IdBuscado)
{
	int status=-1;
	int index;

	if(pEmpleados!=NULL && len>0 && IdBuscado>=0)
	{
		for(index=0; index<len ; index++)
		{
			if( pEmpleados[index].id==IdBuscado && pEmpleados[index].isEmpty == 0)
			{
				status = index;
				break;
			}
		}
	}
	return status;
}
//recorro el array
//verifico que haya espacio
//retorno la posicion
int bucarLibre(Employes* pEmpleados, int len)
{
	int retorno=-1;
	int i;

	if(pEmpleados!=NULL && len>0)
	{
		for(i=0; i<len ;i++)
		{
			if(pEmpleados[i].isEmpty==VACIO)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}
//eliminar empleados
//cambion la bandera a 1 del id recivido
int Eliminar_empleados(Employes Empleados[], int len, int IdBuscado)
{
	int status = -1;

		status =1;
		Empleados[IdBuscado].isEmpty=1;
	return status;
}
//modifico posicion
//llamo a funcion para seleccionar opcion
//modifico opcion elegida
int modificarEmpleados(Employes* pEmpleados)
{
	int status=-1;
	int idamodificar;
	int auxsector;
	float auxsalario;
	char auxnombre[NAME_AND_ADDRESS_LEN];
	char auxapellido[NAME_AND_ADDRESS_LEN];
	if(pEmpleados !=NULL)
	{
		if(selecionarcampoaModificar(&idamodificar)==1)
		{
			status=1;
			switch (idamodificar)
			{
			case 1:
				if(getEmpleadoSector(&auxsector)==1)
				{
					pEmpleados->sector =auxsector;
				}
				break;
			case 2:
				if(getEmpleadoSalario(&auxsalario)==1)
				{
					pEmpleados->salario = auxsalario;
				}
				break;
			case 3:
				if(getANombreEmpleados(auxnombre)==1)
				{
					strncpy(pEmpleados->nombre, auxnombre, NAME_AND_ADDRESS_LEN);
				}
				break;
			case 4:
				if(getAApellidoEmpleados(auxapellido)==1)
				{
					strncpy(pEmpleados->apellido, auxapellido, NAME_AND_ADDRESS_LEN);
				}
				break;
			}
		}
	}
	return status;
}
//funcion privada del archivo
//llamo a la funcion perdir int
//retorno por puntero valor ingresado para la funcion modificar
static int selecionarcampoaModificar(int*selectedField)
{
	int status=-1;
	int auxSelecionItem;

	if(utn_getNumeroInt(&auxSelecionItem, "\nElegi la opcion:\n 1-sector\n 2-salario\n 3-nombre\n 4-apellido\n ", "Error",1 , 4, 2)==0)
	{
		status =1;
		*selectedField= auxSelecionItem;
	}
	return status;
}
//funcion privada del archivo
//llamo a la funcion pedir int
//retorno valor ingresado para funcion ordenamiento
static int selecionarModificar(void)
{
	int status;
	int auxSelecionItem;

	if(utn_getNumeroInt(&auxSelecionItem, "\n0)Ordenar A-Z:\n 1)ordenar Z-A\n", "Error",0 , 1, 1)==0)
	{
		status = auxSelecionItem;
	}
	return status;
}
//funcion privada del archivo
//llamo funcion pedir char
//retorno por puntero el valor ingresado para la funcion modificar
static int getANombreEmpleados (char empleadoNombre[])
{
	int status =-1;
	char mensaje[180];
	char auxNombre[NAME_AND_ADDRESS_LEN];
	strncpy(mensaje, "\nIngrese nombre del empleado: ",sizeof(mensaje));
	if(utn_getText(auxNombre, NAME_AND_ADDRESS_LEN , mensaje, "Error",1)==0)
	{
		status =1;
		strncpy(empleadoNombre, auxNombre, NAME_AND_ADDRESS_LEN);
	}
	return status;
}

//funcion privada del archivo
//llamo funcion pedir char
//retorno por puntero el valor ingresado para la funcion modificar
static int getAApellidoEmpleados(char empleadosApellido[])
{
	int status =-1;
	char mensaje[180];
	char auxapellido[NAME_AND_ADDRESS_LEN];
	strncpy(mensaje, "\nIngrese apellido del empleado:",sizeof(mensaje));
	if(utn_getText(auxapellido, NAME_AND_ADDRESS_LEN , mensaje, "Error",1)==0)
	{
		status =1;
		strncpy(empleadosApellido, auxapellido, NAME_AND_ADDRESS_LEN);
	}
	return status;
}
//funcion privada del archivo
//llamo funcion pedir int
//retorno por puntero el valor ingresado para la funcion modificar
static int getEmpleadoSector(int *sectorEmpleado)
{
	int status =-1;
	char mensaje[180];
	int auxsector;
	strncpy(mensaje,"\nIngrese sector del empleado:", sizeof(mensaje));
	if(utn_getNumeroInt(&auxsector, mensaje, "Error",0, 1, 3)==0)
	{
		status=1;
		*sectorEmpleado=auxsector;
	}
	return status;
}

//funcion privada del archivo
//llamo funcion pedir float
//retorno por puntero el valor ingresado para la funcion modificar
static int getEmpleadoSalario(float *salarioEmpleado)
{
	int status =-1;
	char mensaje[NAME_AND_ADDRESS_LEN];
	float auxsalario;
	strncpy(mensaje,"\nIngrese precio por dia:", sizeof(mensaje));
	if(utn_getNumeroFloat(&auxsalario, mensaje, "Error",1, 100000, 3)==0)
	{
		status=1;
		*salarioEmpleado = auxsalario;
	}
	return status;
}
//funcion ordenamiento
//llamo funcion seleccionar
//ordeno dependiendo opcion ingresada
//
int cliente_ordenarApellidoSector(Employes *array, int limite)
{
	int estado=-1;
	int flagSwap;
	int auxComt;
	Employes buffer;

	if(array != NULL && limite>=0)
	{
		flagSwap=0;
		if(selecionarModificar()==0)
		{
			do{
				flagSwap=0;
				for(int i=0; i<limite-1; i++)
				{
					auxComt = strncmp(array[i].apellido,array[i+1].apellido,NOMBRE_Y_APELLIDO_LEN);
					if(auxComt >0 || (auxComt==0 && array[i].sector < array[i+1].sector))
					{
					flagSwap = 1;
					buffer = array[i];
					array[i] = array[i+1];
					array[i+1] = buffer;
					estado=0;
					}
				}
			limite--;
			}while(flagSwap);
		}
		else
		{
			do{
				flagSwap=0;
			for(int i=0; i<limite-1; i++)
			{
				auxComt = strncmp(array[i].apellido,array[i+1].apellido,NOMBRE_Y_APELLIDO_LEN);
				if(auxComt < 0 || (auxComt==0 && array[i].sector < array[i+1].sector))
				{
					flagSwap = 1;
					buffer = array[i];
					array[i] = array[i+1];
					array[i+1] = buffer;
					estado=0;
			   }
			}
			limite--;
			}while(flagSwap);
		}
	}
	return estado;
}
//funcion promedio
//recorro el array
//guarco contador y acumulador
//saco el promedio
int promedio(Employes *list, int len)
{
	int estado=-1;
	int cont=0;
	float acum=0;
	float promedio=0;
	int contadorS=0;

	for(int i=0; i <len ;i++)
	{
		if(list[i].isEmpty==0)
		{
			cont++;
			acum = acum + list[i].salario;
			estado=0;
		}
	}
	promedio= acum/cont;
	for(int indice = 0; indice <len ;indice++)
	{
		if(list[indice].isEmpty==0 && list[indice].salario > promedio)
		{
			contadorS++;
		}
	}
	printf("\nel promedio es: %f\n",promedio);
	printf("Cobran mas que el promedio: %d",contadorS);
		return estado;
}
//menu
//llamo funcion pedir int para que usuario eliga la opcion del menu

void menuEmployee (Employes list[], int len)
	{
		int opcion;
		int lugarLibre;
		int bandera;
		do{
			if (utn_getNumeroInt(&opcion, "\nBienvenido \n1)Altas:\n2)Modificar:\n3)Baja:\n4)Informar:", "\nError opcion Invalida",  1, 4, 10)==0)
				{
				switch (opcion)
					{
						case 1:
							//busco lugar libre
							lugarLibre = bucarLibre(list, len);
							//pido y cargo los datos ingresados
				cargarEmpleados(&list[lugarLibre], len, list[lugarLibre].id, list[lugarLibre].nombre, list[lugarLibre].apellido, list[lugarLibre].salario, list[lugarLibre].sector);
							bandera=1;
						break;
						case 2:
							//verifico que se haya cumplido la opcion 1
							if(bandera==1)
							{
								//recorro el array para imprimir los datos cargados
								for(int i=0;i< len ;i++)
								{
									imprimir_empleados(&list[i]);
								}

								int idIngresado;
								int indexAModif;
								//pido que ingrese un numero a buscar
								//verifico que exista
								//llamo a la funcion modificar y imprimo
								if (utn_getNumeroInt(&idIngresado, "\ningrese ID\n", "Error", 1, 9999, 5) ==0)
								{
									indexAModif = buscadorPorID(list,len,idIngresado);
									if(indexAModif >=0)
									{
										modificarEmpleados(&list[indexAModif]);
										imprimir_empleados(&list[indexAModif]);
									}
								}
							}
							else{
								printf("Error, no hay empleados cargados\n");
							}
							break;
						case 3:
							//verifico que la opcion 1 se haya ingresado
							if(bandera ==1)
							{
								//recorro el array para imprimir los datos cargados
								for(int i=0;i< len ;i++)
								{
									imprimir_empleados(&list[i]);
								}
									int idingre;
									int idDarBaja;
									//pido que ingrese un numero a buscar
									//verifico que exista
									//llamo a la funcion eliminar y imprimo
									if (utn_getNumeroInt(&idingre, "\ningrese ID a eliminar\n", "Error", 1, 9999, 5) ==0)
									{
										idDarBaja = buscadorPorID(list,len,idingre);
										if(idDarBaja>=0)
										{
											Eliminar_empleados(list,len,idingre);
											printf("Empleado eliminado\n");
										}
									}
							}
							else
							{
								printf("Error, no hay empleados cargados\n");
							}
							break;
						case 4:
							//verifico que la opcion 1 se haya ingresado
							if(bandera==1)
							{
								//llamo funcion ordenar
								//verifico que la funcion ordenar devuelva 0
								//imprimo
								if(cliente_ordenarApellidoSector(list, len)==0)
								{
									for(int index=0;index< len ;index++)
									{
										imprimir_empleados(&list[index]);
									}
								}
									promedio(list,len);
							}
							else
							{
								printf("\n No hay empleados ingresados\n");
							}

						break;
					}
				}
		}while (opcion <4);
	}
