#ifndef CONFEDERACION_H_
#define CONFEDERACION_H_

#include "utn.h"

//ESTADO ABM
#define LIBRE 0
#define OCUPADO 1
#define BAJA -1

typedef struct
{
	int idConfederacion;
	char nombre[TAM_CHAR];
	char region[TAM_CHAR];
	int anioCreacion;
	int isEmpty;
}eConfederacion;

int eConfederacion_getID(void);
void eConfederacion_inicializarlista(eConfederacion lista[], int TAM);
int eConfederacion_obtenerIndexLibre(eConfederacion lista[], int TAM);
eConfederacion eConfederacion_ingresarDatos(void);
eConfederacion eConfederacion_ingresarUna(eConfederacion lista[], int TAM);
int eConfederacion_buscarPorID(eConfederacion lista[], int TAM, int ID);
void eConfederacion_imprimirUno(eConfederacion viaje);
int eConfederacion_imprimirTodos(eConfederacion viajees[], int TAM);
int eConfederacion_sortPorID(eConfederacion lista[], int TAM);
int eConfederacion_harcodeo(eConfederacion lista[]);
eConfederacion eConfederacion_modificarUno(eConfederacion viaje);
int eConfederacion_alta(eConfederacion lista[], int TAM);
int eConfederacion_baja(eConfederacion lista[], int TAM);
int eConfederacion_modificar(eConfederacion lista[], int TAM);
int eConfederacion_sortPorNombre(eConfederacion lista[], int TAM);

#endif /* CONFEDERACION_H_ */
