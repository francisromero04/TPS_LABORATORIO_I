#include "Seleccion.h"

Seleccion* selec_new()
{
	Seleccion* aux = NULL;
	aux = (Seleccion*)malloc(sizeof(Seleccion));
	return aux;
}

Seleccion* selec_newParametros(char* idStr, char* paisStr, char* confederacionStr, char* convocadosStr)
{
	Seleccion* this = NULL;
	this = selec_new();

	if(this != NULL)
	{
		if( !(selec_setId(this, atoi(idStr)) && selec_setPais(this, paisStr) &&
			  selec_setConfederacion(this, confederacionStr) && selec_setConvocados(this, atoi(convocadosStr)) ))
		{
			selec_delete(this);
		}
	}

	return this;
}

void selec_delete(Seleccion* this)
{
	if(this != NULL)
	{
		free(this);
		this = NULL;
	}
}

//setters
int selec_setId(Seleccion* this, int id)
{
	int rtn = -1;

	if(this != NULL && id > 0)
	{
		this->id = id;
		rtn = 1;
	}

	return rtn;
}

int selec_setPais(Seleccion* this, char* pais)
{
	int rtn = -1;

	if(this != NULL && pais != NULL)
	{
		if(strlen(pais) < 25 && strlen(pais) > 1)
		{
			strcpy(this->pais, pais);
			rtn = 1;
		}
	}

	return rtn;
}

int selec_setConfederacion(Seleccion* this, char* confederacion)
{
	int rtn = -1;

	if(this != NULL && confederacion != NULL)
	{
		if(strlen(confederacion) < 25 && strlen(confederacion) > 1)
		{
			strcpy(this->confederacion, confederacion);
			rtn = 1;
		}
	}

	return rtn;
}

int selec_setConvocados(Seleccion* this, int convocados)
{
	int rtn = -1;

	if(this != NULL)
	{
		this->convocados = convocados;
		rtn = 1;
	}

	return rtn;
}

//getters

int selec_getId(Seleccion* this, int* id)
{
	int rtn = -1;

	if(this != NULL)
	{
		*id = this->id;
		rtn = 1;
	}

	return rtn;
}

int selec_getPais(Seleccion* this, char* pais)
{
    int rtn = -1;

	if(this != NULL && pais != NULL)
	{
		strcpy(pais, this->pais);
		rtn = 1;
	}

	return rtn;
}

int selec_getConfederacion(Seleccion* this, char* confederacion)
{
	int rtn = -1;

	if(this != NULL && confederacion != NULL)
	{
		strcpy(confederacion, this->confederacion);
		rtn = 1;
	}

	return rtn;
}

int selec_getConvocados(Seleccion* this, int* convocados)
{
	int rtn = -1;

	if(this != NULL && convocados != NULL)
	{
		*convocados = this->convocados;
		rtn = 1;
	}

	return rtn;
}

void selec_imprimir(Seleccion* this)
{
	int id;
	char pais[30];
	char confederacion[15];
	int convocados;

	selec_getId(this, &id);
	selec_getPais(this, pais);
	selec_getConfederacion(this, confederacion);
	selec_getConvocados(this, &convocados);

	printf("|%-4d|%-20s|%-17s|%-12d|\n", id, pais, confederacion, convocados);
}

void listarConfederacion(void)
{
	printf("\n+---------------+\n"
			"|CONFEDERACIONES|\n"
			"+---------------+\n"
			"|      AFC      |\n"
			"|      CAF      |\n"
			"|     UEFA      |\n"
			"|    CONCACAF   |\n"
			"|    CONMEBOL   |\n"
			"+---------------+\n\n");
}

int selec_criterioConfederacion(void* pUno, void* pDos)
{
	int rtn;
	Seleccion* thisOne;
	Seleccion* thisTwo;
	thisOne = pUno;
	thisTwo = pDos;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if(strncmp(thisOne->confederacion, thisTwo->confederacion, 50) > 0)
		{
			rtn = 1;
		}
		else
		{
			if(strncmp(thisOne->confederacion, thisTwo->confederacion, 50) < 0)
			{
				rtn = 0;
			}
		}
	}
	return rtn;
}
