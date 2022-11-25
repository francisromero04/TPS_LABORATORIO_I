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
	char descripcionEstado[TAM_CHAR];

	jug_getId(this, &id);
	jug_getNombreCompleto(this, nombreCompleto);
	jug_getEdad(this, &edad);
	jug_getPosicion(this, posicion);
	jug_getNacionalidad(this, nacionalidad);
	jug_getIdSeleccion(this, &idSeleccion);
	jug_estadoConvocatoria(idSeleccion, descripcionEstado);

	printf("|%-4d|%-25s|%-6d|%-25s|%-20s|%-12s|\n", id, nombreCompleto, edad, posicion, nacionalidad, descripcionEstado);
}

int jug_criterioNacionalidad(void* pUno, void* pDos)
{
	int rtn;
	char nacionalidadUno[TAM_CHAR];
	char nacionalidadDos[TAM_CHAR];

	if(pUno != NULL && pDos != NULL)
	{
		jug_getNacionalidad(pUno, nacionalidadUno);
		jug_getNacionalidad(pDos, nacionalidadDos);

		rtn = stricmp(nacionalidadUno, nacionalidadDos);

	}
	return rtn;
}

int jug_criterioEdad(void* pUno, void* pDos)
{
	int rtn = 0;
	int edadUno, edadDos;

	/* 1 = menor a mayor
	 * 0 = mayor a menor
	 * -1 = como vino
	 */

	if(pUno != NULL && pDos != NULL)
	{
		jug_getEdad(pUno, &edadUno);
		jug_getEdad(pDos, &edadDos);

		if(edadUno < edadDos)
		{
			rtn = -1;
		}
		else
		{
			if(edadUno > edadDos)
			{
				rtn = 1;
			}
		}
	}

	return rtn;
}

int jug_criterioNombre(void* pUno, void* pDos)
{
	int rtn;

	char nombreUno[TAM_CHAR];
	char nombreDos[TAM_CHAR];

	if(pUno != NULL && pDos != NULL)
	{
		jug_getNombreCompleto(pUno, nombreUno);
		jug_getNombreCompleto(pDos, nombreDos);

		rtn = stricmp(nombreUno, nombreDos);
	}

	return rtn;
}

int jug_estadoConvocatoria(int idSeleccion , char* estadoStr)
{
	int rtn = -1;

	if(idSeleccion >= 0 &&  idSeleccion <= 30 && estadoStr != NULL)
	{
		switch(idSeleccion)
		{
			case 0:
				strcpy(estadoStr, "NO CONVOCADO");
			break;

			case 1:
				strcpy(estadoStr, "ALEMANIA");
			break;

			case 2:
				strcpy(estadoStr, "ARABIA");
			break;

			case 3:
				strcpy(estadoStr, "ARGENTINA");
			break;

			case 4:
				strcpy(estadoStr, "AUSTRALIA");
			break;

			case 5:
				strcpy(estadoStr, "BELGICA");
			break;

			case 6:
				strcpy(estadoStr, "BRASIL");
			break;

			case 7:
				strcpy(estadoStr, "CAMERUN");
			break;

			case 8:
				strcpy(estadoStr, "CANADA");
			break;

			case 9:
				strcpy(estadoStr, "COREA SUR");
			break;

			case 10:
				strcpy(estadoStr, "COSTA RICA");
			break;

			case 11:
				strcpy(estadoStr, "CROACIA");
			break;

			case 12:
				strcpy(estadoStr, "DINAMARCA");
			break;

			case 13:
				strcpy(estadoStr, "ECUADOR");
			break;

			case 14:
				strcpy(estadoStr, "ESPAÑA");
			break;

			case 15:
				strcpy(estadoStr, "EE. UU.");
			break;

			case 16:
				strcpy(estadoStr, "FRANCIA");
			break;

			case 17:
				strcpy(estadoStr, "GALES");
			break;

			case 18:
				strcpy(estadoStr, "GHANA");
			break;

			case 19:
				strcpy(estadoStr, "HOLANDA");
			break;

			case 20:
				strcpy(estadoStr, "INGLATERRA");
			break;

			case 21:
				strcpy(estadoStr, "IRAN");
			break;

			case 22:
				strcpy(estadoStr, "JAPON");
			break;

			case 23:
				strcpy(estadoStr, "MARRUECOS");
			break;

			case 24:
				strcpy(estadoStr, "MEXICO");
			break;

			case 25:
				strcpy(estadoStr, "POLONIA");
			break;

			case 26:
				strcpy(estadoStr, "PORTUGAL");
			break;

			case 27:
				strcpy(estadoStr, "QATAR");
			break;

			case 28:
				strcpy(estadoStr, "SENEGAL");
			break;

			case 29:
				strcpy(estadoStr, "SERBIA");
			break;

			case 30:
				strcpy(estadoStr, "SUIZA");
			break;
		}
		rtn = 1;
	}

	return rtn;
}
