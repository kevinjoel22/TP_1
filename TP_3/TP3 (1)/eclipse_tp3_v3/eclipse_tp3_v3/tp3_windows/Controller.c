#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Biblioteca.h"
#include "parser.h"
#include "Controller.h"
#include "string.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE *auxP;
	auxP =fopen(path,"r"); //abro y leo el archivo
	if(auxP!=NULL)
	{
		if(parser_EmployeeFromTextLectura(auxP, pArrayListEmployee)==0) //les paso a parser el puntero a archivo para que los transforme
		{
		retorno=0;
		}
	}
	else
	{
		printf("hay un error");
	}
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE *auxP;
	auxP =fopen(path,"rb"); //abro y leo el archivo

	if(auxP!=NULL)
	{
		puts("estoy dentro del NULL frombinary");
		if(parser_EmployeeFromBinary(auxP, pArrayListEmployee)==0) //les paso a parser el puntero a archivo para que los transforme
		{
		retorno=0;
		}
	}
	else
	{
		retorno=-1;
		printf("hay un error");
	}
	fclose(auxP);
    return retorno;
}


/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */


int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	char nombreAux[128];
	int id;
	int horasAux;
	int salarioAux;

	Employee *nuevoEmpleado;
	Employee* auxid;
	if(pArrayListEmployee!=NULL)
	{
		if(utn_getText(nombreAux, 128 , "Ingrese el nombre:\n", "Error\n",3)==0 &&
			utn_getNumeroInt(&horasAux, "Ingrese horas:\n", "Error\n",1, 1000, 3)==0 &&
			utn_getNumeroInt(&salarioAux, "Ingrese salario:\n  ", "Error\n",1, 100000, 3)==0)
			{
				auxid= ll_get(pArrayListEmployee, ll_len(pArrayListEmployee)-1);
				employee_getId(auxid, &id);
				id++;
				printf("valor de id:%d\n",id);
				nuevoEmpleado = employee_newParametrosAdd(id,nombreAux,horasAux,salarioAux);
				retorno=0;
			}
		if(nuevoEmpleado!=NULL)
		{
			ll_add(pArrayListEmployee, nuevoEmpleado );
			retorno=0;
		}
	}

	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int len;
	int idBuscado;
	int id;
	char nombre[128];
	int horas;
	int sueldo;
	int opcion;

	Employee* aux;

	if(pArrayListEmployee!=NULL)
	{
		len = ll_len(pArrayListEmployee);
		if(len>=0)
		{
			controller_ListEmployee(pArrayListEmployee);

			utn_getNumeroInt(&id,"Ingrese id del empleado a modificar\n" , "Error\n", 1, 2000, 3);

			idBuscado = Controller_buscarById(pArrayListEmployee, len, id);

			if(idBuscado!=-1)
			{
				aux = (Employee*)ll_get(pArrayListEmployee, idBuscado);

				employee_imprimir(aux, idBuscado);

				puts("1)Modificar nombre");
				puts("2)Modificar horas");
				puts("3)Modificar sueldo");
				utn_getNumeroInt(&opcion, "Ingrese opcion a modificar\n", "Error, ingrese opcion a modificar", 1, 3, 3);

				switch(opcion)
				{
					case 1:
						utn_getText(nombre, 128, "Ingrese nuevo nombre:\n", "Error, Ingrese nuevo nombre\n", 3);

						employee_setNombre(aux,nombre);

						break;
					case 2:
						utn_getNumeroInt(&horas, "Ingrese hora a modificar\n", "Error, ingrese hora a modificar", 1, 1000, 3);

						employee_setHorasTrabajadas(aux, horas);

						break;
					case 3:
						utn_getNumeroInt(&sueldo, "Ingrese sueldo a modificar\n", "Error, ingrese sueldo a modificar", 1, 10000, 3);

						employee_setSueldo(aux, sueldo);

						break;
				}
			}
			else
			{
				puts("NO existe ese id.");
			}
		}
		else
		{
			puts("No hay nada cargado.");
		}
	}




    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int idBuscado;
	int id;
	int len;


	if(pArrayListEmployee!=NULL)
	{
		len = ll_len(pArrayListEmployee);
		if(len>0)
		{
			controller_ListEmployee(pArrayListEmployee);

			if(utn_getNumeroInt(&idBuscado, "Ingrese id a buscar:\n", "id Invalido.\n",1, 2000, 3)==0)
			{
				puts("hola");
				id = Controller_buscarById(pArrayListEmployee, ll_len(pArrayListEmployee), idBuscado);

				ll_remove(pArrayListEmployee, id);
				retorno =0;
			}
		}
		else
		{
			puts("No hay empleados ingresados.");
		}
	}
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int tam;
	Employee* empleado;
	if(pArrayListEmployee!=NULL)
	{
		tam= ll_len(pArrayListEmployee);
		for(int i=0; i<tam; i++)
		{
			empleado= (Employee*)ll_get(pArrayListEmployee,i);
			employee_imprimir(empleado,i);
			retorno=0;
		}
	}
	return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int opcion;
	if(pArrayListEmployee!=NULL)
	{
		if(ll_len(pArrayListEmployee)>=0)
		{
			puts("1)ordenar por nombre");
			puts("2)ordenar por hora trabajadas");
			puts("3)ordenar por sueldo");
			utn_getNumeroInt(&opcion, "Ingrese opcion a modificar\n", "Error,Ingrese OPcion a modificar\n", 1, 3, 3);

				switch(opcion)
				{
				case 1:
					if(ll_sort(pArrayListEmployee, OrdenamientoPorNombre, 1)==0)
					{
						retorno=0;
					}
					break;
				case 2:
					if(ll_sort(pArrayListEmployee, OrdenamientoPorhora, 1)==0)
					{
						retorno=0;
					}
					break;
				case 3:
					if(ll_sort(pArrayListEmployee, OrdenamientoPorSueldo, 1)==0)
					{
						retorno=0;
					}
					break;
				}
		}
		else
		{
			puts("Error, no hay Empleados cargados");
		}
	}
	else
	{
		puts("Error. no hay empleados en la lista");
	}
    return retorno;
}

