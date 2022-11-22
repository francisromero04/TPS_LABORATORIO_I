#include "nexo.h"

/// @brief Recibe una lista y su len, busca un indice "LIBRE" para realizar un ALTA.
/// Pide los datos a guardar y le da un ID unico a cada posicion, cambiando su estado a "OCUPADO".
/// @param listaJugadores
/// @param TAM_JUGADORES
/// @param listaConfed
/// @param TAM_CONFED
/// @return Retorna el indice donde se almacenaron los datos.
int nexo_alta(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConf[], int TAM_CONF)
{
	int rtn = -1;
	int indexJugador;
	eJugador auxJugador;
	eConfederacion auxConfederacion;

	if(listaJugadores != NULL && TAM_JUGADORES > 0 && listaConf != NULL && TAM_CONF > 0)
	{
		indexJugador = eJugador_obtenerIndexLibre(listaJugadores, TAM_JUGADORES);

		///SI INDEX == -1 LISTA LLENA
		///SI INDEX != -1 TENGO POSICIONES LIBRES

		if (indexJugador != -1)
		{
			auxJugador = eJugador_ingresarDatos();
			auxConfederacion = eConfederacion_ingresarUna(listaConf, TAM_CONF);
			auxJugador.idJugador = eJugador_getID();
			auxJugador.fk_idConfederacion = auxConfederacion.idConfederacion;
			auxJugador.isEmpty = OCUPADO;
			listaJugadores[indexJugador] = auxJugador;
			rtn = indexJugador;
		}
	}

	if(rtn != -1)
	{
		puts("\nSE HA DADO DE ALTA UN JUGADOR.");
	}

	return rtn;
}

/// @brief Recibe una lista y su len. Imprime un listado con las ALTAS realizadas y
/// luego pide un ID para cambiar su estado a BAJA.
/// @param lista
/// @param TAM
/// @return Retorna 1 salio bien
int nexo_baja(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConf[], int TAM_CONF)
{
	int rtn = -1;
	int idProducto;
	int index;
	int flag = 0;

	if(listaJugadores != NULL && TAM_JUGADORES > 0 && listaConf != NULL && TAM_CONF > 0)
	{
		eJugador_sortPorID(listaJugadores, TAM_JUGADORES);

		if(nexo_listarTodos(listaJugadores, TAM_JUGADORES, listaConf, TAM_CONF))
		{
			flag = 1;
		}

		if(flag)
		{
			utn_getNumero("\nINGRESE ID DEL JUGADOR A DAR DE BAJA: ", "ERROR. ", 1000, 9999, 3, &idProducto);

			while (eJugador_buscarPorID(listaJugadores, TAM_JUGADORES, idProducto) == -1)
			{
				puts("\nNO EXISTE ID.");
				utn_getNumero("\nINGRESE ID DEL PRODUCTO A DAR DE BAJA: ", "ERROR. ", 100, 1000, 3, &idProducto);
			}

			index = eJugador_buscarPorID(listaJugadores, TAM_JUGADORES, idProducto);
			listaJugadores[index].isEmpty = BAJA;
			rtn = 1;
		}
	}

	if(rtn == 1)
	{
		puts("\nSE HA DADO DE BAJA EL JUGADOR.");
	}

	return rtn;
}

