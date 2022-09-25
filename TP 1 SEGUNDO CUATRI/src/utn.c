#include "utn.h"

//-----------------------------------------------STATICS HEADERS--------------------------------------------------------

static int myGets(char* cadena, int longitud);
static int esNumerica(char* cadena, int limite);
static int getInt(int* pResultado);

//-----------------------------------------------FUNCIONES ESTATICAS----------------------------------------------------

/// @brief Se encarga de añadirle un \n en lugar del enter y un \0 para finalizar la cadena.
///  Luego copia bufferString en la cadena pasada como parametro.
/// @param cadena
/// @param longitud
/// @return Retorna 1 si salio bien y un 0 de lo contrario.
static int myGets(char* cadena, int longitud)
{
	int retorno = 0;
	char bufferString[4096];

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)
		{
			if(bufferString[strlen(bufferString)-1] == '\n')
			{
				bufferString[strlen(bufferString)-1] = '\0';
			}
			if(strlen(bufferString) <= longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno = 1;
			}
		}
	}
	return retorno;
}

/// @brief Recibe una cadena con su limite entero. Valida si en la cadena hay un numero cargado.
/// @param cadena
/// @param limite
/// @return Retorna 0 si salio bien y -1 si salio mal.
static int esNumerica(char* cadena, int limite)
{
	int retorno = -1;
	int i;

	if(cadena != NULL && limite > 0)
	{
		retorno = 1; //VERDADERO
		for(i = 0; i < limite && cadena[i] != '\0'; i++)
		{
			if(i == 0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/// @brief Se encarga de validar si lo que se ingreso mediante myGets es un numero. Si la cadena tiene un
/// caracter que este entre el 0 y el 9, lo pasa a un entero mediante atoi.
/// @param pResultado
/// @return Retorna 1 en caso exitoso y 0 de lo contrario.
static int getInt(int* pResultado)
{
	int retorno = 0;
	char buffer[4096];

	if(	pResultado != NULL &&
		myGets(buffer, sizeof(buffer)) == 0 &&
		esNumerica(buffer,sizeof(buffer)) )
		{
			*pResultado = atoi(buffer);
			retorno = 1;
		}
	return retorno;
}

//-----------------------------------------------INPUTS UTN-------------------------------------------------------------

/// @brief Reserva espacios de memoria para dos mensajes a traves de punteros. Recibe dos enteros para establecer
/// un rango entre numeros, otro para reintentos y un entero para guardar el numero pedido.
/// @param char[] mensaje
/// @param char[] mensajeError
/// @param int minimo
/// @param int maximo
/// @param int reintentos
/// @param int* pNumeroIngresado
/// @return Retorna 1 si salio bien, de lo contrario 0.
int utn_getNumero(char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos, int* pResultado)
{
	int retorno = 0;
	int rtnGetInt;
	int bufferInt;
	do
	{
		printf("%s",mensaje);
		rtnGetInt = getInt(&bufferInt);

		if(rtnGetInt == 0 && pResultado != NULL && mensaje != NULL && mensajeError != NULL
				&& reintentos >= 0 && bufferInt >= minimo && bufferInt <= maximo)
		{
			retorno = 1;
			*pResultado = bufferInt;
			break;
		}

		printf("%s",mensajeError);
		reintentos--;

	}while(reintentos>=0);

	return retorno;
}
