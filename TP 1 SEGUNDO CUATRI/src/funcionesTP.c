#include "funcionesTP.h"

/// @brief Recibe tres punteros a entero como parametro por referencia. Reservan direcciones de memoria que
/// almacenan los distintos costos que se piden.
/// @param primerCosto
/// @param segundoCosto
/// @param tercerCosto
/// @return Retorna 1 si salio bien, de lo contrario retorna -1.
int ingresarCostos(int* primerCosto, int* segundoCosto, int* tercerCosto)
{
	int rtn = -1;
	int opcionCostos;
	int flagHospedaje = 0, flagComida = 0, flagTransporte = 0;

	if(primerCosto != NULL && segundoCosto != NULL && tercerCosto != NULL)
	{
		printf("\n+--------------------------------------+\n"
				"|    INGRESO COSTOS DE MANTENIMIENTO   |\n"
				"+--------------------------------------+\n"
				"|1-COSTO HOSPEDAJE                     |\n"
				"|2-COSTO COMIDA                        |\n"
				"|3-COSTO TRANSPORTE                    |\n"
				"+--------------------------------------+\n\n");
		utn_getNumero("INGRESE QUE COSTO DESEA INGRESAR: ", "ERROR. ", 1, 3, 3, &opcionCostos);

		switch(opcionCostos)
		{
			case 1:
				if(flagHospedaje == 0 && *primerCosto == 0)
				{
					utn_getNumero("\nINGRESE COSTO HOSPEDAJE: ", "ERROR. ", 1, 99999, 3, primerCosto);
					flagHospedaje = 1;
				}
				else
				{
					printf("NO ES POSIBLE INGRESAR MAS DE UNA VEZ EL COSTO DE HOSPEDAJE.\n");
				}
			break;

			case 2:
				if(flagComida == 0 && *segundoCosto == 0)
				{
					utn_getNumero("\nINGRESE COSTO DE COMIDA: ", "ERROR. ", 1, 99999, 3, segundoCosto);
					flagComida = 1;
				}
				else
				{
					printf("NO ES POSIBLE INGRESAR MAS DE UNA VEZ EL COSTO DE COMIDA.\n");
				}
			break;

			case 3:
				if(flagTransporte == 0 && *tercerCosto == 0)
				{
					utn_getNumero("\nINGRESE COSTO DE TRANSPORTE: ", "ERROR. ", 1, 99999, 3, tercerCosto);
					flagTransporte = 1;
				}
				else
				{
					printf("NO ES POSIBLE INGRESAR MAS DE UNA VEZ EL COSTO DE TRANSPORTE.\n");
				}
			break;
		}

		if(*primerCosto > 0 && *segundoCosto > 0 && *tercerCosto > 0)
		{
			rtn = 1;
		}
	}

	return rtn;
}

/// @brief Pide que se ingrese un entero. Depende el ingresado, se sabe a cual confederacion se eligio.
/// @param primerContador
/// @param segundoCotador
/// @param tercerContador
/// @param cuartoContador
/// @param quintoContador
/// @param sextoContador
/// @return Retorna 1 si salio bien, sino -1.
int ingresarConfederacion(int* primerContador, int* segundoCotador, int* tercerContador, int* cuartoContador, int* quintoContador, int* sextoContador)
{
	int confederacionElegida;
	int rtn = -1;

	if(utn_getNumero("INGRESE CONFEDERACION (1. AFC | 2. CAF | 3. CONCACAF | 4. CONMEBOL | 5. UEFA | 6. OFC): ", "ERROR. ", 1, 6, 3, &confederacionElegida) == 0)
	{
		switch(confederacionElegida)
		{
			case 1:
				(*primerContador)++;
			break;

			case 2:
				(*segundoCotador)++;
			break;

			case 3:
				(*tercerContador)++;
			break;

			case 4:
				(*cuartoContador)++;
			break;

			case 5:
				(*quintoContador)++;
			break;

			case 6:
				(*sextoContador)++;
			break;
		}

		rtn = 1;
	}
	return rtn;
}

