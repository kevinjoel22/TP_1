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


int cargarEmpleados(Employes *pEmpleados)
{
	int retorno=-1;
	int sectorAux;
	float salarioAux;
	char nombreAux[128];
	char apellidoAux[60];

	if(pEmpleados!=NULL)
	{
		if(utn_getText(nombreAux, 128 , "Ingrese el nombre: ", "Error",3)==0)
		{
			if(utn_getText(apellidoAux,60, "Ingrese el apellido: ", "Error",3)==0)
			{
				if(utn_getNumeroInt(&sectorAux, "Ingrese el sector:  ", "Error",1, 1000, 3)==0)
				{
					if(utn_getNumeroFloat(&salarioAux, "Ingrese salario:  ", "Error",1, 100000, 3)==0)
					{
						pEmpleados-> sector= sectorAux;
						pEmpleados->salario = salarioAux;
						pEmpleados->id = dameUnIdNuevo();
						strncpy(pEmpleados->nombre,nombreAux,sizeof(pEmpleados->nombre));
						strncpy(pEmpleados->apellido,apellidoAux,sizeof(pEmpleados->apellido));
						pEmpleados->isEmpty = 0;
						retorno=0;
					}
				}
			}
		}
	}
	return retorno;
}


static int dameUnIdNuevo(void) //privada del archivo
{
	static int contador=0;
	contador++;//es global : mantiene su valor
	return contador;
}

int imprimir_empleados(Employes* pEmpleados)
{
	if(pEmpleados->isEmpty ==0)
	{
		printf("id: %d - %s - %d - %f - %s\n",pEmpleados->id, pEmpleados->nombre, pEmpleados->sector, pEmpleados->salario, pEmpleados->apellido);
		/*printf("\nsector: %d", pEmpleados->sector);
		printf("\nsalario: %f", pEmpleados->salario);
		printf("\nid: %d", pEmpleados->id);
		printf("\nnombre: %s",pEmpleados->nombre);
		printf("\napellido: %s", pEmpleados->apellido);*/
	}
	return 1;
}

int buscadorPorID(Employes* pEmpleados, int len, int IdBuscado, int *pFounIdPosition)
{
	int status=-1;
	int index;

	if(pEmpleados!=NULL && len>0 && IdBuscado>=0)
	{
		for(index=0; index<len ; index++)
		{
			if( pEmpleados[index].id==IdBuscado && pEmpleados[index].isEmpty == 0)
			{
				*pFounIdPosition = index;
				status = 1;
				break;
			}
		}
	}
	return status;
}

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
int Eliminar_empleados(Employes Empleados[], int len, int IdBuscado)
{
	int status = -1;
	int foundDisplayPosition;

	if(buscadorPorID(Empleados,len, IdBuscado, &foundDisplayPosition)==1)
	{
		status =1;
		Empleados[foundDisplayPosition].isEmpty=1;
	}
	return status;
}
//MOSTRAR LISTADO A modificar
//seleccionar id a modificar
//buscar el id
//Modificar l pantalla

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
							lugarLibre = bucarLibre(list, len);
							cargarEmpleados(&list[lugarLibre]);
							bandera=1;
						break;
						case 2:
							if(bandera==1)
							{
								if(cargarEmpleados(&list[lugarLibre])==1)
								{
									for(int i=0;i< len ;i++)
									{
										imprimir_empleados(&list[i]);
									}
									//----------------------------------------------------
									int idIngresado;
									int indexAModif;

									if (utn_getNumeroInt(&idIngresado, "\ningrese ID\n", "Error", 1, 9999, 5) ==0)
									{

										if(buscadorPorID(list,len,idIngresado,&indexAModif)==1)
										{
											modificarEmpleados(&list[indexAModif]);
											imprimir_empleados(&list[indexAModif]);
										}
										else
										{
											printf("ingresaste cualquiera\n");
										}
									}
								}
							}

							else{
								printf("Error, no hay empleados cargados\n");
							}
							break;
						case 3:
							if(bandera ==1)
							{
								for(int i=0;i< len ;i++)
								{
									imprimir_empleados(&list[i]);
								}
									int idingre;
									int idDarBaja;
									if (utn_getNumeroInt(&idingre, "\ningrese ID a eliminar\n", "Error", 1, 9999, 5) ==0)
									{
										if(buscadorPorID(list,len,idingre,&idDarBaja)==1)
										{
											Eliminar_empleados(list,len,idDarBaja);
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
							if(bandera==1)
							{
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
