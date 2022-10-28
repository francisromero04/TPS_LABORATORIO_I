#include "jugador.h"

/// @brief Incrementa un entero el cual se usa para establecer un unico ID.
/// @return Retorna ese mismo entero (ID).
int eJugador_getID(void)
{
	static int idIncremental = 1005;
	static int rtn;

	rtn = idIncremental++;

	return rtn;
}

/// @brief Recibe una lista y su len, la recorre e inicializa cada posicion
/// como "LIBRE" para luego establecer un ALTA y asi no pisar datos.
/// @param lista
/// @param TAM
void eJugador_inicializarlista(eJugador lista[], int TAM)
{
	int i;

	if (lista != NULL && TAM > 0)
	{
		for (i = 0; i < TAM; i++)
		{
			lista[i].isEmpty = LIBRE;
		}
	}
}

/// @brief Recibe una lista y su len, la recorre y busca posiciones libres
/// para luego establecer un ALTA y asi no pisar datos.
/// @param lista
/// @param TAM
/// @return Retorna el indice "LIBRE" encontrado.
int eJugador_obtenerIndexLibre(eJugador lista[], int TAM)
{
	int rtn = -1;
	int i;

	if (lista != NULL && TAM > 0)
	{
		for (i = 0; i < TAM; i++)
		{
			if (lista[i].isEmpty == LIBRE)
			{
				rtn = i;
				break;
			}
		}
	}
	return rtn;
}

/// @brief Pide los datos necesarios para guardarlos en un auxiliar y luego retornarlos.
/// @return Retorna el auxiliar con los datos cargados
eJugador eJugador_ingresarDatos(void)
{
	eJugador auxiliar;

	puts("");
	utn_getNombreCompleto(auxiliar.nombre);
	utn_getString("INGRESE LA POSICION DEL JUGADOR: ", "ERROR. ", 3, TAM_CHAR, auxiliar.posicion);
	utn_getNumero("INGRESE NUMERO DE CAMISETA: ", "ERROR. ", 1, 200, 3, &auxiliar.numeroCamiseta);
	utn_getNumero("INGRESE LOS AÑOS DE CONTRATO (menos de 30): ", "ERROR. ", 1, 30, 3, &auxiliar.aniosContrato);
	utn_getNumFloat("INGRESE EL SALARIO DEL JUGADOR: ", "ERROR. ", 1, 999999, 3, &auxiliar.salario);

	return auxiliar;
}

