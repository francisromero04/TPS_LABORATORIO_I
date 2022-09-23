#include <stdio.h>
#include <stdlib.h>
#include "funcionesTP.h"

//TP 1 Francis Romero (Division D)

int main(void)
{
	setbuf(stdout, NULL);

	int opcion;

	int flagOpcionUno = 0;
	int flagOpcionDos = 0;
	int flagOpcionTres = 0;

	int costoHospedaje = 0;
	int costoComida = 0;
	int costoTransporte = 0;
	int costoMantenimiento;

	int contadorAfc;
	int contadorCaf;
	int contadorConcacaf;
	int contadorConmebol;
	int contadorUefa;
	int contadorOfc;

	float promedioAfc = 0;
	float promedioCaf = 0;
	float promedioConcacaf = 0;
	float promedioConmebol = 0;
	float promedioUefa = 0;
	float promedioOfc = 0;

	do
	{
		printf("\n+======================================+\n");
		printf("|------------MENU PRINCIPAL------------|\n");
		printf("|======================================|\n");
		printf("|1. INGRESO DE COSTOS DE MANTENIMIENTO |\n");
		printf("|2. CARGA DE JUGADORES                 |\n");
		printf("|3. REALIZAR TODOS LOS CALCULOS        |\n");
		printf("|4. INFORMAR TODOS LOS RESULTADOS      |\n");
		printf("|5. SALIR                              |\n");
		printf("+======================================+\n\n");

		utn_getNumero("INGRESE OPCION: ", "ERROR. ", 1, 5, 3, &opcion);

		switch(opcion)
		{
			case 1:
				if(flagOpcionUno == 0)
				{
					if(ingresarCostos(&costoHospedaje, &costoComida, &costoTransporte) == 1)
					{
						flagOpcionUno = 1;
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
						menuIngresoJugadores(&contadorAfc, &contadorCaf, &contadorConcacaf, &contadorConmebol, &contadorUefa, &contadorOfc);

						flagOpcionDos = 1;
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
						promedioAfc = contadorAfc*100 / 22;
						promedioCaf = contadorCaf*100 / 22;
						promedioConcacaf = contadorConcacaf*100 / 22;
						promedioConmebol = contadorConmebol*100 /22;
						promedioUefa = contadorUefa*100 /22;
						promedioOfc = contadorOfc*100 / 22;

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
					if(flagOpcionUno == 1 && flagOpcionTres == 1)
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
