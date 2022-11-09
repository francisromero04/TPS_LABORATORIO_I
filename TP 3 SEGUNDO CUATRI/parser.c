#include "parser.h"

/** \brief Parsea los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 */
int parser_JugadorFromText(FILE* pFile , LinkedList* pArrayListJugador)
{
	eJugador* this;
	int rtn = -1;
	char buffer[6][100];
	int datos;

	if(pFile != NULL)
	{
		if(pArrayListJugador != NULL)
		{
			fscanf(pFile,"%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]\n",buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);

			do
			{
				datos = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);

				if(datos == 6)
				{
					this = jug_newParametros(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);

					if(this != NULL)
					{
						ll_add(pArrayListJugador,this);
						rtn = 1;
					}
				}
			}while(feof(pFile) == 0);
		}
	}

    return rtn;
}

/** \brief Parsea los datos de los jugadores desde el archivo binario.
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 */
int parser_JugadorFromBinary(FILE* pFile , LinkedList* pArrayListJugador)
{
	int rtn = -1;
	int lectura;

	if(pFile != NULL && pArrayListJugador != NULL)
	{
		eJugador* pJug = jug_new();

		do
		{
			lectura = fread(pJug, sizeof(eJugador), 1, pFile);

			if(lectura)
			{
				ll_add(pArrayListJugador, pJug);
				pJug = jug_new();
				rtn = 1;
			}
		}while(!feof(pFile));

		free(pJug);
		fclose(pFile);
	}

	return rtn;
}

/** \brief Parsea los datos de los selecciones desde el archivo selecciones.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int parser_SeleccionFromText(FILE* pFile , LinkedList* pArrayListSeleccion)
{
	Seleccion* this;
	int rtn = -1;
	char buffer[4][100];
	int datos;

	if(pFile != NULL)
	{
		if(pArrayListSeleccion != NULL)
		{
			fscanf(pFile,"%[^,], %[^,], %[^,], %[^\n]\n",buffer[0], buffer[1], buffer[2], buffer[3]);

			do
			{
				datos = fscanf(pFile,"%[^,], %[^,], %[^,], %[^\n]\n",buffer[0], buffer[1], buffer[2], buffer[3]);

				if(datos == 4)
				{
					this = selec_newParametros(buffer[0], buffer[1], buffer[2], buffer[3]);

					if(this != NULL)
					{
						ll_add(pArrayListSeleccion,this);
						rtn = 1;
					}
				}
			}while(feof(pFile) == 0);
		}
	}

	return rtn;
}

int parser_IdFromText(FILE* pFile)
{
	int rtn = -1;
	char idAux[100];
	int datos;

	if(pFile != NULL)
	{
		do
		{
			datos = fscanf(pFile, "%[^\n]\n",idAux);

			if(datos == 1)
			{
				rtn = atoi(idAux);
			}
		}while(feof(pFile) == 0);
	}

    return rtn;
}