/// @brief Abre un submenu para modificar datos de cierta posicion.
/// @param jugador
/// @param lista
/// @param TAM_CONFED
/// @return Retorna un auxiliar con los datos modificados
eJugador nexo_modificarUno(eJugador jugador, eConfederacion lista[], int TAM_CONFED)
{
	int opcionMenuModificar, flagIngreso = -1;
	eConfederacion auxConfederacion;

	do
	{
		puts("\nCAMPOS A MODIFICAR:");
		puts("1. NOMBRE");
		puts("2. POSICION");
		puts("3. NUMERO CAMISETA");
		puts("4. CONFEDERACION");
		puts("5. SALARIO");
		puts("6. AÑOS DE CONTRATO");
		puts("7. GUARDAR CAMBIOS\n");

		utn_getNumero("INGRESE LA OPCION DEL CAMPO A MODIFICAR: ", "ERROR. ", 1, 7, 1, &opcionMenuModificar);

		switch(opcionMenuModificar)
		{
			case 1:
				if(	utn_getNombreCompleto(jugador.nombre))
				{
					puts("EL NOMBRE DEL JUGADOR SE HA MODIFICADO.");
				}
			break;

			case 2:
				utn_getString("INGRESE LA POSICION DEL JUGADOR: ", "ERROR. ", 3, TAM_CHAR, jugador.posicion);

				if(stricmp(jugador.posicion, "arquero") == 0 || stricmp(jugador.posicion, "defensor") == 0 ||
				   stricmp(jugador.posicion, "mediocampista") == 0 || stricmp(jugador.posicion, "delantero") == 0)
				{
					flagIngreso = 1;
				}
				else if(flagIngreso == -1)
				{
					while(stricmp(jugador.posicion, "arquero") != 0 || stricmp(jugador.posicion, "defensor") != 0 ||
						  stricmp(jugador.posicion, "mediocampista") != 0 || stricmp(jugador.posicion, "delantero") != 0)
					{
						printf("ERROR, SOLO PUEDE INGRESAR ARQUERO, DEFENSOR, MEDIOCAMPISTA O DELANTERO.\n");
						utn_getString("REINGRESE LA POSICION CORRECTA DEL JUGADOR: ", "ERROR. ", 3, TAM_CHAR, jugador.posicion);

						if(stricmp(jugador.posicion, "arquero") == 0 || stricmp(jugador.posicion, "defensor") == 0 ||
						   stricmp(jugador.posicion, "mediocampista") == 0 || stricmp(jugador.posicion, "delantero") == 0)
						{
							flagIngreso = 1;
							break;
						}
					}
				}

				if(flagIngreso == 1)
				{
					puts("LA POSICION DEL JUGADOR SE HA MODIFICADO.");
				}
			break;

			case 3:
				if(utn_getNumero("INGRESE NUMERO DE CAMISETA (MENOR DE 30): ", "ERROR. ", 1, 30, 3, &jugador.numeroCamiseta))
				{
					puts("EL NUMERO DE CAMISETA DEL JUGADOR SE HA MODIFICADO.");
				}
			break;

			case 4:
				auxConfederacion = eConfederacion_ingresarUna(lista, TAM_CONFED);
				jugador.fk_idConfederacion = auxConfederacion.idConfederacion;
				puts("LA CONFEDERACION EN LA QUE JUEGA SE HA MODIFICADO.");

			break;

			case 5:
				if(utn_getNumFloat("INGRESE EL SALARIO DEL JUGADOR: ", "ERROR. ", 1, 999999, 3, &jugador.salario))
				{
					puts("EL SALARIO DEL JUGADOR SE HA MODIFICADO.");
				}
			break;

			case 6:
				if(utn_getNumero("INGRESE LOS AÑOS DE CONTRATO (MENOS DE 30): ", "ERROR. ", 1, 30, 3, &jugador.aniosContrato))
				{
					puts("LOS AÑOS DE CONTRATO DEL JUGADOR SE HAN MODIFICADO.");
				}
			break;
		}
	}while(opcionMenuModificar != 7);

	return jugador;
}

/// @brief Recibe una lista y su len. Imprime un listado con las ALTAS realizadas y
/// luego pide un ID para modificar.
/// @param array
/// @param TAM
/// @return @return Retorna 1 si se pudo modificar el campo requerido o -1 si hubo algun error
int nexo_modificacion(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConf[], int TAM_CONF)
{
	int rtn = -1;
	int idJugador;
	int index;
	int flag = 0;
	eJugador auxiliar;

	if(listaJugadores != NULL && TAM_JUGADORES > 0 && listaConf != NULL && TAM_CONF > 0)
	{
		eJugador_sortPorID(listaJugadores, TAM_JUGADORES);

		if(nexo_listarTodos(listaJugadores, TAM_JUGADORES, listaConf, TAM_CONF))
		{
			flag = 1;
		}

		if(flag)
		{
			utn_getNumero("\nINGRESE ID DEL JUGADOR A MODIFICAR: ", "ERROR. ", 1000, 9999, 3, &idJugador);

			while(eJugador_buscarPorID(listaJugadores, TAM_JUGADORES, idJugador) == -1)
			{
				puts("NO EXISTE ID.");
				utn_getNumero("\nREINGRESE ID DEL JUGADOR A MODIFICAR: ", "ERROR. ", 1000, 9999, 3, &idJugador);
			}

			index = eJugador_buscarPorID(listaJugadores, TAM_JUGADORES, idJugador);
			auxiliar = nexo_modificarUno(listaJugadores[index], listaConf, TAM_CONF);
			listaJugadores[index] = auxiliar;
			rtn = 1;
		}
	}

	if(rtn == 1)
	{
		puts("\nDATOS MODIFICADOS CORRECTAMENTE, CAMBIOS GUARDADOS.");
	}

	return rtn;
}