/// @brief Pide que se ingrese un entero, depende cual se determina una posicion a guardar.
/// @param contadorArqueros
/// @param contadorDefensores
/// @param contadorMediocampistas
/// @param contadorDelanteros
/// @return Retorna distintos enteros positivos si salio bien, de lo contrario -1.
int ingresarPosicion(int* contadorArqueros, int* contadorDefensores, int* contadorMediocampistas, int* contadorDelanteros)
{
	int posicion;
	int rtn = -1;

	if(utn_getNumero("\nINGRESE POSICION (1. ARQUEROS | 2. DEFENSORES | 3. MEDIOCAMPISTAS | 4. DELANTEROS): ", "ERROR. ", 1, 4, 3, &posicion) == 0)
	{
		switch(posicion)
		{
			case 1:
				if(*contadorArqueros < 2)
				{
					(*contadorArqueros)++;
					rtn = 1;
				}
				else
				{
					printf("\nERROR. NO SE ADMITEN MAS DE 2 ARQUEROS. \n");
				}
			break;

			case 2:
				if(*contadorDefensores < 8)
				{
					(*contadorDefensores)++;
					rtn = 2;
				}
				else
				{
					printf("\nERROR. NO SE ADMITEN MAS DE 8 DEFENSORES. \n");
				}
			break;

			case 3:
				if(*contadorMediocampistas < 8)
				{
					(*contadorMediocampistas)++;
					rtn = 3;
				}
				else
				{
					printf("\nERROR. NO SE ADMITEN MAS DE 8 MEDIOCAMPISTAS. \n");
				}
			break;

			case 4:
				if(*contadorDelanteros < 4)
				{
					(*contadorDelanteros)++;
					rtn = 4;
				}
				else
				{
					printf("\nERROR. NO SE ADMITEN MAS DE 4 DELANTEROS. \n");
				}
			break;
		}
	}
	return rtn;
}

/// @brief Recibe como parametros tres enteros y los suma, guardando el resultado en un puntero a entero pasado por referencia.
/// @param primerCosto
/// @param segundoCosto
/// @param tercerCosto
/// @param costoMantenimiento
/// @return Retorna 1 si salio bien, de lo contrario retorna 0.
int calcularCostoMantenimiento(int primerCosto, int segundoCosto, int tercerCosto, int* costoMantenimiento)
{
	int rtn = -1;

	if(primerCosto > 0 && segundoCosto > 0 && tercerCosto > 0)
	{
		*costoMantenimiento = primerCosto + segundoCosto + tercerCosto;
		rtn = 1;
	}

	return rtn;
}

/// @brief Recibe como parametros un entero y 6 flotantes para luego imprimirlos en un cierto formato. Tambien valida si cierto flotante es mayor
/// que los demas, para sumarle a ese un incremento.
/// @param costoMantenimiento
/// @param promedioAfc
/// @param promedioCaf
/// @param promedioConcacaf
/// @param promedioConmebol
/// @param promedioUefa
/// @param promedioOfc
void imprimirCalculos(int costoMantenimiento, float promedioAfc, float promedioCaf, float promedioConcacaf, float promedioConmebol, float promedioUefa, float promedioOfc)
{
	float incremento;
	float CostoIncrementado;

	printf("\n\t\tINFORMAR TODOS LOS RESULTADOS\n"
			"Porcentaje Uefa: %.2f\n"
			"Porcentaje Conmebol: %.2f\n"
			"Porcentaje Concacaf: %.2f\n"
			"Porcentaje Afc: %.2f\n"
			"Porcentaje Ofc: %.2f\n"
			"Porcentaje Caf: %.2f\n", promedioUefa, promedioConmebol, promedioConcacaf, promedioAfc, promedioOfc, promedioCaf);

	if( (promedioUefa > promedioCaf) && (promedioUefa > promedioAfc) && (promedioUefa > promedioConmebol) &&
		(promedioUefa > promedioConcacaf) && (promedioUefa > promedioOfc) )
	{
		incremento = (costoMantenimiento*35) / 100;
		CostoIncrementado = costoMantenimiento + incremento;
		printf("\nEL COSTO DE MANTENIMIENTO ERA DE %d Y RECIBIO UN AUMENTO DE %.2f, SU NUEVO VALOR ES DE %.2f\n", costoMantenimiento, incremento, CostoIncrementado);
	}
	else
	{
		printf("\nEL COSTO DE MANTENIMIENTO ES DE %d\n", costoMantenimiento);
	}
}
