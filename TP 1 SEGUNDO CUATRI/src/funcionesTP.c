#include "funcionesTP.h"

//PROTOTIPO ESTATICAS

static int ingresarConfederacion(void);
static int ingresarPosicion(int contadorArqueros, int contadorDefensores, int contadorMediocampistas, int contadorDelanteros);

//DESARROLLO FUNCIONES
/// @brief Recibe tres punteros a entero como parametro por referencia. Reservan direcciones de memoria que
/// almacenan los distintos costos que se piden.
/// @param primerCosto
/// @param segundoCosto
/// @param tercerCosto
/// @return Retorna 1 si salio bien, de lo contrario retorna 0.
int ingresarCostos(int* primerCosto, int* segundoCosto, int* tercerCosto)
{
	int rtn = 0;
	int opcionCostos;

	int costoUno = 0;
	int costoDos = 0;
	int costoTres = 0;

	int flagHospedaje = 0;
	int flagComida = 0;
	int flagTransporte = 0;

	if(primerCosto != NULL && segundoCosto != NULL && tercerCosto != NULL)
	{
		do
		{
			printf("\n+--------------------------------------+\n"
					"|    INGRESO COSTOS DE MANTENIMIENTO   |\n"
					"+--------------------------------------+\n"
					"|1-COSTO HOSPEDAJE ->             $%4d|\n"
					"|2-COSTO COMIDA ->                $%4d|\n"
					"|3-COSTO TRANSPORTE -> $          $%4d|\n"
					"|4-VOLVER AL MENU PRINCIPAL.           |\n"
					"+--------------------------------------+\n\n", costoUno, costoDos, costoTres);
			utn_getNumero("-INGRESE QUE COSTO DESEA INGRESAR: ", "ERROR. ", 1, 4, 3, &opcionCostos);

			switch(opcionCostos)
			{
				case 1:
					if(flagHospedaje == 0)
					{
						utn_getNumero("(A) INGRESE COSTO HOSPEDAJE: ", "ERROR. ", 1, 99999, 3, &costoUno);
						flagHospedaje = 1;
					}
					else
					{
						printf("NO ES POSIBLE INGRESAR MAS DE UNA VEZ LOS COSTOS.\n");
					}
				break;

				case 2:
					if(flagComida == 0)
					{
						utn_getNumero("(B) INGRESE COSTO DE COMIDA: ", "ERROR. ", 1, 99999, 3, &costoDos);
						flagComida = 1;
					}
					else
					{
						printf("NO ES POSIBLE INGRESAR MAS DE UNA VEZ LOS COSTOS.\n");
					}
				break;

				case 3:
					if(flagTransporte == 0)
					{
						utn_getNumero("(C) INGRESE COSTO DE TRANSPORTE: ", "ERROR. ", 1, 99999, 3, &costoTres);
						flagTransporte = 1;
					}
					else
					{
						printf("NO ES POSIBLE INGRESAR MAS DE UNA VEZ LOS COSTOS.\n");
					}
				break;
			}
		}while(opcionCostos != 4);

		*primerCosto = costoUno;
		*segundoCosto = costoDos;
		*tercerCosto = costoTres;

		rtn = 1;
	}

	return rtn;
}

/// @brief Pide que se ingrese un entero. Depende el ingresado, con un macro se sabe a cual confederacion pertenece.
/// @return Retorna la confederacion que se ingreso.
static int ingresarConfederacion(void)
{
	int confederacion;
	utn_getNumero("INGRESE CONFEDERACION: (1-AFC | 2-CAF | 3-CONCACAF | 4-CONMEBOL | 5-UEFA | 6-OFC): ", "ERROR. ", 1, 6, 3, &confederacion);

	switch(confederacion)
	{
		case 1:
			confederacion = AFC;
		break;

		case 2:
			confederacion = CAF;
		break;

		case 3:
			confederacion = CONCACAF;
		break;

		case 4:
			confederacion = CONMEBOL;
		break;

		case 5:
			confederacion = UEFA;
		break;

		case 6:
			confederacion = OFC;
		break;
	}

	return confederacion;
}

/// @brief Pide que se ingrese un entero. Depende el ingresado, con un macro se sabe cual posicion guardar.
/// @param contadorArqueros
/// @param contadorDefensores
/// @param contadorMediocampistas
/// @param contadorDelanteros
/// @return Retorna la posicion elegida.
static int ingresarPosicion(int contadorArqueros, int contadorDefensores, int contadorMediocampistas, int contadorDelanteros)
{
	int posicion;

	printf("\nCARGA DE JUGADORES\n"
			"------------------\n"
			"1. ARQUEROS -> %d\n"
			"2. DEFENSORES -> %d\n"
			"3. MEDIOCAMPISTAS -> %d\n"
			"4. DELANTEROS -> %d\n\n", contadorArqueros, contadorDefensores, contadorMediocampistas, contadorDelanteros);
	utn_getNumero("INGRESE POSICION: ", "ERROR. ", 1, 4, 3, &posicion);

	switch(posicion)
	{
		case 1:
			posicion = ARQUEROS;
		break;

		case 2:
			posicion = DEFENSORES;
		break;

		case 3:
			posicion = MEDIOCAMPISTAS;
		break;

		case 4:
			posicion = DELANTEROS;
		break;
	}

	return posicion;
}

