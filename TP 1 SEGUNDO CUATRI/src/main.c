#include <stdio.h>
#include <stdlib.h>
#include "funcionesTP.h"

//TP 1 Francis Romero (Division D)

int main(void)
{
	setbuf(stdout, NULL);

	int opcion, posicion, numeroCamiseta, respuesta, totalJugadores;
	int flagOpcionUno = 0, flagOpcionDos = 0, flagOpcionTres = 0;
	int costoHospedaje = 0, costoComida = 0, costoTransporte = 0, costoMantenimiento;
	int contadorArqueros = 0, contadorDefensas = 0, contadorMediocampos = 0, contadorDelanteros = 0;
	int contadorAfc = 0, contadorCaf = 0, contadorConcacaf = 0, contadorConmebol = 0, contadorUefa = 0, contadorOfc = 0;
	float promedioAfc, promedioCaf, promedioConcacaf, promedioConmebol, promedioUefa, promedioOfc;

	do
	{
		printf("\n+======================================+\n");
		printf("|------------MENU PRINCIPAL------------|\n");
		printf("|======================================|\n");
		printf("|1. INGRESO DE COSTOS DE MANTENIMIENTO |\n");
		printf("|   Costo de Hospedaje ->%5d         |\n", costoHospedaje);
		printf("|   Costo de Comida ->%5d            |\n", costoComida);
		printf("|   Costo de Transporte ->%5d        |\n", costoTransporte);
		printf("|2. CARGA DE JUGADORES                 |\n");
		printf("|   Arqueros ->%5d                   |\n", contadorArqueros);
		printf("|   Defensores ->%5d                 |\n", contadorDefensas);
		printf("|   Mediocampistas ->%5d             |\n", contadorMediocampos);
		printf("|   Delanteros ->%5d                 |\n", contadorDelanteros);
		printf("|3. REALIZAR TODOS LOS CALCULOS        |\n");
		printf("|4. INFORMAR TODOS LOS RESULTADOS      |\n");
		printf("|5. SALIR                              |\n");
		printf("+======================================+\n\n");

		utn_getNumero("INGRESE OPCION: ", "ERROR. ", 1, 5, 3, &opcion);

		switch(opcion)
		{
			case 1:
				if(flagOpcionUno == 0 || flagOpcionUno == 2)
				{
					if(ingresarCostos(&costoHospedaje, &costoComida, &costoTransporte) == 1)
					{
						flagOpcionUno = 1;
					}
					else
					{
						flagOpcionUno = 2;
					}
				}
				else
				{
					printf("\nNO ES POSIBLE INGRESAR MAS DE UNA VEZ LOS COSTOS.\n\n");
				}
			break;

			case 2:
				if(flagOpcionUno == 1)
				{
					if(flagOpcionDos == 0)
					{
						do
						{
							posicion = ingresarPosicion(&contadorArqueros, &contadorDefensas, &contadorMediocampos, &contadorDelanteros);

							if(posicion == 1 || posicion == 2 || posicion == 3 || posicion == 4)
							{
								ingresarConfederacion(&contadorAfc, &contadorCaf, &contadorConcacaf, &contadorConmebol, &contadorUefa, &contadorOfc);
								utn_getNumero("INGRESE NUMERO DE CAMISETA (menor de 30): ", "ERROR. ", 1, 30, 3, &numeroCamiseta);
								respuesta = funcionContinuar("\nDESEA CONTINUAR INGRESANDO JUGADORES? (S / N): ", "ERROR. ");
								flagOpcionDos = 1;
							}
						}while(respuesta != 0);
					}
					else
					{
						printf("\nNO ES POSIBLE INGRESAR MAS DE UNA VEZ LOS JUGADORES.\n\n");
					}
				}
				else
				{
					printf("\nNO ES POSIBLE CARGAR JUGADORES SIN HABER CARGADO PRIMERO LOS COSTOS.\n\n");
				}
			break;

			case 3:
				if(flagOpcionUno == 1 && flagOpcionDos == 1)
				{
					if(flagOpcionTres == 0)
					{
						totalJugadores = contadorArqueros + contadorDefensas + contadorMediocampos + contadorDelanteros;
						promedioAfc = (float) contadorAfc / totalJugadores;
						promedioCaf = (float) contadorCaf / totalJugadores;
						promedioConcacaf = (float) contadorConcacaf / totalJugadores;
						promedioConmebol = (float) contadorConmebol / totalJugadores;
						promedioUefa = (float) contadorUefa / totalJugadores;
						promedioOfc = (float) contadorOfc / totalJugadores;

						calcularCostoMantenimiento(costoHospedaje, costoComida, costoTransporte, &costoMantenimiento);
						printf("\nSE HAN CALCULADO LOS RESULTADOS.\n");
						flagOpcionTres = 1;
					}
					else
					{
						printf("\nNO ES POSIBLE REALIZAR LOS CALCULOS 2 VECES.\n\n");
					}
				}
				else
				{
					printf("\nNO ES POSIBLE REALIZAR LOS CALCULOS SIN HABER INGRESADO LOS COSTOS Y LOS JUGADORES.\n\n");
				}
			break;

			case 4:
				if(flagOpcionTres == 1)
				{
					if(flagOpcionUno == 1 && flagOpcionDos == 1)
					{
						imprimirCalculos(costoMantenimiento, promedioAfc, promedioCaf, promedioConcacaf, promedioConmebol, promedioUefa, promedioOfc);
					}
					else
					{
						printf("\nNO ES POSIBLE IMPRIMIR SIN HABER INGRESADO NINGUN DATO.\n\n");
					}
				}
				else
				{
					printf("\nNO ES POSIBLE IMPRIMIR SIN HABER CALCULADO ANTES.\n\n");
				}
			break;

			case 5:
				printf("\nPROGRAMA CERRADO.");
			break;
		}
	}while(opcion != 5);

	return 0;
}
