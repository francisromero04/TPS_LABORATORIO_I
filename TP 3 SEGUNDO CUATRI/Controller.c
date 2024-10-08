#include <stdio.h>
#include <stdlib.h>

#include "Jugador.h"
#include "Seleccion.h"
#include "LinkedList.h"
#include "parser.h"
#include "Controller.h"

/** \brief Carga los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_cargarJugadoresDesdeTexto(char* path , LinkedList* pArrayListJugador)
{
	int rtn = -1; //LL NULA O PATH NULO
	FILE* pFile = fopen(path, "r");

	if(pArrayListJugador != NULL && path != NULL)
	{
		if(parser_JugadorFromText(pFile, pArrayListJugador) == 1)
		{
			if(ll_len(pArrayListJugador) >= 1)
			{
				rtn = 1; //LEN MAYOR A 0
				printf("\nSE CARGO LA LISTA DE JUGADORES CORRECTAMENTE.");
			}
			else
			{
				rtn = 0; //LL VACIA
				printf("\nSE CARGO LA LISTA DE JUGADORES INCORRECTAMENTE.");
			}
		}
	}
	return rtn;
}

/** \brief Carga los datos de los selecciones desde el archivo selecciones.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_cargarSeleccionesDesdeTexto(char* path , LinkedList* pArrayListSeleccion)
{
	int rtn = -1; //LL NULA O PATH NULO
	FILE* pFile = fopen(path, "r");

	if(pArrayListSeleccion != NULL && path != NULL)
	{
		if(parser_SeleccionFromText(pFile, pArrayListSeleccion) == 1)
		{
			if(ll_len(pArrayListSeleccion) >= 1)
			{
				rtn = 1; //LEN MAYOR A 0
				printf("\nSE CARGO LA LISTA DE SELECCIONES CORRECTAMENTE. \n");
			}
			else
			{
				rtn = 0; //LL VACIA
				printf("\nSE CARGO LA LISTA DE SELECCIONES INCORRECTAMENTE. \n");
			}
		}
	}
	return rtn;
}

/** \brief Carga los datos de los jugadores desde el archivo generado en modo binario.
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_cargarJugadoresDesdeBinario(char* path , LinkedList* pArrayListJugador)
{
	int rtn = -1; //LL NULA O PATH NULO

	if(pArrayListJugador != NULL && path != NULL)
	{
		FILE* pFile = fopen(path, "rb");

		if(pFile != NULL)
		{
			if(parser_JugadorFromBinary(pFile , pArrayListJugador) == 1)
			{
				if(ll_len(pArrayListJugador) >= 1)
				{
					rtn = 1; //LEN MAYOR A 0
					printf("\nSE CARGO LA LISTA DE JUGADORES BINARIOS CORRECTAMENTE. \n");
				}
				else
				{
					rtn = 0; //LL VACIA
					printf("\nSE CARGO LA LISTA DE JUGADORES BINARIOS INCORRECTAMENTE. \n");
				}
			}
		}
	}

	return rtn;
}

/** \brief Alta de jugadores
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_agregarJugador(LinkedList* pArrayListJugador)
{
	int rtn = -1;
	int auxId;
	int auxEdad;
	int auxIdSeleccion = 0;
	char auxPosicion[TAM_CHAR];
	char auxNombreCompleto[TAM_CHAR];
	char auxNacionalidad[TAM_CHAR];
	eJugador* unJugador = NULL;

	if(pArrayListJugador != NULL)
	{
		if(utn_getNombreCompleto(auxNombreCompleto) == 1 && utn_getNumero("INGRESE SU EDAD (mayor que 18 y menor que 40):", "ERROR. ", 18, 40, 3, &auxEdad) == 0)
		{
			utn_getString("INGRESE POSICION (ARQUERO / DEFENSOR / MEDIOCAMPISTA / DELANTERO): ", "ERROR. ", 3, TAM_CHAR, auxPosicion);
			validarPosicion(auxPosicion);
			utn_getString("INGRESE NACIONALIDAD (SOLO SELECCIONES CLASIFICADAS AL MUNDIAL): ", "ERROR. ", 3, TAM_CHAR, auxNacionalidad);
			validarNacionalidad(auxNacionalidad);

			auxId = controller_generadorID();
			unJugador = jug_newParametrosAlta(auxId, auxNombreCompleto, auxEdad, auxPosicion, auxNacionalidad, auxIdSeleccion);

			if(unJugador != NULL)
			{
				controller_saveId(auxId);
				ll_add(pArrayListJugador, unJugador);
				rtn = 1;
			}
		}
	}

	return rtn;
}

/** \brief Modificar datos del jugador
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_editarJugador(LinkedList* pArrayListJugador)
{
	int i;
	int rtn = -1;
	int edad;
	char posicion[TAM_CHAR];
	char nombreCompleto[TAM_CHAR];
	char nacionalidad[TAM_CHAR];
	int idJugador, idAbuscar, opcionMenu, flagIngreso = -1;
	eJugador* this = NULL;

	if(pArrayListJugador != NULL)
	{
		controller_listarJugadores(pArrayListJugador);

		if(utn_getNumero("\nINGRESE EL ID DEL JUGADOR A MOFIDIFICAR: ", "\nERROR.", 1, 1000, 2, &idAbuscar) == 0)
		{
			for(i = 0; i < ll_len(pArrayListJugador); i++)
			{
				this = (eJugador*) ll_get(pArrayListJugador, i);
				jug_getId(this, &idJugador);

				if(idAbuscar == idJugador)
				{
					puts("\n\t\t\t\tLISTADO DE JUGADORES COMPLETA");
					puts("+-------------------------------------------------------------------------------------------------+");
					puts("| ID |     NOMBRE COMPLETO     | EDAD |        POSICION         |    NACIONALIDAD    |ID SELECCION|");
					puts("+-------------------------------------------------------------------------------------------------+");

					ll_get(pArrayListJugador, i);
					eJugador_imprimir(this);
					puts("+-------------------------------------------------------------------------------------------------+");

					if(utn_getNumero("\nCAMPOS A MODIFICAR: \n"
									"1. NOMBRE COMPLETO \n2. EDAD \n"
									"3. POSICION \n4. NACIONALIDAD \n"
									"\nINGRESE OPCION: ", "ERROR.", 1, 5, 2, &opcionMenu) == 0)
					{
						switch(opcionMenu)
						{
							case 1:
								if(utn_getNombreCompleto(nombreCompleto) == 1)
								{
									if(jug_setNombreCompleto(this, nombreCompleto) == 1)
									{
										puts("\nNOMBRE MODIFICADO. \n");
									}
								}
							break;

							case 2:
								if(utn_getNumero("INGRESE SU EDAD (mayor que 18 y menor que 40): ", "ERROR. ", 18, 40, 3, &edad) == 0)
								{
									if(jug_setEdad(this, edad) == 1)
									{
										puts("\nEDAD MODIFICADA. \n");
									}
								}
							break;

							case 3:
								utn_getString("INGRESE POSICION: ", "ERROR. ", 3, TAM_CHAR, posicion);
								validarPosicion(posicion);

								if(jug_setPosicion(this, posicion) == 1)
								{
									puts("\nPOSICION MODIFICADA. \n");
								}
							break;

							case 4:
								utn_getString("INGRESE NACIONALIDAD: ", "ERROR. ", 3, TAM_CHAR, nacionalidad);
								validarNacionalidad(nacionalidad);

								if(jug_setNacionalidad(this, nacionalidad) == 1)
								{
									puts("\nNACIONALIDAD MODIFICADA \n");
								}
							break;
						}
					}

					rtn = 1; //retorna 1 si pudo modificar
				}
			}
		}
	}

	if(rtn == 1)
	{
		printf("\nSE HA MODIFICADO CORRECTAMENTE \n");
	}
	else
	{
		rtn = 0;

		if(rtn == 0)
		{
			printf("\nID NO ENCONTRADO, REGRESARAS AL MENU PRINCIPAL. \n");
		}
	}

    return rtn;
}

/** \brief Baja del jugador
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 */
int controller_removerJugador(LinkedList* pArrayListJugador)
{
	int rtn = -1;
	int idJugador, idAbuscar;
	int opcionBaja;
	int indexABorrar;
	eJugador* this = NULL;

	if(pArrayListJugador != NULL)
	{
		controller_listarJugadores(pArrayListJugador);

		if(utn_getNumero("\nINGRESE EL ID DEL JUGADOR A DAR DE BAJA: ", "\nERROR.", 1, 1000, 2, &idAbuscar) == 0)
		{
			for(int i = 0; i < ll_len(pArrayListJugador); i++)
			{
				this = (eJugador*) ll_get(pArrayListJugador, i);
				jug_getId(this, &idJugador);

				if(idAbuscar == idJugador)
				{
					puts("\n\t\t\t\tLISTADO DE JUGADORES");
					puts("+-------------------------------------------------------------------------------------------------+");
					puts("| ID |     NOMBRE COMPLETO     | EDAD |        POSICION         |    NACIONALIDAD    |ID SELECCION|");
					puts("+-------------------------------------------------------------------------------------------------+");

					ll_get(pArrayListJugador, i);
					eJugador_imprimir(this);
					puts("+-------------------------------------------------------------------------------------------------+");

					opcionBaja = funcionContinuar("\nESTA SEGURO QUE QUIERE DAR DE BAJA ESTE JUGADOR? (s/n): ", "\nERROR.");
					indexABorrar = ll_indexOf(pArrayListJugador, this);

					if(opcionBaja == 1)
					{
						ll_remove(pArrayListJugador, indexABorrar);
						rtn = 1;
					}
				}
			}
		}
	}

	if(rtn == 1)
	{
		printf("\nSE HA DADO DE BAJA CORRECTAMENTE. \n");
	}
	else
	{
		rtn = 0;

		if(rtn == 0)
		{
			printf("\nID NO ENCONTRADO, REGRESARAS AL MENU PRINCIPAL. \n");
		}
	}

    return rtn;
}

