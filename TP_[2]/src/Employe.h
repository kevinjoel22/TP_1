/*
 * Employe.h
 *
 *  Created on: 11 oct. 2021
 *      Author: KEVIN
 */

#include <stdio.h>
#include <stdlib.h>
#ifndef EMPLOYE_H_
#define EMPLOYE_H_
#define NOMBRE_Y_APELLIDO_LEN 51
typedef struct{
	int id;
	char nombre[NOMBRE_Y_APELLIDO_LEN];
	char apellido[NOMBRE_Y_APELLIDO_LEN];
	float salario;
	int sector;
	int isEmpty;
}Employes;

int Inicializar(Employes listadoDeEmpleados[],int len);
int buscoEspacioLibre(Employes listadoDeEmpleados[], int listlen, int *pEmptyPosition);
int cargarEmpleados(Employes *pEmpleados);
int imprimir_empleados(Employes* pEmpleados);
int buscadorPorID(Employes* pEmpleados, int len, int IdBuscado, int *pFounIdPosition);
int bucarLibre(Employes* pEmpleados, int len);
int Eliminar_empleados(Employes pEmpleados[], int len, int IdBuscado);
int modificarEmpleados(Employes* pEmpleados);
void menuEmployee (Employes list[], int len);
int promedio(Employes *list, int len);
int cliente_ordenarNombreSector(Employes *array, int limite);


#endif /* EMPLOYE_H_ */