/// @brief Recibe una lista y su len. Recorre la lista buscando posiciones en estado "OCUPADO",
///  si las hay, ordena por doble criterio.
/// @param lista
/// @param TAM
/// @return Retorna 0 o 1 dependiendo el criterio
int nexo_sortPorNombre(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED)
{
	int rtn = -1;
	eJugador aux;

	if (listaJugadores != NULL && TAM_JUGADORES > 0)
	{
		for (int i = 0; i < TAM_JUGADORES - 1; i++)
		{
			for (int j = i + 1; j < TAM_JUGADORES; j++)
			{
				if (listaJugadores[i].isEmpty == OCUPADO && listaJugadores[j].isEmpty == OCUPADO)
				{
					if(stricmp(listaConfed[i].nombre, listaConfed[j].nombre) < 0)
					{
						if(stricmp(listaJugadores[i].nombre, listaJugadores[j].nombre) < 0)
						{
							aux = listaJugadores[i];
							listaJugadores[i] = listaJugadores[j];
							listaJugadores[j] = aux;
							rtn = 0;
						}
					}
				}
			}
		}
	}

	return rtn;
}

/// @brief Imprime los datos cargados de una posicion.
/// @param confederacion
void nexo_listarUno(eJugador jugador, eConfederacion confederacion)
{
	printf("|%4d|%-20s|%-15s|%-11d|%-9.1f|%-13d|%-15s|\n", jugador.idJugador, jugador.nombre, jugador.posicion, jugador.numeroCamiseta, jugador.salario, jugador.aniosContrato, confederacion.nombre);
}

