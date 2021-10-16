/*
 ============================================================================
 Name        : TP_[2].c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Employe.h"
#include "Biblioteca.h"
#define CANTIDAD_DE_EMPLEADOS 1000
int main(void) {
	setbuf(stdout,NULL);

	Employes listadoDeEmpleados[CANTIDAD_DE_EMPLEADOS];

	Inicializar(listadoDeEmpleados,CANTIDAD_DE_EMPLEADOS);

	menuEmployee(listadoDeEmpleados, CANTIDAD_DE_EMPLEADOS);

	return EXIT_SUCCESS;
}