/** \brief Listar jugadores
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_listarJugadores(LinkedList* pArrayListJugador)
{
	int rtn = -1;

	if(pArrayListJugador != NULL)
	{
		int lenList = ll_len(pArrayListJugador);

		puts("\n\t\t\t\tLISTADO DE JUGADORES COMPLETA");
		puts("+-------------------------------------------------------------------------------------------------+");
		puts("| ID |     NOMBRE COMPLETO     | EDAD |        POSICION         |    NACIONALIDAD    |  SELECCION |");
		puts("+-------------------------------------------------------------------------------------------------+");

		for(int i = 0; i < lenList; i++)
		{
			eJugador* pJugador = ll_get(pArrayListJugador, i);
			eJugador_imprimir(pJugador);
			puts("+-------------------------------------------------------------------------------------------------+");
		}

		rtn = 1;
	}

	return rtn;
}

int controller_listarJugadoresConvocados(LinkedList* pArrayListJugador)
{
	int rtn = -1, idSeleccion;
	eJugador* this = NULL;

	if(pArrayListJugador != NULL)
	{
		int lenList = ll_len(pArrayListJugador);

		puts("\n\t\t\t\tLISTADO DE JUGADORES CONVOCADOS");
		puts("+-------------------------------------------------------------------------------------------------+");
		puts("| ID |     NOMBRE COMPLETO     | EDAD |        POSICION         |    NACIONALIDAD    |  SELECCION |");
		puts("+-------------------------------------------------------------------------------------------------+");

		for(int i = 0; i < lenList; i++)
		{
			this = (eJugador*) ll_get(pArrayListJugador, i);
			jug_getIdSeleccion(this, &idSeleccion);

			if(idSeleccion >= 1 && idSeleccion <= 30)
			{
				eJugador_imprimir(this);
				puts("+-------------------------------------------------------------------------------------------------+");
				rtn = 1;
			}
		}
	}

	return rtn;
}

int controller_listarJugadoresNoConvocados(LinkedList* pArrayListJugador)
{
	int rtn = -1, idSeleccion;
	eJugador* this = NULL;

	if(pArrayListJugador != NULL)
	{
		int lenList = ll_len(pArrayListJugador);

		puts("\n\t\t\t\tLISTADO DE JUGADORES NO CONVOCADOS");
		puts("+-------------------------------------------------------------------------------------------------+");
		puts("| ID |     NOMBRE COMPLETO     | EDAD |        POSICION         |    NACIONALIDAD    |  SELECCION |");
		puts("+-------------------------------------------------------------------------------------------------+");

		for(int i = 0; i < lenList; i++)
		{
			this = (eJugador*) ll_get(pArrayListJugador, i);
			jug_getIdSeleccion(this, &idSeleccion);

			if(idSeleccion == 0)
			{
				eJugador_imprimir(this);
				puts("+-------------------------------------------------------------------------------------------------+");
				rtn = 1;
			}
		}
	}

	return rtn;
}

/** \brief Listar selecciones
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_listarSelecciones(LinkedList* pArrayListSeleccion)
{
	int rtn = -1;

	if(pArrayListSeleccion != NULL)
	{
		int lenList = ll_len(pArrayListSeleccion);

		puts("\n\t\tLISTADO DE SELECCIONES");
		puts("+--------------------------------------------------------+");
		puts("| ID |        PAIS        |  CONFEDERACION  | CONVOCADOS |");
		puts("+--------------------------------------------------------+");

		for(int i = 0; i < lenList; i++)
		{
			Seleccion* pSeleccion = ll_get(pArrayListSeleccion, i);
			selec_imprimir(pSeleccion);
			puts("+--------------------------------------------------------+");
		}

		rtn = 1;
	}

	return rtn;
}

/** \brief Ordenar jugadores
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_ordenarJugadores(LinkedList* pArrayListJugador, int criterio)
{
	int rtn = -1;
	LinkedList* auxiliarOrdenar;
	int len = ll_len(pArrayListJugador);
	int opcionOrden;

	/* 1 = menor a mayor
	 * 0 = mayor a menor
	 * -1 = como vino
	 */

	if(pArrayListJugador != NULL)
	{
		switch(criterio)
		{
			case 1:
				if(len > 0)
				{
					printf("\n 0 = MAYOR A MENOR | 1 = MENOR A MAYOR \n");;
					utn_getNumero("INGRESE QUE CRITERIO DE ORDENAMIENTO DESEA: ", "ERROR. ", 0, 1, 3, &opcionOrden);
					auxiliarOrdenar = ll_clone(pArrayListJugador);
					rtn = ll_sort(auxiliarOrdenar, jug_criterioNacionalidad, opcionOrden);
					controller_listarJugadores(auxiliarOrdenar);
					rtn = 1;
				}
			break;

			case 2:
				if(len > 0)
				{
					printf("\n 0 = MAYOR A MENOR | 1 = MENOR A MAYOR \n");;
					utn_getNumero("INGRESE QUE CRITERIO DE ORDENAMIENTO DESEA: ", "ERROR. ", 0, 1, 3, &opcionOrden);
					auxiliarOrdenar = ll_clone(pArrayListJugador);
					rtn = ll_sort(auxiliarOrdenar, jug_criterioEdad, opcionOrden);
					controller_listarJugadores(auxiliarOrdenar);
					rtn = 2;
				}
			break;

			case 3:
				if(len > 0)
				{
					printf("\n 0 = MAYOR A MENOR | 1 = MENOR A MAYOR \n");;
					utn_getNumero("INGRESE QUE CRITERIO DE ORDENAMIENTO DESEA: ", "ERROR. ", 0, 1, 3, &opcionOrden);
					auxiliarOrdenar = ll_clone(pArrayListJugador);
					rtn = ll_sort(auxiliarOrdenar, jug_criterioNombre, opcionOrden);
					controller_listarJugadores(auxiliarOrdenar);
					rtn = 3;
				}
			break;
		}
	}

	return rtn;
}

