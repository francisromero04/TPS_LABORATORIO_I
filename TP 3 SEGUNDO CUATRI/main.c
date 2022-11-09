#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Jugador.h"

int main()
{
	setbuf(stdout, NULL);
    int opcionMenu, opcionListar, opcionOrden, opcionSalir;
    int flagCarga = 0, flagGuardado = 0;
    LinkedList* listaJugadores = ll_newLinkedList();
    LinkedList* listaSelecciones = ll_newLinkedList();
    LinkedList* listaBinaria = ll_newLinkedList();

    do{
    	puts("\n\t\t\tMENU DE OPCIONES:\n"
			"\t\t\t-----------------\n\n"
			"1. CARGA DE ARCHIVOS\n"
			"2. ALTA DE JUGADOR \n"
			"3. MODIFICAR DE JUGADOR. \n"
			"4. BAJA DE JUGADOR. \n"
			"5. LISTADOS. \n"
			"6. CONVOCAR JUGADORES. \n"
			"7. ORDENAR Y LISTAR. \n"
			"8. GENERAR ARCHIVO BINARIO. \n"
			"9. CARGAR ARCHIVO BINARIO E IMPRIMIR. \n"
			"10. GUARDAR ARCHIVOS .CSV \n"
			"11. SALIR. \n\n");
    	utn_getNumero("INGRESE OPCION: ", "ERROR. ", 1, 11, 3, &opcionMenu);

        switch(opcionMenu)
        {
            case 1:
            	if(controller_cargarJugadoresDesdeTexto("jugadores.csv", listaJugadores) == 1 &&
                   controller_cargarSeleccionesDesdeTexto("selecciones.csv", listaSelecciones) == 1)
            	{
            		printf("\nSE HAN CARGADO LOS JUGADORES Y LAS SELECCIONES DESDE LOS ARCHIVOS DATA CSV.\n");
            		flagCarga = 1;
            	}
			break;

            case 2:
            	if(flagCarga == 1)
				{
            		controller_agregarJugador(listaJugadores);
				}
				else
				{
					printf("\nNO ES POSIBLE DAR DE ALTA SIN HABER CARGADO LOS DATOS DESDE LOS ARCHIVOS.\n");
				}
            break;

            case 3:
            	if(flagCarga == 1)
				{
            		controller_editarJugador(listaJugadores);
				}
				else
				{
					printf("\nNO ES POSIBLE MODIFICAR SIN HABER CARGADO LOS DATOS DESDE LOS ARCHIVOS.\n");
				}
            break;

            case 4:
				if(flagCarga == 1)
				{
					controller_removerJugador(listaJugadores);
				}
				else
				{
					printf("\nNO ES POSIBLE DAR DE BAJA SIN HABER CARGADO LOS DATOS DESDE LOS ARCHIVOS.\n");
				}
			break;

            case 5:
            	if(flagCarga == 1)
            	{
            		utn_getNumero("\nOPCIONES A IMPRIMIR: \n"
								  "1. TODOS LOS JUGADORES \n2. TODAS LAS SELECCIONES \n"
								  "3. JUGADORES CONVOCADOS (unicamente) \n"
								"\nINGRESE OPCION: ", "ERROR.", 1, 3, 2, &opcionListar);

            		switch(opcionListar)
            		{
						case 1:
							controller_listarJugadores(listaJugadores);
						break;

						case 2:
							controller_listarSelecciones(listaSelecciones);
						break;

						case 3:
							controller_listarJugadoresConvocados(listaJugadores);
						break;
            		}
            	}
            	else
            	{
            		printf("\nNO ES POSIBLE LISTAR SIN HABER CARGADO LOS DATOS DESDE LOS ARCHIVOS.\n");
            	}
            break;

            case 6:
				if(flagCarga == 1)
				{
					controller_MenuConvocar(listaJugadores, listaSelecciones);
				}
				else
				{
					printf("\nNO ES POSIBLE CONVOCAR SIN HABER CARGADO LOS DATOS DESDE LOS ARCHIVOS.\n");
				}
			break;

            case 7:
				if(flagCarga == 1)
				{
					utn_getNumero("\nOPCIONES A ORDENAR: \n"
								  "1. JUGADORES POR NACIONALIDAD\n2. SELECCIONES POR CONFEDERACION\n"
								  "3. JUGADORES POR EDAD\n4. JUGADORES POR NOMBRE\n"
								  "\nINGRESE LA OPCION DE ORDENAMIENTO: ", "ERROR. ", 1, 4, 3, &opcionOrden);

					switch(opcionOrden)
					{
						case 1:
							controller_ordenarJugadores(listaJugadores, 1);
						break;

						case 2:
							controller_ordenarSelecciones(listaSelecciones);
						break;

						case 3:
							controller_ordenarJugadores(listaJugadores, 2);
						break;

						case 4:
							controller_ordenarJugadores(listaJugadores, 3);
						break;
					}
				}
				else
				{
					printf("\nNO ES POSIBLE ORDENAR/LISTAR SIN HABER CARGADO LOS DATOS DESDE LOS ARCHIVOS.\n");
				}
			break;

            case 8:
            	if(flagCarga == 1)
				{
            		if(controller_guardarJugadoresModoBinario("data_bin.bin", listaJugadores, listaSelecciones) != 1)
            		{
            			printf("\nESTA CONFEDERACION NO TIENE JUGADORES CONVOCADOS, PARA GUARDAR EN BINARIO PRIMERO CONVOQUE.\n");
            		}
            		else
            		{
            			printf("\nESTA CONFEDERACION TIENE JUGADORES CONVOCADOS, SE GUARDARON EN BINARIO CORRECTAMENTE.\n");
            		}
				}
				else
				{
					printf("\nNO ES POSIBLE GENERAR ARCHIVO BINARIO SIN HABER CARGADO LOS DATOS DESDE LOS ARCHIVOS.\n");
				}
            break;

            case 9:
            	if(flagCarga == 1)
				{
            		if(controller_cargarJugadoresDesdeBinario("data_bin.bin", listaBinaria) == 1)
            		{
            			controller_listarJugadores(listaBinaria);
            		}
            		else
            		{
            			printf("\nNO HAY JUGADORES CONVOCADOS GUARDADOS EN BINARIO. \n");
            		}
				}
				else
				{
					printf("\nNO ES POSIBLE CARGAR ARCHIVO BINARIO SIN HABER CARGADO LOS DATOS DESDE LOS ARCHIVOS.\n");
				}
            break;

            case 10:
				if(flagCarga == 1)
				{
					if(controller_guardarJugadoresModoTexto("jugadores.csv", listaJugadores) == 1 &&
					   controller_guardarSeleccionesModoTexto("selecciones.csv", listaSelecciones) == 1)
					{
						printf("\nLAS LISTAS FUERON GUARDADAS CON EXITO. \n");
						flagGuardado = 1;
					}
					else
					{
						printf("\nNO SE PUDIERON GUARDAR LAS LISTAS DE FORMA CORRECTA. \n");
					}
				}
				else
				{
					printf("\nNO ES POSIBLE GUARDAR SIN HABER CARGADO LOS DATOS DESDE LOS ARCHIVOS.\n");
				}
			break;

            case 11:
            	if(flagCarga == 1 && flagGuardado != 1)
            	{
					printf("\nPARA PODER SALIR DEBES GUARDAR PRIMERO.\n");
            	}
            	else
            	{
            		if(flagGuardado == 1 || flagCarga == 0)
            		{
                    	opcionSalir = funcionContinuar("\nDESEA SALIR DEL PROGRAMA? (s/n): ", "ERROR. ");
            		}
            	}
            break;
        }
    }while(opcionSalir != 1);

    return 0;
}