/// @brief Recibe una lista y su len, pregunta si tiene posiciones en estado "OCUPADO",
/// si las tiene imprime los datos almacenados en esas posiciones.
/// @param lista
/// @param TAM
/// @return Retorna 1 si imprimio al menos uno.
int nexo_listarTodos(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED)
{
	int i;
	int rtn = 0;
	int cantidad = 0;
	int idConfederacion;
	int indexId;

	if (listaJugadores != NULL && TAM_JUGADORES > 0 && listaConfed != NULL && TAM_CONFED > 0)
	{
		puts("\n\t\t\t\t LISTA DE JUGADORES");
		puts("+---------------------------------------------------------------------------------------------+");
		puts("| ID |       NOMBRE       |   POSICION    |Nº CAMISETA| SALARIO |AÑOS CONTRATO| CONFEDERACION |");
		puts("+---------------------------------------------------------------------------------------------+");

		for (i = 0; i < TAM_JUGADORES; i++)
		{
			if (listaJugadores[i].isEmpty == OCUPADO)
			{
				idConfederacion = listaJugadores[i].fk_idConfederacion;
				indexId = eConfederacion_buscarPorID(listaConfed, TAM_CONFED, idConfederacion);
				nexo_listarUno(listaJugadores[i], listaConfed[indexId]);
				puts("+---------------------------------------------------------------------------------------------+");
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

int averiguarNombreConfederacion(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED, char* nombreConfed)
{
	int rtn = -1;
	int idConfederacion;
	int indexId;

	if (listaJugadores != NULL && TAM_JUGADORES > 0 && listaConfed != NULL && TAM_CONFED > 0)
	{
		for (int i = 0; i < TAM_JUGADORES - 1; i++)
		{
			for (int j = i + 1; j < TAM_JUGADORES; j++)
			{
				if (listaJugadores[i].isEmpty == OCUPADO)
				{
					idConfederacion = listaJugadores[i].fk_idConfederacion;
					indexId = eConfederacion_buscarPorID(listaConfed, TAM_CONFED, idConfederacion);
					strcpy(nombreConfed, listaConfed[indexId].nombre);
				}
			}
		}
	}

	return rtn;
}

/// @brief Imprime los datos cargados de una posicion.
/// @param confederacion
void nexo_listarUnaConfederacionConJugador(eJugador jugador, eConfederacion confederacion)
{
	printf("|%4d|%-8s|%-22s|%-12d|%-16s|\n", confederacion.idConfederacion, confederacion.nombre, confederacion.region, confederacion.anioCreacion, jugador.nombre);
}

/// @brief Recibe una lista y su len, pregunta si tiene posiciones en estado "OCUPADO",
/// si las tiene imprime los datos almacenados en esas posiciones.
/// @param lista
/// @param TAM
/// @return Retorna 1 si imprimio al menos uno.
int nexo_listarConfederacionesConJugadores(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED)
{
	int rtn = 0;
	int cantidad = 0;

	if (listaJugadores != NULL && TAM_JUGADORES > 0 && listaConfed != NULL && TAM_CONFED > 0)
	{
		puts("\n\t\t\tLISTA DE CONFEDERACIONES");
		puts("+------------------------------------------------------------------+");
		puts("| ID | NOMBRE |        REGION        |AÑO CREACION| NOMBRE JUGADOR |");
		puts("+------------------------------------------------------------------+");

		for (int i = 0; i < TAM_JUGADORES; i++)
		{
			for (int j = 0; j < TAM_CONFED; j++)
			{
				if (listaJugadores[i].isEmpty == OCUPADO)
				{
					if(listaConfed[j].idConfederacion == listaJugadores[i].fk_idConfederacion)
					{
						eConfederacion_sortPorID(listaConfed, TAM_CONFED);
						nexo_listarUnaConfederacionConJugador(listaJugadores[i], listaConfed[j]);
						puts("+------------------------------------------------------------------+");
						cantidad++;
					}
				}
			}
		}
	}

	if (cantidad > 0)
	{
		rtn = 1;
	}

	return rtn;
}

/// @brief Recibe dos listas y sus len, recorre las listas buscando posiciones en estado "OCUPADO",
///  si las hay, el acumulador suma enteros. Luego busca el entero mas grande y muestra a que indice pertenece.
/// @param listaJugadores
/// @param TAM_JUGADORES
/// @param listaConfed
/// @param TAM_CONFED
/// @return Retorna 1 si salio bien.
int nexo_calcularContratoMasLargo(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED)
{
	int rtn = -1;
	int mayor = 0;
	int acumulador;
	int index = -1;

	if (listaJugadores != NULL && TAM_JUGADORES > 0 && listaConfed != NULL && TAM_CONFED > 0)
	{
		for (int i = 0; i < TAM_CONFED; i++)
		{
			acumulador = 0;

			for (int j = 0; j < TAM_JUGADORES; j++)
			{
				if(listaJugadores[j].isEmpty == OCUPADO)
				{
					if(listaConfed[i].idConfederacion == listaJugadores[j].fk_idConfederacion)
					{
						acumulador += listaJugadores[j].aniosContrato;
					}
				}
			}

			if(acumulador > mayor)
			{
				index = i;
				mayor = acumulador;
			}
			else
			{
				if(acumulador > 0 && acumulador == mayor)
				{
					rtn = 1;
				}
			}
		}
		printf("\nLA CONFEDERACION CON MAS AÑOS DE CONTRATO ES %s CON %d\n", listaConfed[index].nombre, mayor);
	}

	return rtn;
}

/// @brief Recibe dos listas y sus len, recorre las listas buscando posiciones en estado "OCUPADO",
///  si las hay, el contador incrementa debido a las confederaciones. Luego calcula un promedio para
/// cada confederacion y los imprime
/// @param listaJugadores
/// @param TAM_JUGADORES
/// @param listaConfed
/// @param TAM_CONFED
/// @return Retorna 1 si salio bien.
int nexo_calcularPromedios(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED)
{
	int rtn = -1;
	int idConfederacion;
	int indexId;
	int cantidadJugadores = 0;
	int cantidad[6];
	float promedios[6];

	if (listaJugadores != NULL && TAM_JUGADORES > 0 && listaConfed != NULL && TAM_CONFED > 0)
	{
		for(int i = 0; i < 6; i++)
		{
			cantidad[i] = 0;
		}

		for (int i = 0; i < TAM_JUGADORES; i++)
		{
			if (listaJugadores[i].isEmpty == OCUPADO)
			{
				cantidadJugadores++;
				idConfederacion = listaJugadores[i].fk_idConfederacion;
				indexId = eConfederacion_buscarPorID(listaConfed, TAM_CONFED, idConfederacion);

				if(listaJugadores[i].fk_idConfederacion == listaConfed[indexId].idConfederacion)
				{
					switch(listaJugadores[i].fk_idConfederacion)
					{
						case 100:
							cantidad[0]++;
						break;

						case 101:
							cantidad[1]++;
						break;

						case 102:
							cantidad[2]++;
						break;

						case 103:
							cantidad[3]++;
						break;

						case 104:
							cantidad[4]++;
						break;

						case 105:
							cantidad[5]++;
						break;
					}
				}
			}
		}

		promedios[0] = (float)cantidad[0] *100 / cantidadJugadores;
		promedios[1] = (float)cantidad[1] *100 /cantidadJugadores;
		promedios[2] = (float)cantidad[2] *100 /cantidadJugadores;
		promedios[3] = (float)cantidad[3] *100 /cantidadJugadores;
		promedios[4] = (float)cantidad[4] *100 /cantidadJugadores;
		promedios[5] = (float)cantidad[5] *100 /cantidadJugadores;

		printf("\nCANTIDAD TOTAL DE JUGADORES: %d\n", cantidadJugadores);
		printf("\nPORCENTAJE CONMEBOL: %.2f", promedios[0]);
		printf("\nPORCENTAJE UEFA: %.2f", promedios[1]);
		printf("\nPORCENTAJE AFC: %.2f", promedios[2]);
		printf("\nPORCENTAJE CAF: %.2f", promedios[3]);
		printf("\nPORCENTAJE CONCACAF: %.2f", promedios[4]);
		printf("\nPORCENTAJE OFC: %.2f\n", promedios[5]);

		rtn = 1;
	}

	return rtn;
}

/// @brief Recibe dos listas y sus len, pregunta si tienen posiciones en estado "OCUPADO",
/// si las tiene imprime los datos almacenados en esas posiciones.
/// @param lista
/// @param TAM
/// @return Retorna 1 si imprimio al menos uno.
int nexo_listarJugadorPorConfederacion(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED, char confederacion[])
{
	int i;
	int rtn = 0;
	int cantidad = 0;
	int idConfederacion;
	int indexId;

	if (listaJugadores != NULL && TAM_JUGADORES > 0 && listaConfed != NULL && TAM_CONFED > 0)
		{
			puts("\n\t\t\t\t LISTA DE JUGADORES");
			puts("+---------------------------------------------------------------------------------------------+");
			puts("| ID |       NOMBRE       |   POSICION    |Nº CAMISETA| SALARIO |AÑOS CONTRATO| CONFEDERACION |");
			puts("+---------------------------------------------------------------------------------------------+");

			for (i = 0; i < TAM_JUGADORES; i++)
			{
				if (listaJugadores[i].isEmpty == OCUPADO)
				{
					idConfederacion = listaJugadores[i].fk_idConfederacion;
					indexId = eConfederacion_buscarPorID(listaConfed, TAM_CONFED, idConfederacion);

					if(stricmp(listaConfed[indexId].nombre, confederacion) == 0)
					{
						nexo_listarUno(listaJugadores[i], listaConfed[indexId]);
						puts("+---------------------------------------------------------------------------------------------+");
						cantidad++;
					}
				}
			}
		}

		if (cantidad > 0)
		{
			rtn = 1;
		}

	return rtn;
}

/// @brief Recibe dos listas y sus len, recorre las listas buscando posiciones en estado "OCUPADO",
///  si las hay, el contador se incrementa. Busca el indice donde se encuentra la region con mas jugadores y los muestra.
/// @param listaJugadores
/// @param TAM_JUGADORES
/// @param listaConfed
/// @param TAM_CONFED
/// @return Retorna 1 si encuentra la region
int nexo_listarRegionConMasJugadores(eJugador listaJugadores[], int TAM_JUGADORES, eConfederacion listaConfed[], int TAM_CONFED)
{
	int rtn = -1;
	int mayor = 0;
	int contador;
	int index = -1;
	char confederacion[TAM_CHAR];

	if (listaJugadores != NULL && TAM_JUGADORES > 0 && listaConfed != NULL && TAM_CONFED > 0)
	{
		for (int i = 0; i < TAM_CONFED; i++)
		{
			contador = 0;

			for (int j = 0; j < TAM_JUGADORES; j++)
			{
				if(listaJugadores[j].isEmpty == OCUPADO)
				{
					if(listaConfed[i].idConfederacion == listaJugadores[j].fk_idConfederacion)
					{
						contador++;
					}
				}
			}

			if(contador > mayor)
			{
				index = i;
				mayor = contador;
			}
			else
			{
				if(contador > 0 && contador == mayor)
				{
					rtn = 1;
				}
			}
		}

		printf("\nLA REGION CON MAS JUGADORES ES %s CON %d\n", listaConfed[index].region, mayor);
		strcpy(confederacion,listaConfed[index].nombre);
		nexo_listarJugadorPorConfederacion(listaJugadores, TAM_JUGADORES, listaConfed, TAM_CONFED, confederacion);
	}

	return rtn;
}
