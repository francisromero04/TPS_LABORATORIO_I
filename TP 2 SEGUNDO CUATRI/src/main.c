#include <stdio.h>
#include <stdlib.h>
#include "nexo.h"

#define TAM_LISTA 3000

int main(void)
{
	setbuf(stdout, NULL);

	int opcion, opcionInforme, opcionSalir;
	int flagAlta = 0, flagHarcodeo = 0;
	int jugadoresMayorSaldo = 0;
	float saldoAcumulado, saldoPromedio;

	eJugador listaJugadores[TAM_LISTA];
	eConfederacion listaConfederaciones[TAM_LISTA];

	eJugador_inicializarlista(listaJugadores, TAM_LISTA);
	eConfederacion_inicializarlista(listaConfederaciones, TAM_LISTA);
	eConfederacion_harcodeo(listaConfederaciones);

	do
	{
		printf("\nMENU DE OPCIONES\n\n"
			   "1. ALTA DE JUGADOR\n"
			   "2. BAJA DE JUGADOR\n"
			   "3. MODIFICACION DE JUGADOR\n"
			   "4. INFORMES\n"
			   "5. ALTA JUGADORES HARCODEADOS\n"
			   "6. SALIR \n\n");
		utn_getNumero("INGRESE LA OPCION: ", "ERROR. ", 1, 6, 3, &opcion);

		switch(opcion)
		{
			case 1:
				nexo_alta(listaJugadores, TAM_LISTA, listaConfederaciones, TAM_LISTA);
				flagAlta = 1;
			break;

			case 2:
				if(flagAlta == 1 || flagHarcodeo == 1)
				{
					nexo_baja(listaJugadores, TAM_LISTA, listaConfederaciones, TAM_LISTA);
				}
				else
				{
					printf("\nNO ES POSIBLE DAR DE BAJA SIN HABER DADO DE ALTA UN JUGADOR PRIMERO.\n");
				}
			break;

			case 3:
				if(flagAlta == 1 || flagHarcodeo == 1)
				{
					nexo_modificacion(listaJugadores, TAM_LISTA, listaConfederaciones, TAM_LISTA);
				}
				else
				{
					printf("\nNO ES POSIBLE MODIFICAR SIN HABER DADO DE ALTA UN JUGADOR PRIMERO.\n");
				}
			break;

			case 4:
				if(flagAlta == 1 || flagHarcodeo == 1)
				{
					printf("\nMENU DE INFORMES\n\n"
						   "1. LISTADO DE LOS JUGADORES ORDENADOS ALFABETICAMENTE POR NOMBRE DE CONFEDERACION Y NOMBRE DE JUGADOR.\n"
						   "2. LISTADO DE CONFEDERACIONES CON SUS JUGADORES.\n"
						   "3. TOTAL Y PROMEDIO DE TODOS LOS SALARIOS Y CUANTOS JUGADORES COBRAN MAS DEL SALARIO PROMEDIO.\n"
						   "4. INFORMAR LA CONFEDERACION CON MAYOR CANTIDAD DE AÑOS DE CONTRATOS TOTAL.\n"
						   "5. INFORMAR PORCENTAJE DE JUGADORES POR CADA CONFEDERACION\n"
						   "6. INFORMAR CUAL ES LA REGION CON MAS JUGADORES Y EL LISTADO DE LOS MISMOS. \n\n");
					utn_getNumero("QUE OPCION DESEA INFORMAR?: ", "ERROR. ", 1, 6, 3, &opcionInforme);

					switch(opcionInforme)
					{
						case 1:
							nexo_sortPorNombre(listaJugadores, TAM_LISTA, listaConfederaciones, TAM_LISTA);
							nexo_listarTodos(listaJugadores, TAM_LISTA, listaConfederaciones, TAM_LISTA);
						break;

						case 2:
						 	nexo_listarConfederacionesConJugadores(listaJugadores, TAM_LISTA, listaConfederaciones, TAM_LISTA);
						break;

						case 3:
							eJugador_calcularSaldoPromedio(listaJugadores, TAM_LISTA, &saldoAcumulado, &saldoPromedio);
							jugadoresMayorSaldo = eJugador_verificarSalario(listaJugadores, TAM_LISTA, saldoPromedio);
							eJugador_ImprimirSaldoPromedio(saldoAcumulado, saldoPromedio, jugadoresMayorSaldo);
						break;

						case 4:
							nexo_calcularContratoMasLargo(listaJugadores, TAM_LISTA, listaConfederaciones, TAM_LISTA);
						break;

						case 5:
							nexo_calcularPromedios(listaJugadores, TAM_LISTA, listaConfederaciones, TAM_LISTA);
						break;

						case 6:
							nexo_listarRegionConMasJugadores(listaJugadores, TAM_LISTA, listaConfederaciones, TAM_LISTA);
						break;
					}
				}
				else
				{
					printf("\nNO ES POSIBLE IMPRIMIR SIN HABER DADO DE ALTA UN JUGADOR PRIMERO.\n");
				}
			break;

			case 5:
				if(eJugador_harcodeo(listaJugadores) == 1)
				{
					flagHarcodeo = 1;
					printf("\nSE HAN DADO DE ALTA LOS JUGADORES HARCODEADOS.\n");
				}
			break;

			case 6:
				opcionSalir = funcionContinuar("\nDESEA SALIR DEL PROGRAMA? (s/n): ", "ERROR. ");

				if(opcionSalir == 1)
				{
					printf("\nSE HA SALIDO DEL PROGRAMA.");
				}
			break;
		}

	}while(opcionSalir != 1);

	return 0;
}
