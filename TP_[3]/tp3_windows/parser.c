#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromTextLectura(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int cantidad;
	char buffer1[1024];//id
	char buffer2[1024];//nombre
	char buffer3[1024];//horas
	char buffer4[1024];//sueldo

	Employee* nuevoEmpleado;

	if(pFile !=NULL && pArrayListEmployee != NULL)
	{

	fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer1,buffer2,buffer3,buffer4);

		while(!feof(pFile))//recorre cada linea del archivo
		{
			cantidad = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer1,buffer2,buffer3,buffer4); // verifico que se pudieron levantar cada campo
			if(cantidad < 4)
			{
				break;
			}

			nuevoEmpleado = employee_newParametros(buffer1,buffer2,buffer3,buffer4); // contruyo un nuevo empleado con los datos que tengo en buffer

			ll_add(pArrayListEmployee,nuevoEmpleado); // agredo al linkedlist

			retorno=0;
		}
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */


int parser_EmployeeFromTextEscritura(FILE* pFile , LinkedList* pArrayListEmployee)
{
	Employee* auxEmpleado = NULL;
	int retorno=-1;
	int id;
	char nombre[128];
	int hora;
	int sueldo;

	if(pFile!=NULL && pArrayListEmployee !=NULL)
	{
		fprintf(pFile, "id,nombre,horasTrabajadas,sueldo\n");

		for(int i=0; i<ll_len(pArrayListEmployee); i++)
		{
			auxEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
			if(auxEmpleado!=NULL)
			{
				if(employee_getId(auxEmpleado, &id)==0 &&
				employee_getNombre(auxEmpleado, nombre)==0 &&
				employee_getHorasTrabajadas(auxEmpleado, &hora)==0 &&
				employee_getSueldo(auxEmpleado, &sueldo)==0)
				{
					puts("estoy dentro del fprintf");
				fprintf(pFile,"%d,%s,%d,%d\n", id, nombre, hora, sueldo);
				retorno=0;
				}
			}
		}
	}

	return retorno;
}



int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	Employee* auxEmpleados=NULL;
	int retorno=-1;
	int can=0;

	Employee aux;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		while(!feof(pFile))
		{
			can = fread(&aux, sizeof(Employee),1,pFile);
			if(can<1)
			{
				break;
			}
			auxEmpleados = employee_newParametrosAdd(aux.id, aux.nombre, aux.horasTrabajadas, aux.sueldo);
			if(auxEmpleados!=NULL)
			{
			ll_add(pArrayListEmployee, auxEmpleados);
			retorno=0;
			puts("estoy lladd");
			}
		}
	}
    return retorno;
}

int parser_EmployeeFromBinaryEscritura(FILE* pFile, LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int cantidad;
	int cantidadAux=0;

	Employee* empleado;

	if(pFile != NULL && pArrayListEmployee!=NULL)
	{
		for(int i=0; i< ll_len(pArrayListEmployee); i++)
		{
			empleado = (Employee*)ll_get(pArrayListEmployee, i);

			if(empleado!=NULL)
			{
				cantidad = fwrite(empleado, sizeof(Employee),1,pFile);

				if(cantidad<1)
				{
					break;
				}

				cantidadAux++;

				if(cantidadAux==ll_len(pArrayListEmployee))
				{
					retorno=0;
				}
			}
		}
	}
	return retorno;
}
