#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "utn.h"

//ESTADO ABM
#define LIBRE 0
#define OCUPADO 1
#define BAJA -1

typedef struct
{
	int idJugador;
	char nombre[TAM_CHAR];
	char posicion[TAM_CHAR];
	int numeroCamiseta;
	int fk_idConfederacion;
	float salario;
	int aniosContrato;
	int isEmpty;
}eJugador;

int eJugador_getID(void);
void eJugador_inicializarlista(eJugador lista[], int TAM);
int eJugador_obtenerIndexLibre(eJugador lista[], int TAM);
eJugador eJugador_ingresarDatos(void);
int eJugador_buscarPorID(eJugador lista[], int TAM, int ID);
int eJugador_calcularSaldoPromedio(eJugador lista[], int TAM, float* saldoAcumulado, float* saldoPromedio);
int eJugador_verificarSalario(eJugador lista[], int TAM, float saldoPromedio);
void eJugador_ImprimirSaldoPromedio(float saldoAcumulado, float saldoPromedio, int jugadoresMayorSaldo);
int eJugador_sortPorID(eJugador lista[], int TAM);
int eJugador_harcodeo(eJugador lista[]);

#endif /* JUGADOR_H_ */
