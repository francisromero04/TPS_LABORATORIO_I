int controller_cargarJugadoresDesdeTexto(char* path , LinkedList* pArrayListJugador);
int controller_cargarJugadoresDesdeBinario(char* path , LinkedList* pArrayListJugador);
int controller_agregarJugador(LinkedList* pArrayListJugador);
int controller_editarJugador(LinkedList* pArrayListJugador);
int controller_removerJugador(LinkedList* pArrayListJugador);
int controller_listarJugadores(LinkedList* pArrayListJugador);
int controller_ordenarJugadores(LinkedList* pArrayListJugador, int criterio);
int controller_guardarJugadoresModoTexto(char* path , LinkedList* pArrayListJugador);
int controller_guardarJugadoresModoBinario(char* path , LinkedList* pArrayListJugador, LinkedList* pArraySelec);
int controller_cargarSeleccionesDesdeTexto(char* path , LinkedList* pArrayListSeleccion);
int controller_editarSeleccion(LinkedList* pArrayListSeleccion);
int controller_listarSelecciones(LinkedList* pArrayListSeleccion);
int controller_ordenarSelecciones(LinkedList* pArrayListSeleccion);
int controller_guardarSeleccionesModoTexto(char* path , LinkedList* pArrayListSeleccion);
int controller_getUltimoId(void);
int controller_saveId(int nuevoId);
int controller_generadorID();
int controller_convocarJugador(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion);
int controller_quitarJugador(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion);
int controller_MenuConvocar(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion);
int controller_listarJugadoresConvocados(LinkedList* pArrayListJugador);
int controller_listarJugadoresNoConvocados(LinkedList* pArrayListJugador);
