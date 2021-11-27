/*
 * UTN_Biblioteca.h
 *
 *  Created on: 7 sep. 2021
 *      Author: KEVIN
 */

#ifndef UTN_BIBLIOTECA_H_
#define UTN_BIBLIOTECA_H_

int utn_getNumeroInt (int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int suma(int numero1, int numero2);
int resta(int numero1, int numero2);
int multiplicacion(int numero1, int numero2);
int division(int numero1, int numero2, float *pResultado); //1y 2 pasaje por valor / pasaje por referencia
int factorial(int numero, int *pFactorial);



#endif /* UTN_BIBLIOTECA_H_ */
