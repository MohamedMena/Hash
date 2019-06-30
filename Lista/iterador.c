#include "iterador.h"
#define DESTRUIR_ITER_OK 0
#define DESTRUIR_ITER_ERROR -1
#define AVANZAR_ITER_OK 0
#define AVANZAR_ITER_ERROR -1

iterador_t* iter_lista_crear(lista_se_t* lista){
	if(!lista) return NULL;

	iterador_t* nuevo_iter = malloc(sizeof(iterador_t));
	if(!nuevo_iter) return NULL;

	nuevo_iter->nodo_anterior = NULL;
	nuevo_iter->nodo_actual = lista->inicio;
	nuevo_iter->lista = lista;

	return nuevo_iter;
}

void* iter_lista_elemento_actual(iterador_t* iterador){
	if(!iterador) return NULL;
	if(!iterador->nodo_actual) return NULL;

	return(iterador->nodo_actual->elemento);
}

bool tiene_siguiente(iterador_t* iterador){
	if(!iterador) return false;

	if(!iterador->nodo_actual) return false;

	return (iterador->nodo_actual->siguiente != NULL);
}

int iter_lista_avanzar(iterador_t* iterador){
	if(!iterador) return AVANZAR_ITER_ERROR;

	if(!iterador->nodo_actual) return AVANZAR_ITER_ERROR;

	iterador->nodo_anterior = iterador->nodo_actual;
	iterador->nodo_actual = iterador->nodo_actual->siguiente;

	return AVANZAR_ITER_OK;
}

bool iter_lista_esta_al_final(iterador_t* iterador){
	if(!iterador) return true;

	return (!iterador->nodo_actual);
}

int reiniciar_iterador(iterador_t* iterador){
	if(!iterador) return -1;

	iterador->nodo_actual = iterador->lista->inicio;
	iterador->nodo_anterior = NULL;

	return 1;
}

int iter_lista_destruir(iterador_t* iterador){
	if(!iterador) return DESTRUIR_ITER_ERROR;
	free(iterador);

	return DESTRUIR_ITER_OK;
}


void* iter_lista_borrar(iterador_t* iterador){
	if(!iterador) return NULL;

	void* dato_a_eliminar = NULL;
	if(iterador->nodo_actual == iterador->lista->inicio){
		dato_a_eliminar = elemento_en_posicion(iterador->lista, 0); 
		borrar_de_posicion(iterador->lista, 0);
		iterador->nodo_actual = iterador->lista->inicio;
	}else{
		nodo_t* nodo_a_eliminar = iterador->nodo_actual;
		dato_a_eliminar = nodo_a_eliminar->elemento;
		iterador->nodo_actual = nodo_a_eliminar->siguiente;
		iterador->nodo_anterior->siguiente = nodo_a_eliminar->siguiente;
		free(nodo_a_eliminar);
		iterador->lista->cantidad--;
	}
	return dato_a_eliminar;
}