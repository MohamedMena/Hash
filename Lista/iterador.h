#ifndef __ITERADOR_H__
#define __ITERADOR_H__

#include "lista_se.h"

typedef struct iterador{
	nodo_t* nodo_actual;
	nodo_t* nodo_anterior;
	lista_se_t* lista;
} iterador_t;


/* Crea un iterador para recorrer la lista pasada por parámetro.
* Devuelve un iterador para recorrer la lista o NULL si hubo un error.
*/
iterador_t* crear(lista_se_t* lista);

/*
* Destruye el iterador. 
* Devuelve 0 si se destruyo correctamente
* Devuelve -1 en caso de error.
*/
int destruir(iterador_t* iterador);

/*
* Avanza el iterador a la siguiente posicion de la lista.
* Devuelve 0 si se destruyo correctamente
* Devuelve -1 en caso de error.
*/
int avanzar(iterador_t* iterador);

/*
* Devuelve true si existe un elemento en la posicion siguiente a la actual. Devuelve False en caso contrario.
*/
bool tiene_siguiente(iterador_t* iterador);

/*
* Devuelve el elemento que esta en la posicion actual del iterador
* Devuelve NULL en caso de error.
*/
void* elemento_actual(iterador_t* iterador);

/*
* Verifica si el iterador apunta al final de la lista.
* Esto es cuando el iterador esta apuntando a NULL.
* Devuelve true si el iterador llego al final, false en caso contrario.
*/
bool iter_esta_al_final(iterador_t* iterador);

/*
* Elimina el elemento en la posicion a la que apunta el iterador.
* Elimina la posicion de la lista y devuelve el dato.
* Devuelve NULL en caso de error.
*/
void* iter_borrar(iterador_t* iterador);

/*
* Reinicia el iterador, volviendo la posicion actual al principio de la lista.
* Devuelve 0 si se reinicio correctamente
* Devuelve -1 en caso de error.
*/
int reiniciar_iterador(iterador_t* iterador);

#endif