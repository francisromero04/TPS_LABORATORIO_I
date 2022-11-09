#include "Jugador.h"

eJugador* jug_new()
{
	eJugador* aux = NULL;
	aux = (eJugador*)malloc(sizeof(eJugador));
	return aux;
}

eJugador* jug_newParametros(char* idStr, char* nombreCompletoStr, char* edadStr, char* posicionStr, char* nacionalidadStr, char* idSelccionStr)
{
    eJugador* this = NULL;
    this = jug_new();

	if(this != NULL)
	{
		if( !(jug_setId(this, atoi(idStr)) &&
			  jug_setNombreCompleto(this, nombreCompletoStr) &&
			  jug_setEdad(this, atoi(edadStr)) &&
			  jug_setPosicion(this, posicionStr) &&
			  jug_setNacionalidad(this, nacionalidadStr) &&
			  jug_setIdSeleccion(this, atoi(idSelccionStr))) )
		{
			jug_delete(this);
		}
	}

	return this;
}

//UTILIZO ESTA CUANDO UN USUARIO DA DE ALTA UN PASAJERO USANDO LOS INPUTS (controller_addJugador)
eJugador* jug_newParametrosAlta(int id, char* nombreCompletoStr, int edad, char* posicionStr, char* nacionalidadStr, int idSelccion)
{
	eJugador* this;

	if(id >= 0 && nombreCompletoStr != NULL && edad >= 0 && posicionStr != NULL && nacionalidadStr != NULL && idSelccion >= 0)
	{
		this = jug_new();

		if(this != NULL)
		{
			if(jug_setId(this, id) && jug_setNombreCompleto(this, nombreCompletoStr) && jug_setEdad(this, edad) &&
			   jug_setPosicion(this, posicionStr) && jug_setNacionalidad(this, nacionalidadStr))
			{
				puts("\nALTA DE JUGADOR EXITOSA!\n");
			}
			else
			{
				jug_delete(this);
			}
		}
	}

	return this;
}

void jug_delete(eJugador* this)
{
	if(this != NULL)
	{
		free(this);
		this = NULL;
	}
}

//SETTERS

int jug_setId(eJugador* this,int id)
{
	int rtn = -1;

	if(this != NULL && id > 0)
	{
		this->id = id;
		rtn = 1;
	}

	return rtn;
}

int jug_setNombreCompleto(eJugador* this,char* nombreCompleto)
{
	int rtn = -1;

	if(this != NULL && nombreCompleto != NULL)
	{
		if(strlen(nombreCompleto) < 25 && strlen(nombreCompleto) > 1)
		{
			strcpy(this->nombreCompleto, nombreCompleto);
			rtn = 1;
		}
	}

	return rtn;
}

int jug_setEdad(eJugador* this,int edad)
{
	int rtn = -1;

	if(this !=NULL)
	{
		if(edad > 0 && edad <= 40)
		{
			this->edad = edad;
			rtn = 1;
		}
	}

	return rtn;
}

int jug_setPosicion(eJugador* this,char* posicion)
{
	int rtn = -1;

	if(this != NULL && posicion !=NULL)
	{
		if(strlen(posicion) < 25 && strlen(posicion) > 1)
		{
			strcpy(this->posicion, posicion);
			rtn = 1;
		}
	}

	return rtn;
}

int jug_setNacionalidad(eJugador* this,char* nacionalidad)
{
	int rtn = -1;

	if(this!=NULL)
	{
		if(strlen(nacionalidad) < 25 && strlen(nacionalidad) > 1)
		{
			strcpy(this->nacionalidad, nacionalidad);
			rtn = 1;
		}
	}

	return rtn;
}

int jug_setIdSeleccion(eJugador* this,int idSeleccion)
{
	int rtn = -1;

	if(this != NULL && idSeleccion >= 0)
	{
		this->idSeleccion = idSeleccion;
		rtn = 1;
	}

	return rtn;
}

//GETTERS

int jug_getId(eJugador* this,int* id)
{
	int rtn = -1;

	if(this != NULL)
	{
		*id = this->id;
		rtn = 1;
	}

	return rtn;
}

int jug_getNombreCompleto(eJugador* this,char* nombreCompleto)
{
    int rtn = -1;

	if(this != NULL && nombreCompleto != NULL)
	{
		strcpy(nombreCompleto, this->nombreCompleto);
		rtn = 1;
	}

	return rtn;
}

