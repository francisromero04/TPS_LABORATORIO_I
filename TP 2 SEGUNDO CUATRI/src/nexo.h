#ifndef NEXO_H_
#define NEXO_H_

#include "jugador.h"
#include "confederacion.h"

int nexo_alta(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConf[], int TAM_CONF);
int nexo_baja(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConf[], int TAM_CONF);
eJugador nexo_modificarUno(eJugador jugador, eConfederacion lista[], int TAM_CONFED);
int nexo_modificacion(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConf[], int TAM_CONF);
void nexo_listarUno(eJugador jugador, eConfederacion confederacion);
int nexo_listarTodos(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED);
void nexo_listarUnaConfederacionConJugador(eJugador jugador, eConfederacion confederacion);
int nexo_listarConfederacionesConJugadores(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED);
int nexo_calcularContratoMasLargo(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED);
int nexo_calcularPromedios(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED);
int nexo_imprimirJugadorPorConfederacion(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED, char confederacion[]);
int nexo_listarRegionConMasJugadores(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED);

#endif /* NEXO_H_ */