/// @brief Recibe una lista, su len y un ID. Recorre esa lista, buscando posiciones en estado
/// "OCUPADO" y que coincida el ID recibido como parametro. Si encuentra uno,
/// devuelve el indice donde se encuentra ese ID.
/// @param lista
/// @param TAM
/// @param ID
/// @return Retorna el indice donde se encuentra el ID.
int eJugador_buscarPorID(eJugador lista[], int TAM, int ID)
{
	int rtn = -1;
	int i;

	if (lista != NULL && TAM > 0)
	{
		for (i = 0; i < TAM; i++)
		{
			if (lista[i].idJugador == ID && lista[i].isEmpty == OCUPADO)
			{
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

/// @brief Recibe una lista, su len y dos flotantes. Recorre la lista buscando posiciones en estado "OCUPADO",
///  si las hay, el contador se incrementa debido a cuantas existen y el acumulador suma los salarios.
/// Luego se realiza el calculo del promedio el cual se guarda en el flotante pasado por referencia.
/// @param lista
/// @param TAM
/// @param saldoAcumulado
/// @param saldoPromedio
/// @return Retorna 1 si sale bien.
int eJugador_calcularSaldoPromedio(eJugador lista[], int TAM, float* saldoAcumulado, float* saldoPromedio)
{
	int rtn = -1;
	int contadorJugadores = 0;
	float acumuladorSalario = 0;

	if (lista != NULL && TAM > 0)
	{
		for (int i = 0; i < TAM; i++)
		{
			if(lista[i].isEmpty == OCUPADO)
			{
				contadorJugadores++;
				acumuladorSalario += lista[i].salario;
			}
		}

		*saldoAcumulado = acumuladorSalario;
		*saldoPromedio = acumuladorSalario / contadorJugadores;

		rtn = 1;
	}

	return rtn;
}

/// @brief Recibe una lista, su len y un flotantes. Recorre la lista buscando posiciones en estado "OCUPADO",
///  si las hay, cuenta cuantos jugadores superan el promedio de los salarios.
/// @param lista
/// @param TAM
/// @param saldoPromedio
/// @return Retorna cuantos jugadores superan ese promedio.
int eJugador_verificarSalario(eJugador lista[], int TAM, float saldoPromedio)
{
	int rtn = -1;
	int jugadoresMayorSaldo = 0;

	if (lista != NULL && TAM > 0)
	{
		for (int i = 0; i < TAM; i++)
		{
			if(lista[i].isEmpty == OCUPADO)
			{
				if(lista[i].salario > saldoPromedio)
				{
					jugadoresMayorSaldo++;
				}
			}
		}
		rtn = jugadoresMayorSaldo;
	}

	return rtn;
}

/// @brief Recibe el total acumulado de los salarios, el salario promedio y
/// la cantidad de jugadores que lo superan, para luego mostrarlos.
/// @param saldoAcumulado
/// @param saldoPromedio
/// @param jugadoresMayorSaldo
void eJugador_ImprimirSaldoPromedio(float saldoAcumulado, float saldoPromedio, int jugadoresMayorSaldo)
{
	printf("\nLA SUMATORIA TOTAL DE LOS SALARIOS ES DE: $%.2f, MIENTRAS QUE SU PROMEDIO ES DE: $%.2f.", saldoAcumulado, saldoPromedio);
	printf("\nLA CANTIDAD DE JUGADORES CON UN SALDO MAYOR A ESTE PROMEDIO ES DE: %d.\n", jugadoresMayorSaldo);
}

/// @brief Recibe una lista y su len. Recorre la lista buscando posiciones en estado "OCUPADO",
///  si las hay, ordena por doble criterio.
/// @param lista
/// @param TAM
/// @return Retorna 0 o 1 dependiendo el criterio
int eJugador_sort(eJugador lista[], int TAM)
{
	int rtn = -1;
	int i;
	int j;
	eJugador aux;

	if (lista != NULL && TAM > 0)
	{
		for (i = 0; i < TAM - 1; i++)
		{
			for (j = i + 1; j < TAM; j++)
			{
				if (lista[i].isEmpty == OCUPADO && lista[j].isEmpty == OCUPADO)
				{
					if(stricmp(lista[i].fk_nombreConfederacion, lista[j].fk_nombreConfederacion) < 0)
					{
						aux = lista[i];
						lista[i] = lista[j];
						lista[j] = aux;
						rtn = 0; // RETORNA 0 SI SE ORDENA POR NOMBRE DE CONFEDERACION
					}
					else
					{
						if(stricmp(lista[i].fk_nombreConfederacion, lista[j].fk_nombreConfederacion) == 0)
						{
							if(stricmp(lista[i].nombre, lista[j].nombre) < 0)
							{
								aux = lista[i];
								lista[i] = lista[j];
								lista[j] = aux;
								rtn = 1; //RETORNA 1 SI SE ORDENA POR NOMBRE DE JUGADOR
							}
						}
					}
				}
			}
		}
	}

	return rtn;
}

/// @brief Recibe una lista y su len. Recorre la lista buscando posiciones en estado "OCUPADO",
///  si las hay, ordena por ID.
/// @param lista
/// @param TAM
/// @return Retorna 1 si salio bien.
int eJugador_sortPorID(eJugador lista[], int TAM)
{
	int rtn = -1;
	int i;
	int j;
	eJugador aux;

	if (lista != NULL && TAM > 0)
	{
		for (i = 0; i < TAM - 1; i++)
		{
			for (j = i + 1; j < TAM; j++)
			{
				if (lista[i].isEmpty == OCUPADO && lista[j].isEmpty == OCUPADO)
				{
					if(lista[i].idJugador > lista[j].idJugador)
					{
						aux = lista[i];
						lista[i] = lista[j];
						lista[j] = aux;
						rtn = 1;
					}
				}
			}
		}
	}

	return rtn;
}

/// @brief Recibe una lista y carga datos en distintos indices de la lista.
/// @param lista
/// @return Retorna 1 si salio bien.
int eJugador_harcodeo(eJugador lista[])
{
	int rtn = -1;

	if(lista != NULL)
	{
		lista[0].idJugador = 1000;
		lista[0].isEmpty = OCUPADO;
		lista[0].aniosContrato = 4;
		lista[0].numeroCamiseta = 10;
		lista[0].salario = 1500000;
		lista[0].fk_idConfederacion = 100;
		strcpy(lista[0].nombre, "Lionel Messi");
		strcpy(lista[0].posicion, "Delantero");

		lista[1].idJugador = 1001;
		lista[1].isEmpty = OCUPADO;
		lista[1].aniosContrato = 5;
		lista[1].numeroCamiseta = 3;
		lista[1].salario = 8000000;
		lista[1].fk_idConfederacion = 100;
		strcpy(lista[1].nombre, "Marcos Rojo");
		strcpy(lista[1].posicion, "Defensor");

		lista[2].idJugador = 1002;
		lista[2].isEmpty = OCUPADO;
		lista[2].aniosContrato = 6;
		lista[2].numeroCamiseta = 9;
		lista[2].salario = 6000000;
		lista[2].fk_idConfederacion = 100;
		strcpy(lista[2].nombre, "Leandro Paredes");
		strcpy(lista[2].posicion, "Mediocampista");

		lista[3].idJugador = 1003;
		lista[3].isEmpty = OCUPADO;
		lista[3].aniosContrato = 3;
		lista[3].numeroCamiseta = 7;
		lista[3].salario = 1100000;
		lista[3].fk_idConfederacion = 101;
		strcpy(lista[3].nombre, "Kylian Mbappe");
		strcpy(lista[3].posicion, "Delantero");

		lista[4].idJugador = 1004;
		lista[4].isEmpty = OCUPADO;
		lista[4].aniosContrato = 8;
		lista[4].numeroCamiseta = 5;
		lista[4].salario = 7000000;
		lista[4].fk_idConfederacion = 101;
		strcpy(lista[4].nombre, "Marco Verratti");
		strcpy(lista[4].posicion, "Mediocampista");

		rtn = 1;
	}

	return rtn;
}
