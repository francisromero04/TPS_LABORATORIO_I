#include "confederacion.h"

/// @brief Incrementa un entero el cual se usa para establecer un unico ID.
/// @return Retorna ese mismo entero (ID).
int eConfederacion_getID(void)
{
	static int idIncremental = 105;
	static int rtn;

	rtn = idIncremental++;

	return rtn;
}

/// @brief Recibe una lista y su len, la recorre e inicializa cada posicion
/// como "LIBRE" para luego establecer un ALTA y asi no pisar datos.
/// @param lista
/// @param TAM
void eConfederacion_inicializarlista(eConfederacion lista[], int TAM)
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
int eConfederacion_obtenerIndexLibre(eConfederacion lista[], int TAM)
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
eConfederacion eConfederacion_ingresarDatos(void)
{
	eConfederacion auxiliar;

	puts("");
	utn_getString("INGRESE NOMBRE DE LA CONFEDERACION: ", "ERROR. ", 3, TAM_CHAR, auxiliar.nombre);
	utn_getString("INGRESE REGION DE LA CONFEDERACION: ", "ERROR. ", 3, TAM_CHAR, auxiliar.region);
	utn_getNumero("INGRESE EL AÑO DE CREACION: ", "ERROR. ", 1900, 2022, 3, &auxiliar.anioCreacion);

	return auxiliar;
}

