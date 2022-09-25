#ifndef FUNCIONESTP_H_
#define FUNCIONESTP_H_

#include "utn.h"

#define ARQUEROS 1
#define DEFENSORES 2
#define MEDIOCAMPISTAS 3
#define DELANTEROS 4

#define AFC 5
#define CAF 6
#define CONCACAF 7
#define CONMEBOL 8
#define UEFA 9
#define OFC 10

int ingresarCostos(int* primerCosto, int* segundoCosto, int* tercerCosto);
int menuIngresoJugadores(int* contadorUno, int* contadorDos, int* contadorTres, int* contadorCuatro, int* contadorCinco, int* contadorSeis, int* sumaJugadores);
int calcularCostoMantenimiento(int primerCosto, int segundoCosto, int tercerCosto, int* costoMantenimiento);
void imprimirCalculos(int costoMantenimiento, float promedioAfc, float promedioCaf, float promedioConcacaf, float promedioConmebol, float promedioUefa, float promedioOfc);

#endif /* FUNCIONESTP_H_ */
