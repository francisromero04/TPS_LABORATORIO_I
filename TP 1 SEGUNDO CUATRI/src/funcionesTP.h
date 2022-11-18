#ifndef FUNCIONESTP_H_
#define FUNCIONESTP_H_

#include "utn.h"

int ingresarCostos(int* primerCosto, int* segundoCosto, int* tercerCosto);
int ingresarPosicion(int* contadorArqueros, int* contadorDefensores, int* contadorMediocampistas, int* contadorDelanteros);
int ingresarConfederacion(int* primerContador, int* segundoCotador, int* tercerContador, int* cuartoContador, int* quintoContador, int* sextoContador);
int calcularCostoMantenimiento(int primerCosto, int segundoCosto, int tercerCosto, int* costoMantenimiento);
void imprimirCalculos(int costoMantenimiento, float promedioAfc, float promedioCaf, float promedioConcacaf, float promedioConmebol, float promedioUefa, float promedioOfc);

#endif /* FUNCIONESTP_H_ */