/// @brief Recibe una lista, su len y un ID. Recorre esa lista, buscando posiciones en estado
/// "OCUPADO" y que coincida el ID recibido como parametro. Si encuentra uno,
/// devuelve el indice donde se encuentra ese ID.
/// @param lista
/// @param TAM
/// @param ID
/// @return Retorna el indice donde se encuentra el ID.
int eConfederacion_buscarPorID(eConfederacion lista[], int TAM, int ID)
{
	int rtn = -1;
	int i;

	if (lista != NULL && TAM > 0)
	{
		for (i = 0; i < TAM; i++)
		{
			if (lista[i].idConfederacion == ID && lista[i].isEmpty == OCUPADO)
			{
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

/// @brief Pide los datos necesarios para guardarlos en un auxiliar y luego retornarlos.
/// @return Retorna el auxiliar con los datos cargados.
eConfederacion eConfederacion_ingresarUna(eConfederacion lista[], int TAM)
{
	eConfederacion auxiliar;

	eConfederacion_imprimirTodos(lista, TAM);
	utn_getNumero("\nINGRESE ID DE SU CONFEDERACION: ", "ERROR. ", 100, 105, 3, &auxiliar.idConfederacion);

	return auxiliar;
}

/// @brief Imprime los datos cargados de una posicion.
/// @param confederacion
void eConfederacion_imprimirUno(eConfederacion confederacion)
{
	printf("|%-4d|%-16s|%-22s|%-12d|\n", confederacion.idConfederacion, confederacion.nombre, confederacion.region, confederacion.anioCreacion);
}

/// @brief Recibe una lista y su len, pregunta si tiene posiciones en estado "OCUPADO",
/// si las tiene imprime los datos almacenados en esas posiciones.
/// @param lista
/// @param TAM
/// @return Retorna 1 si imprimio al menos uno.
int eConfederacion_imprimirTodos(eConfederacion lista[], int TAM)
{
	int i;
	int rtn = 0;
	int cantidad = 0;

	if (lista != NULL && TAM > 0)
	{
		puts("\n\t\t LISTA DE CONFEDERACIONES");
		puts("+---------------------------------------------------------+");
		puts("| ID |     NOMBRE     |        REGION        |AÑO CREACION|");
		puts("+---------------------------------------------------------+");

		for (i = 0; i < TAM; i++)
		{
			if (lista[i].isEmpty == OCUPADO)
			{
				eConfederacion_imprimirUno(lista[i]);
				puts("+---------------------------------------------------------+");
				cantidad++;
			}
		}
	}

	if (cantidad > 0)
	{
		rtn = 1;
	}

	return rtn;
}

/// @brief Abre un submenu para modificar datos de cierta posicion.
/// @param confederacion
/// @return Retorna un auxiliar con los datos modificados
eConfederacion eConfederacion_modificarUno(eConfederacion confederacion)
{
	int opcionMenuModificar;

	do
	{
		puts("\nCAMPOS A MODIFICAR:");
		puts("1. NOMBRE");
		puts("2. REGION");
		puts("3. AÑO DE CREACION");
		puts("4. GUARDAR CAMBIOS\n");

		utn_getNumero("INGRESE LA OPCION DEL CAMPO A MODIFICAR: ", "ERROR. ", 1, 7, 1, &opcionMenuModificar);

		switch(opcionMenuModificar)
		{
			case 1:
				if(utn_getString("INGRESE NOMBRE DE LA CONFEDERACION: ", "ERROR. ", 3, TAM_CHAR, confederacion.nombre))
				{
					puts("EL NOMBRE DE LA CONFEDERACION SE HA MODIFICADO.");
				}
			break;

			case 2:
				if(utn_getString("INGRESE REGION DE LA CONFEDERACION: ", "ERROR. ", 3, TAM_CHAR, confederacion.region))
				{
					puts("LA REGION SE HA MODIFICADO.");
				}
			break;

			case 3:
				if(utn_getNumero("INGRESE EL AÑO DE CREACION: ", "ERROR. ", 1900, 2022, 3, &confederacion.anioCreacion))
				{
					puts("EL AÑO DE CREACION SE HA MODIFICADO.");
				}
			break;

			case 4:
				puts("\nDATOS MODIFICADOS CORRECTAMENTE, CAMBIOS GUARDADOS.");
			break;
		}
	}while(opcionMenuModificar != 4);

	return confederacion;
}

/// @brief Recibe una lista y su len. Recorre la lista buscando posiciones en estado "OCUPADO",
///  si las hay, ordena por ID.
/// @param lista
/// @param TAM
/// @return Retorna 1 si salio bien.
int eConfederacion_sortPorID(eConfederacion lista[], int TAM)
{
	int rtn = -1;
	int i;
	int j;
	eConfederacion aux;

	if (lista != NULL && TAM > 0)
	{
		for (i = 0; i < TAM - 1; i++)
		{
			for (j = i + 1; j < TAM; j++)
			{
				if (lista[i].isEmpty == OCUPADO && lista[j].isEmpty == OCUPADO)
				{
					if(lista[i].idConfederacion > lista[j].idConfederacion)
					{
						aux = lista[i];
						lista[i] = lista[j];
						lista[j] = aux;
						rtn = 1; // RETORNA 0 SI SE ORDENA POR NOMBRE DE CONFEDERACION
					}
				}
			}
		}
	}

	return rtn;
}

//-----------------------------------------------------ABM---------------------------------------------------------------

/// @brief Recibe una lista y su len, busca un indice "LIBRE" para realizar un ALTA.
/// Pide los datos a guardar y le da un ID unico a cada posicion, cambiando su estado a "OCUPADO".
/// @param lista
/// @param TAM
/// @return Retorna el indice donde se almacenaron los datos.
int eConfederacion_alta(eConfederacion lista[], int TAM)
{
	int rtn = -1;
	eConfederacion auxjugador;
	int index = eConfederacion_obtenerIndexLibre(lista, TAM);

	///SI INDEX == -1 LISTA LLENA
	///SI INDEX != -1 TENGO POSICIONES LIBRES

	if (index != -1)
	{
		auxjugador = eConfederacion_ingresarDatos();
		auxjugador.idConfederacion = eConfederacion_getID();
		auxjugador.isEmpty = OCUPADO;
		lista[index] = auxjugador;
		rtn = index;
	}

	if(rtn != -1)
	{
		puts("\nSE HA DADO DE ALTA UNA CONFEDERACION.");
	}

	return rtn;
}

/// @brief Recibe una lista y su len. Imprime un listado con las ALTAS realizadas y
/// luego pide un ID para cambiar su estado a BAJA.
/// @param lista
/// @param TAM
/// @return Retorna 1 salio bien
int eConfederacion_baja(eConfederacion lista[], int TAM)
{
	int rtn = 0;
	int idProducto;
	int index;
	int flag = 0;

	if(eConfederacion_imprimirTodos(lista, TAM))
	{
		flag = 1;
	}

	if(flag)
	{
		utn_getNumero("\nINGRESE ID DEL PRODUCTO A DAR DE BAJA: ", "ERROR. ", 100, 1000, 3, &idProducto);

		while (eConfederacion_buscarPorID(lista, TAM, idProducto) == -1)
		{
			puts("\nNO EXISTE ID.");
			utn_getNumero("\nINGRESE ID DEL PRODUCTO A DAR DE BAJA: ", "ERROR. ", 100, 1000, 3, &idProducto);
		}

		index = eConfederacion_buscarPorID(lista, TAM, idProducto);
		lista[index].isEmpty = BAJA;
	}

	if(rtn == 1)
	{
		puts("\nSE HA DADO DE BAJA UNA CONFEDERACION.");
	}

	return rtn;
}

/// @brief Recibe una lista y su len. Imprime un listado con las ALTAS realizadas y
/// luego pide un ID para modificar.
/// @param array
/// @param TAM
/// @return @return Retorna 1 si se pudo modificar el campo requerido o -1 si hubo algun error
int eConfederacion_modificar(eConfederacion lista[], int TAM)
{
	int rtn = 0;
	int idPasajero;
	int index;
	int flag = 0;
	eConfederacion auxiliar;

	if(eConfederacion_imprimirTodos(lista, TAM))
	{
		flag = 1;
	}

	if(flag)
	{
		utn_getNumero("\nINGRESE ID DEL jugador A MODIFICAR: ", "ERROR. ", 100, 1000, 3, &idPasajero);

		while(eConfederacion_buscarPorID(lista, TAM, idPasajero) == -1)
		{
			puts("NO EXISTE ID.");
			utn_getNumero("\nREINGRESE ID DEL jugador A MODIFICAR: ", "ERROR. ", 100, 1000, 3, &idPasajero);
		}

		index = eConfederacion_buscarPorID(lista, TAM, idPasajero);
		auxiliar = eConfederacion_modificarUno(lista[index]);
		lista[index] = auxiliar;
		rtn = 1;
	}

	return rtn;
}

/// @brief Recibe una lista y carga datos en distintos indices de la lista.
/// @param lista
/// @return Retorna 1 si salio bien.
int eConfederacion_harcodeo(eConfederacion lista[])
{
	int rtn = -1;

	if(lista != NULL)
	{
		lista[0].idConfederacion = 100;
		lista[0].anioCreacion = 1916;
		lista[0].isEmpty = OCUPADO;
		strcpy(lista[0].nombre, "CONMEBOL");
		strcpy(lista[0].region, "SUDAMERICA");

		lista[1].idConfederacion = 101;
		lista[1].anioCreacion = 1954;
		lista[1].isEmpty = OCUPADO;
		strcpy(lista[1].nombre, "UEFA");
		strcpy(lista[1].region, "EUROPA");

		lista[2].idConfederacion = 102;
		lista[2].anioCreacion = 1954;
		lista[2].isEmpty = OCUPADO;
		strcpy(lista[2].nombre, "AFC");
		strcpy(lista[2].region, "ASIA");

		lista[3].idConfederacion = 103;
		lista[3].anioCreacion = 1957;
		lista[3].isEmpty = OCUPADO;
		strcpy(lista[3].nombre, "CAF");
		strcpy(lista[3].region, "AFRICA");

		lista[4].idConfederacion = 104;
		lista[4].anioCreacion = 1962;
		lista[4].isEmpty = OCUPADO;
		strcpy(lista[4].nombre, "CONCACAF");
		strcpy(lista[4].region, "NORTE Y CENTRO AMERICA");

		lista[5].idConfederacion = 105;
		lista[5].anioCreacion = 1966;
		lista[5].isEmpty = OCUPADO;
		strcpy(lista[5].nombre, "OFC");
		strcpy(lista[5].region, "OCEANIA");

		rtn = 1;
	}

	return rtn;
}