int jug_getPosicion(eJugador* this,char* posicion)
{
	int rtn = -1;

	if(this != NULL && posicion != NULL)
	{
		strcpy(posicion, this->posicion);
		rtn = 1;
	}
	return rtn;
}

int jug_getNacionalidad(eJugador* this,char* nacionalidad)
{
	int rtn = -1;

	if(this != NULL && nacionalidad != NULL)
	{
		strcpy(nacionalidad, this->nacionalidad);
		rtn = 1;
	}

	return rtn;
}

int jug_getEdad(eJugador* this,int* edad)
{
	int rtn = -1;

	if(this != NULL && edad != NULL)
	{
		*edad = this->edad;
		rtn = 1;
	}

	return rtn;
}

int jug_getIdSeleccion(eJugador* this,int* idSeleccion)
{
	int rtn = -1;

	if(this != NULL)
	{
		*idSeleccion = this->idSeleccion;
		rtn = 1;
	}

	return rtn;
}

int eJugador_actualizarUltimoId(int idAnterior)
{
	int rtn = -1;

	FILE* pFile = fopen("ultimoId.txt", "w");

	if(pFile != NULL)
	{
		fprintf(pFile, "%d\n", idAnterior+1);
		rtn = 1;
	}

	fclose(pFile);

	return rtn;
}

void eJugador_imprimir(eJugador* this)
{
	int id;
	char nombreCompleto[50];
	int edad;
	char posicion[30];
	char nacionalidad[30];
	int idSeleccion;

	jug_getId(this, &id);
	jug_getNombreCompleto(this, nombreCompleto);
	jug_getEdad(this, &edad);
	jug_getPosicion(this, posicion);
	jug_getNacionalidad(this, nacionalidad);
	jug_getIdSeleccion(this, &idSeleccion);

	printf("|%-4d|%-25s|%-6d|%-25s|%-20s|%-12d|\n", id, nombreCompleto, edad, posicion, nacionalidad, idSeleccion);
}

/// @brief A partir de un id retorna en puntero del jugador y por referencia el indice.
/// @param pArrayListJugador
/// @param auxiliarId
/// @param index
/// @return retorna el puntero al jugador y si no existe, NULL.
eJugador* jug_buscarPorIdSeleccion(LinkedList* pArrayListJugador, int auxiliarId, int* index)
{
	eJugador* this;
	int len = ll_len(pArrayListJugador);
	int idAux;

	for(int i = 0; i < len; i++)
	{
		this = ll_get(pArrayListJugador, i);
		jug_getIdSeleccion(this, &idAux);

		if(idAux == auxiliarId)
		{
			*index = ll_indexOf(pArrayListJugador, this);
			break;
		}
		else
		{
			this = NULL;
		}
	}

	return this;
}

int jug_criterioNacionalidad(void* pUno, void* pDos)
{
	int rtn;
	eJugador* thisOne;
	eJugador* thisTwo;
	thisOne = pUno;
	thisTwo = pDos;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if(strnicmp(thisOne->nacionalidad, thisTwo->nacionalidad, 50) > 0)
		{
			rtn = 1;
		}
		else
		{
			if(strnicmp(thisOne->nacionalidad, thisTwo->nacionalidad, 50) < 0)
			{
				rtn = 0;
			}
		}
	}
	return rtn;
}

int jug_criterioEdad(void* pUno, void* pDos)
{
	int rtn;
	eJugador* thisOne;
	eJugador* thisTwo;
	thisOne = pUno;
	thisTwo = pDos;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if(thisOne->edad > thisTwo->edad)
		{
			rtn = 1;
		}
		else
		{
			if(thisOne->edad < thisTwo->edad)
			{
				rtn = 0;
			}
		}
	}
	return rtn;
}

int jug_criterioNombre(void* pUno, void* pDos)
{
	int rtn;
	eJugador* thisOne;
	eJugador* thisTwo;
	thisOne = pUno;
	thisTwo = pDos;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if(strnicmp(thisOne->nombreCompleto, thisTwo->nombreCompleto, 50) > 0)
		{
			rtn = 1;
		}
		else
		{
			if(strnicmp(thisOne->nombreCompleto, thisTwo->nombreCompleto, 50) < 0)
			{
				rtn = 0;
			}
		}
	}
	return rtn;
}