int OrdenamientoPorNombre(void* empleadoZ, void*empleadoX)
{
	int retorno=0;
	retorno = strcmp(((Employee*)empleadoZ)->nombre,((Employee*)empleadoX)->nombre);
	return retorno;
}

int OrdenamientoPorhora(void* empleadoZ, void* empleadoX)
{
	int retorno=0;

	if(((Employee*)empleadoZ)->horasTrabajadas > ((Employee*)empleadoX)->horasTrabajadas)
	{
		retorno=1; // empleado empleado 1 labura mas que el 2
	}
	else
	{
		if(((Employee*)empleadoZ)->horasTrabajadas < ((Employee*)empleadoX)->horasTrabajadas)
		{
			retorno=-1; // empleado 2 labura mas que el 1
		}
		else
		{
			retorno=0; // empleado trabajan las mismas horas
		}
	}

	return retorno;
}

int OrdenamientoPorSueldo(void* empleadoZ,void* empleadoX)
{
	int retorno=0;
	if(((Employee*)empleadoZ)->sueldo > ((Employee*)empleadoX)->sueldo)
		{
			retorno=1; // empleado empleado 1 labura mas que el 2
		}
		else
		{
			if(((Employee*)empleadoZ)->sueldo < ((Employee*)empleadoX)->sueldo)
			{
				retorno=-1; // empleado 2 labura mas que el 1
			}
			else
			{
				retorno=0; // empleado trabajan las mismas horas
			}
		}
	return retorno;
}



/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;

	FILE* aux;
	if(pArrayListEmployee!=NULL)
	{
		aux = fopen(path,"w");

		if(aux!=NULL)
		{
			parser_EmployeeFromTextEscritura(aux, pArrayListEmployee);
			retorno=0;
		}
	}
	fclose(aux);
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE* aux;

	if(pArrayListEmployee!=NULL)
	{
		aux = fopen(path,"wb");
		if(aux!=NULL)
		{
			if(parser_EmployeeFromBinaryEscritura(aux, pArrayListEmployee)==0)
			{
			puts("se Escribio en binario");
			retorno=0;
			}
		}
	}
	fclose(aux);
    return retorno;
}

int employee_imprimir(Employee* auxEmpleado, int indice)
{
	int retorno=-1;
	int idaux;
	int horaAux;
	int sueldoAux;
	char nombre[128];

	employee_getId(auxEmpleado,&idaux);
	employee_getNombre(auxEmpleado,nombre);
	employee_getHorasTrabajadas(auxEmpleado,&horaAux);
	employee_getSueldo(auxEmpleado,&sueldoAux);

	if(auxEmpleado!=NULL && indice>=0)
	{
		printf("id:%d - nombre:%s - horas:%d - salario:%d \n",idaux,nombre,horaAux,sueldoAux);
		retorno=0;
	}
	return retorno;
}

int Controller_buscarById(LinkedList* pArrayList,int len, int IdBuscado)
{
	int status=-1;
	int index;
	int idAux;
	Employee* aux;

	if(pArrayList!=NULL && len>0 && IdBuscado>=0 && IdBuscado<=len)
	{
		puts("estot en buscar");
		for(index=0; index<len ; index++)
		{
			aux = (Employee*)ll_get(pArrayList, index);

			employee_getId(aux, &idAux);

			if(idAux==IdBuscado)
			{
				status = index;
				break;
			}
		}
	}
	return status;
}