/** \brief Ordenar selecciones
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_ordenarSelecciones(LinkedList* pArrayListSeleccion)
{
	int rtn = -1;
	LinkedList* auxiliarOrdenar;
	int len = ll_len(pArrayListSeleccion);
	int opcionOrden;

	if(pArrayListSeleccion != NULL)
	{
		if(len > 0)
		{
			printf("\n 0 = MAYOR A MENOR | 1 = MENOR A MAYOR \n");;
			utn_getNumero("INGRESE QUE CRITERIO DE ORDENAMIENTO DESEA: ", "ERROR. ", 0, 1, 3, &opcionOrden);
			auxiliarOrdenar = ll_clone(pArrayListSeleccion);
			rtn = ll_sort(auxiliarOrdenar, selec_criterioConfederacion, opcionOrden);
			controller_listarSelecciones(auxiliarOrdenar);
			rtn = 1;
		}
		else
		{
			rtn = -2; //LL VACIA
		}
	}

	return rtn;
}

int controller_convocarJugador(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion)
{
	int rtn = -1;
	int idJugador, idSelecJug, idSeleccion, idJugAbuscar, idSelecAbuscar;
	eJugador* this = NULL;
	Seleccion* thisDos = NULL;
	int opcionContinuar;
	int convocados;

	if(pArrayListJugador != NULL && pArrayListSeleccion != NULL)
	{
		controller_listarJugadoresNoConvocados(pArrayListJugador);

		if(utn_getNumero("\nINGRESE EL ID DEL JUGADOR A CONVOCAR: ", "ERROR. ", 1, 1000, 3, &idJugAbuscar) == 0)
		{
			for(int i = 0; i < ll_len(pArrayListJugador); i++)
			{
				this = (eJugador*) ll_get(pArrayListJugador, i);

				jug_getId(this, &idJugador);
				jug_getIdSeleccion(this, &idSelecJug);

				if(idJugAbuscar == idJugador)
				{
					if(idSelecJug == 0)
					{
						puts("\n\t\t\t\tLISTADO DE JUGADORES");
						puts("+-------------------------------------------------------------------------------------------------+");
						puts("| ID |     NOMBRE COMPLETO     | EDAD |        POSICION         |    NACIONALIDAD    |ID SELECCION|");
						puts("+-------------------------------------------------------------------------------------------------+");

						ll_get(pArrayListJugador, i);
						eJugador_imprimir(this);
						puts("+-------------------------------------------------------------------------------------------------+");

						opcionContinuar = funcionContinuar("\nCONFIRME SI DESEA CONVOCAR A ESTE JUGADOR A LA SELECCION (s/n): ", "ERROR. ");

						if(opcionContinuar == 1)
						{
							controller_listarSelecciones(pArrayListSeleccion);
							utn_getNumero("\nINGRESE EL ID DE LA SELECCION LA CUAL CONVOCA AL JUGADOR: ", "ERROR. ", 1, 30, 3, &idSelecAbuscar);

							for(int j = 0; j < ll_len(pArrayListSeleccion); j++)
							{
								thisDos = (Seleccion*) ll_get(pArrayListSeleccion, j);
								selec_getId(thisDos, &idSeleccion);

								if(idSelecAbuscar == idSeleccion)
								{
									selec_getConvocados(thisDos, &convocados);

									if(convocados <= 22)
									{
										convocados++;
										selec_setConvocados(thisDos, convocados);
										jug_setIdSeleccion(this, idSeleccion);
										rtn = 1;
									}
								}
							}
						}
					}
					else
					{
						printf("\nNO ES POSIBLE CONVOCAR A UN JUGADOR DOS VECES, SE REGRESA AL MENU PRINCIPAL.\n");
						break;
					}
				}
			}
		}
	}

	return rtn;
}

int controller_quitarJugador(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion)
{
	int rtn = -1;
	int idJugador, idJugBaja;
	eJugador* this = NULL;
	Seleccion* thisDos = NULL;
	int opcionContinuar;
	int convocados;
	int idSelec, id;

	if(pArrayListJugador != NULL && pArrayListSeleccion != NULL)
	{
		controller_listarJugadoresConvocados(pArrayListJugador);

		if(utn_getNumero("\nINGRESE EL ID DEL JUGADOR A QUITAR: ", "ERROR. ", 1, 1000, 3, &idJugBaja) == 0)
		{
			for(int i = 0; i < ll_len(pArrayListJugador); i++)
			{
				this = (eJugador*) ll_get(pArrayListJugador, i);
				jug_getId(this, &idJugador);
				jug_getIdSeleccion(this, &idSelec);

				if(idJugBaja == idJugador)
				{
					if(idSelec >= 1 && idSelec <= 30)
					{
						puts("\n\t\t\t\tLISTADO DE JUGADORES");
						puts("+-------------------------------------------------------------------------------------------------+");
						puts("| ID |     NOMBRE COMPLETO     | EDAD |        POSICION         |    NACIONALIDAD    |ID SELECCION|");
						puts("+-------------------------------------------------------------------------------------------------+");

						ll_get(pArrayListJugador, i);
						eJugador_imprimir(this);
						puts("+-------------------------------------------------------------------------------------------------+");

						opcionContinuar = funcionContinuar("\nCONFIRME SI DESEA QUITAR A ESTE JUGADOR DE LA SELECCION (s/n): ", "ERROR. ");

						if(opcionContinuar == 1)
						{
							for(int j = 0; j < ll_len(pArrayListSeleccion); j++)
							{
								thisDos = (Seleccion*) ll_get(pArrayListSeleccion, j);
								selec_getId(thisDos, &id);

								if(idSelec == id)
								{
									selec_getConvocados(thisDos, &convocados);
									convocados--;
									selec_setConvocados(thisDos, convocados);
									jug_setIdSeleccion(this, 0);
									rtn = 1;
								}
							}
						}
					}
					else
					{
						printf("\nEL ID INGRESADO PERTENECE A UN JUGADOR QUE NO ESTA CONVOCADO. SE REGRESA AL MENU PRINCIPAL. \n");
						break;
					}
				}
			}
		}
	}

	return rtn;
}

int controller_MenuConvocar(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion)
{
	int rtn = -1;
	int opcionMenu;

	if(pArrayListJugador != NULL && pArrayListSeleccion != NULL)
	{
		if(utn_getNumero("\nCAMPOS A ELEGIR: \n"
						"1. CONVOCAR \n2. QUITAR DE LA SELECCION \n3. SALIR \n"
						"\nINGRESE OPCION: ", "ERROR.", 1, 3, 2, &opcionMenu) == 0)
		{
			switch(opcionMenu)
			{
				case 1:
					if(controller_convocarJugador(pArrayListJugador, pArrayListSeleccion) == 1)
					{
						printf("\nSE HA CONVOCADO AL JUGADOR CORRECTAMENTE. \n");
					}
				break;

				case 2:
					if(controller_quitarJugador(pArrayListJugador, pArrayListSeleccion) == 1)
					{
						printf("\nSE HA QUITADO AL JUGADOR DE LA SELECCION CORRECTAMENTE. \n");
					}
				break;
			}
		}
	}

    return rtn;
}

int controller_generadorID()
{
	int myId;
	FILE *pFile = NULL;

	pFile = fopen("ultimoId.txt","r");
	myId = parser_IdFromText(pFile);
	fclose(pFile);

	return myId;
}

int controller_saveId(int nuevoId)
{
	int rtn = -1;
	char idAuxChar[100];
	FILE *pFile = NULL;
	pFile = fopen("ultimoId.txt","w+");

	if(pFile != NULL)
	{
		nuevoId++;
		sprintf(idAuxChar,"%d",nuevoId);
		fprintf(pFile,"%d\n",nuevoId);
		rtn = 1;
	}

	fclose(pFile);

	return rtn;
}

/** \brief Guarda los datos de los jugadores en el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_guardarJugadoresModoTexto(char* path , LinkedList* pArrayListJugador)
{
	int rtn = -1;
	int id;
	char nombreCompleto[50];
	int edad;
	char posicion[50];
	char nacionalidad[50];
	int idSeleccion;

	eJugador* this = NULL;
	FILE* pFile;

	if(path != NULL && pArrayListJugador != NULL)
	{
		pFile = fopen(path, "w");
		this = jug_new();

		if(this != NULL)
		{
			fprintf(pFile, "id,nombreCompleto,edad,posicion,nacionalidad,idSelecion\n");

			for(int i = 0; i < ll_len(pArrayListJugador); i++)
			{
				this = (eJugador*) ll_get(pArrayListJugador, i);

				if(this != NULL)
				{
					jug_getId(this, &id);
					jug_getNombreCompleto(this, nombreCompleto);
					jug_getEdad(this, &edad);
					jug_getPosicion(this, posicion);
					jug_getNacionalidad(this, nacionalidad);
					jug_getIdSeleccion(this, &idSeleccion);

					fprintf(pFile,"%d,%s,%d,%s,%s,%d\n", id, nombreCompleto, edad, posicion, nacionalidad, idSeleccion);
					rtn = 1;
				}
				else
				{
					rtn = 0;
					break;
				}
			}
		}

		fclose(pFile);
	}

	return rtn;
}

/** \brief Guarda los datos de los selecciones en el archivo selecciones.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_guardarSeleccionesModoTexto(char* path , LinkedList* pArrayListSeleccion)
{
	int rtn = -1;
	int id;
	char pais[50];
	char confederacion[50];
	int convocados;

	Seleccion* this = NULL;
	FILE* pFile;

	if(path != NULL && pArrayListSeleccion != NULL)
	{
		pFile = fopen(path, "w");
		this = selec_new();

		if(this != NULL)
		{
			fprintf(pFile, "id,pais,confederacion,convocados\n");

			for(int i = 0; i < ll_len(pArrayListSeleccion); i++)
			{
				this = (Seleccion*) ll_get(pArrayListSeleccion, i);

				if(this != NULL)
				{
					selec_getId(this, &id);
					selec_getPais(this, pais);
					selec_getConfederacion(this, confederacion);
					selec_getConvocados(this, &convocados);

					fprintf(pFile,"%d,%s,%s,%d\n", id, pais, confederacion, convocados);
					rtn = 1;
				}
				else
				{
					rtn = 0;
					break;
				}
			}
		}

		fclose(pFile);
	}

	return rtn;
}

/** \brief Guarda los datos de los jugadores en el archivo binario.
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_guardarJugadoresModoBinario(char* path , LinkedList* pArrayListJugador, LinkedList* pArraySelec)
{
	int rtn = -1;
	int idSelecJugador, idSelec;
	FILE *pFile = NULL;
	eJugador* unJugador;
	Seleccion* unaSeleccion;
	int lenSelec = ll_len(pArraySelec);
	int lenJugadores = ll_len(pArrayListJugador);
	char confed[TAM_CHAR], confedSeleccion[TAM_CHAR];

	listarConfederacion();
	utn_getString("INGRESE LA CONFEDERACION DE LOS JUGADORES A GUARDAR: ", "ERROR. ", 3, TAM_CHAR, confed);

	pFile = fopen(path,"wb");

	if(pFile != NULL && pArrayListJugador != NULL)
	{
		for(int i = 0; i < lenJugadores; i++)
		{
			unJugador = ll_get(pArrayListJugador, i);
			jug_getIdSeleccion(unJugador, &idSelecJugador);

			for(int j = 0; j < lenSelec; j++)
			{
				unaSeleccion = ll_get(pArraySelec, j);
				selec_getConfederacion(unaSeleccion, confedSeleccion);
				selec_getId(unaSeleccion, &idSelec);

				if((stricmp(confedSeleccion, confed) == 0) && idSelec == idSelecJugador)
				{
					fwrite(unJugador,sizeof(eJugador),1,pFile);
					rtn = 1;
				}
			}
		}
	}

	fclose(pFile);

	return rtn;
}
