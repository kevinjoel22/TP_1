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
	//llamo funcion inicializar
	Inicializar(listadoDeEmpleados,CANTIDAD_DE_EMPLEADOS);
	//llamo a la funcion menu
	menuEmployee(listadoDeEmpleados, CANTIDAD_DE_EMPLEADOS);

	return EXIT_SUCCESS;
}
