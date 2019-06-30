#include "lista_se.h"

#define CANTIDAD_INICIAL 0
#define SE_INSERTO_NODO_OK 0
#define INSERTAR_NODO_ERROR -1
#define BORRAR_NODO_OK 0
#define BORRAR_NODO_ERROR -1
#define NO_EXISTE_ULTIMO NULL
#define DESTRUIR_LISTA_ERROR -1
#define DESTRUIR_LISTA_OK 0
#define INDICE_INICIO 0

nodo_t* crear_nodo(void* elemento){
	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo) return NULL;

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;

	return nuevo_nodo;
}

bool vacia(lista_se_t* lista){
	if(!lista) return false;

	return (lista->inicio == NULL);
}


lista_se_t* crear_lista(){
	lista_se_t* nueva_lista = malloc(sizeof(lista_se_t));

	if(!nueva_lista) return NULL;

	nueva_lista->inicio = NULL;
	nueva_lista->cantidad = CANTIDAD_INICIAL;

	return nueva_lista;
}

int insertar_en_posicion(lista_se_t* lista, void* elemento, int indice){
	if(!lista) return INSERTAR_NODO_ERROR;

	if(indice < INDICE_INICIO || indice > lista->cantidad) indice = (int)lista->cantidad;

	nodo_t* nodo_a_insertar = crear_nodo(elemento);
	if(!nodo_a_insertar) return INSERTAR_NODO_ERROR;

	if(indice != 0){
		int posicion_actual = INDICE_INICIO;

		nodo_t* nodo_actual = lista->inicio;
		while(posicion_actual < indice-1){
			nodo_actual = nodo_actual->siguiente;
			posicion_actual++;
		}
		nodo_a_insertar->siguiente = nodo_actual->siguiente;
		nodo_actual->siguiente = nodo_a_insertar;
	}else{
		nodo_a_insertar->siguiente = lista->inicio;
		lista->inicio = nodo_a_insertar;
	}

	lista->cantidad++;
	return SE_INSERTO_NODO_OK;
}

int insertar(lista_se_t* lista, void* elemento){
	if(!lista) return INSERTAR_NODO_ERROR;

	return (insertar_en_posicion(lista, elemento, (int)lista->cantidad));
}

int borrar_de_posicion(lista_se_t* lista, int indice){
	if(!lista) return BORRAR_NODO_ERROR;

	if(vacia(lista)) return BORRAR_NODO_ERROR;

	if(indice < 0 || indice > lista->cantidad-1) indice = (int)lista->cantidad-1;
	
	nodo_t* nodo_a_eliminar = NULL;
	if(indice != 0){
		int posicion_actual = INDICE_INICIO;
		nodo_t* nodo_anterior = NULL;
		nodo_a_eliminar = lista->inicio;
		while(posicion_actual < indice){
			nodo_anterior = nodo_a_eliminar;
			nodo_a_eliminar = nodo_a_eliminar->siguiente;
			posicion_actual++;
		}
		nodo_anterior->siguiente = nodo_a_eliminar->siguiente;
	}else{
		nodo_a_eliminar = lista->inicio;
		lista->inicio = nodo_a_eliminar->siguiente;
	}

	lista->cantidad--;
	free(nodo_a_eliminar);
	return BORRAR_NODO_OK;
}

int borrar(lista_se_t* lista){
	if(!lista) return BORRAR_NODO_ERROR;

	int indice = (int)lista->cantidad;
	if(indice != 0) indice--;

	return borrar_de_posicion(lista, indice);
}

void* elemento_en_posicion(lista_se_t* lista, int indice){
	if(!lista) return NULL;

	if(vacia(lista)) return NULL;

	if(indice < 0 || indice > lista->cantidad-1) return NULL;

	int posicion_actual = 0;
	nodo_t* nodo_actual = lista->inicio;
	while(posicion_actual < indice){
		nodo_actual = nodo_actual->siguiente;
		posicion_actual++;
	}

	return nodo_actual->elemento;
}

void* ultimo(lista_se_t* lista){
	if(!lista) return NO_EXISTE_ULTIMO;

	int indice = (int)lista->cantidad;
	if(indice != 0) indice--;

	return elemento_en_posicion(lista, indice);
}

size_t elementos(lista_se_t* lista){
	return lista->cantidad;
}

int destruir_lista(lista_se_t* lista, void destruir_dato(void *, void destruir_dato_hash(void*)), void destruir_dato_hash(void*)){
	if(!lista) return DESTRUIR_LISTA_ERROR;

	void* elemento_a_borrar = NULL;
	while(!vacia(lista)){
		elemento_a_borrar = ultimo(lista);
		borrar(lista);
		if(destruir_dato != NULL) destruir_dato(elemento_a_borrar, destruir_dato_hash);
	}
	free(lista);

	return DESTRUIR_LISTA_OK;
}