/// @brief Recibe punteros a entero como parametro por referencia. Estos almacenan en una direccion de memoria a la que apuntan,
/// la cantidad de veces que se ingreso a x conferencia, para luego poder sacar los promedios por confederacion. Tambien pide los
/// datos de los jugadores poniendo cierto limite en cada posicion.
/// @param contadorUno
/// @param contadorDos
/// @param contadorTres
/// @param contadorCuatro
/// @param contadorCinco
/// @param contadorSeis
/// @return Retorna 1 si salio bien, de lo contrario retorna 0.
int menuIngresoJugadores(int* contadorUno, int* contadorDos, int* contadorTres, int* contadorCuatro, int* contadorCinco, int* contadorSeis)
{
	int rtn = 0;
	int posicion;
	int numeroCamiseta;
	int confederacion;
	int contadorArqueros = 0;
	int contadorDefensores = 0;
	int contadorMediocampistas = 0;
	int contadorDelanteros = 0;
	int contadorAfc = 0;
	int contadorCaf = 0;
	int contadorConcacaf = 0;
	int contadorConmebol = 0;
	int contadorUefa = 0;
	int contadorOfc = 0;
	int respuesta;

	if(contadorUno != NULL && contadorDos != NULL && contadorTres != NULL && contadorCuatro != NULL && contadorCinco && contadorSeis != NULL)
	{
		do
		{
			posicion = ingresarPosicion(contadorArqueros, contadorDefensores, contadorMediocampistas, contadorDelanteros);

			switch(posicion)
			{
				case ARQUEROS:
					if(contadorArqueros < 2)
					{
						contadorArqueros++;
						utn_getNumero("INGRESE NUMERO DE CAMISETA: ", "ERROR. ", 1, 99, 3, &numeroCamiseta);
						confederacion = ingresarConfederacion();
					}
					else
					{
						printf("\nERROR. NO SE ADMITEN MAS DE 2 ARQUEROS. \n");
					}
				break;

				case DEFENSORES:
					if(contadorDefensores < 8)
					{
						contadorDefensores++;
						utn_getNumero("INGRESE NUMERO DE CAMISETA: ", "ERROR. ", 1, 99, 3, &numeroCamiseta);
						confederacion = ingresarConfederacion();
					}
					else
					{
						printf("\nERROR. NO SE ADMITEN MAS DE 8 DEFENSORES. \n");
					}
				break;

				case MEDIOCAMPISTAS:
					if(contadorMediocampistas < 8)
					{
						contadorMediocampistas++;
						utn_getNumero("INGRESE NUMERO DE CAMISETA: ", "ERROR. ", 1, 99, 3, &numeroCamiseta);
						confederacion = ingresarConfederacion();
					}
					else
					{
						printf("\nERROR. NO SE ADMITEN MAS DE 8 MEDIOCAMPISTAS. \n");
					}
				break;

				case DELANTEROS:
					if(contadorDelanteros < 4)
					{
						contadorDelanteros++;
						utn_getNumero("INGRESE NUMERO DE CAMISETA: ", "ERROR. ", 1, 99, 3, &numeroCamiseta);
						confederacion = ingresarConfederacion();
					}
					else
					{
						printf("\nERROR. NO SE ADMITEN MAS DE 4 DELANTEROS. \n");
					}
				break;
			}

			switch(confederacion)
			{
				case AFC:
					contadorAfc++;
				break;

				case CAF:
					contadorCaf++;
				break;

				case CONCACAF:
					contadorConcacaf++;
				break;

				case CONMEBOL:
					contadorConmebol++;
				break;

				case UEFA:
					contadorUefa++;
				break;

				case OFC:
					contadorOfc++;
				break;
			}

			utn_getNumero("\nDESEA SEGUIR INGRESANDO JUGADORES? (1.SI | 2.NO): ", "ERROR. ", 1, 2, 3, &respuesta);
		}while(respuesta != 2);

		*contadorUno = contadorAfc;
		*contadorDos = contadorCaf;
		*contadorTres = contadorConcacaf;
		*contadorCuatro = contadorConmebol;
		*contadorCinco = contadorUefa;
		*contadorSeis = contadorOfc;
		rtn = 1;
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
	int rtn = 0;

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
