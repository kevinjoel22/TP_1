#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Biblioteca.h"
#include "Employee.h"
#include "LinkedList.h"

#define  NOMBRE_LEN 128

Employee* employee_new(void)
{
	Employee* aux;

	aux = (Employee*)malloc(sizeof(Employee));

	if(aux!=NULL)
	{
		employee_setId(aux, 0);
		employee_setNombre(aux," ");
		employee_setHorasTrabajadas(aux, 0);
		employee_setSueldo(aux, 0);
	}
	return aux;
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoSrt)
{
    int auxId;
    int auxHorasTrabajadas;
    int auxSueldo;
    Employee* aux = employee_new();

    if(idStr!= NULL && nombreStr!=NULL && horasTrabajadasStr!=NULL && sueldoSrt!=NULL)
    {
        auxId=atoi(idStr);
        auxHorasTrabajadas=atoi(horasTrabajadasStr);
        auxSueldo=atoi(sueldoSrt);

        if(aux != NULL)
        {
            if(employee_setId(aux, auxId)==1 ||
            employee_setNombre(aux, nombreStr)==1 ||
            employee_setHorasTrabajadas(aux, auxHorasTrabajadas)==1 ||
            employee_setSueldo(aux, auxSueldo)==1)
            {
            	free(aux);
            	printf("algo salio mal\n");
            }
        }
    }
    return aux;
}

Employee* employee_newParametrosAdd(int idStr,char* nombreStr,int horasTrabajadasStr, int sueldoStr)
{
    Employee* aux = employee_new();
	if(idStr>=0 && nombreStr != NULL && horasTrabajadasStr >=0 && sueldoStr>=0)
	{
		if(aux != NULL)
		{
			if(employee_setId(aux, idStr)==1 ||
			employee_setNombre(aux, nombreStr)==1 ||
			employee_setHorasTrabajadas(aux, horasTrabajadasStr)==1 ||
			employee_setSueldo(aux, sueldoStr)==1)
			{
				printf("Algo salio mal\n");
			}
		}
    }
    return aux;
}

int employee_setId(Employee* this, int id)
{
    int retorno=1;
    if(this!=NULL && id>0 )
    {

        this->id=id;
        retorno=0;
    }
    return retorno;
}

int employee_getId(Employee* this, int* id)
{
    int retorno=1;
    if(this!=NULL)
    {
        *id = this->id;
        retorno=0;
    }
    return retorno;
}

int employee_setNombre(Employee* this,char* nombre)
{
    int retorno=1;
    if(this!=NULL && nombre!=NULL && strlen(nombre)>1 && strlen(nombre)<30)
    {
        strncpy(this->nombre,nombre,NOMBRE_LEN);

        retorno=0;
    }
    return retorno;
}

int employee_getNombre(Employee* this,char* nombre)
{
    int retorno=1;
    if(this!=NULL && nombre!=NULL)
    {
        strncpy(nombre,this->nombre,NOMBRE_LEN);
        retorno=0;
    }
    return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int retorno=1;
    if(this!=NULL && horasTrabajadas>=0)
    {
        this->horasTrabajadas=horasTrabajadas;
        retorno=0;
    }
    return retorno;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int retorno=1;
    if(this!=NULL && horasTrabajadas!=NULL)
    {
        *horasTrabajadas=this->horasTrabajadas;
        retorno=0;
    }
    return retorno;
}

int employee_setSueldo(Employee* this,int sueldo)
{
    int retorno=1;
    if(this!=NULL && sueldo>0)
    {
        this->sueldo=sueldo;
        retorno=0;
    }
    return retorno;
}

int employee_getSueldo(Employee* this,int* sueldo)
{
    int retorno=1;
    if(this!=NULL && sueldo!=NULL)
    {
        *sueldo=this->sueldo;
        retorno=0;
    }
    return retorno;
}


