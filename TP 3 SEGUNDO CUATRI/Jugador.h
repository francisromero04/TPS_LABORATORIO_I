#ifndef jug_H_INCLUDED
#define jug_H_INCLUDED

#include "LinkedList.h"
#include "utn.h"

typedef struct
{
	int id;
	char nombreCompleto[100];
	int edad;
	char posicion[30];
	char nacionalidad[30];
	int idSeleccion;
}eJugador;

eJugador* jug_new();
eJugador* jug_newParametros(char* idStr, char* nombreCompletoStr, char* edadStr, char* posicionStr, char* nacionalidadStr, char* idSelccionStr);
eJugador* jug_newParametrosAlta(int id, char* nombreCompletoStr, int edad, char* posicionStr, char* nacionalidadStr, int idSelccion);
void jug_delete();

int jug_setId(eJugador* this,int id);
int jug_setNombreCompleto(eJugador* this,char* nombreCompleto);
int jug_setEdad(eJugador* this,int edad);
int jug_setPosicion(eJugador* this,char* posicion);
int jug_getNacionalidad(eJugador* this,char* nacionalidad);
int jug_setIdSeleccion(eJugador* this,int idSeleccion);

int jug_getId(eJugador* this,int* id);
int jug_getNombreCompleto(eJugador* this,char* nombreCompleto);
int jug_getEdad(eJugador* this,int* edad);
int jug_getPosicion(eJugador* this,char* posicion);
int jug_setNacionalidad(eJugador* this,char* nacionalidad);
int jug_getIdSeleccion(eJugador* this,int* idSeleccion);

int eJugador_actualizarUltimoId(int idAnterior);
void eJugador_imprimir(eJugador* this);

int jug_criterioNacionalidad(void* pUno, void* pDos);
int jug_criterioEdad(void* pUno, void* pDos);
int jug_criterioNombre(void* pUno, void* pDos);
int jug_estadoConvocatoria(int idSeleccion , char* estadoStr);

#endif // jug_H_INCLUDED
