#include "hash.h"
#include "Lista/lista_se.h"
#define CAPACIDAD_INICIAL 20
#define SE_PUDO_GUARDAR_OK 0
#define KO_NO_SE_GUARDO -1
#define KO_NO_SE_ELIMINO -1
#define SE_ELIMINO_OK 0
#define SE_DESTRUYO_OK 0
#define KO_NO_SE_DESTRUYO -1

struct hash{
	void** tabla_hash;
	hash_destruir_dato_t destruir;
	size_t tamanio;
	size_t capacidad;
}

struct nodo_hash_t{
	const char* clave;
	void* elemento;
}

size_t hashing(const char* clave, size_t capacidad){
//TODO
}

nodo_hash_t* crear_nodo_hash(const char* clave, void* elemento){
	nodo_hash_t* nuevo_nodo = malloc(sizeof(nodo_hash_t));
	if(!nuevo_nodo) return NULL;

	strcpy(nuevo_nodo->clave, clave);
	nuevo_nodo->elemento = elemento;

	return nuevo_nodo;
}

void destruir_nodo_hash(void* nodo_hash, hash_destruir_dato_t destruir){

	if(destruir != NULL){
		destruir(nodo_hash->elemento);
	}

	free(nodo_hash);
}

hash_t* crear_hash(hash_destruir_dato_t destruir_elemento){
	hash_t* nuevo_hash = malloc(sizeof(hash_t));
	if(!nuevo_hash) return NULL;

	void** tabla_datos = malloc(sizeof(void*)*CAPACIDAD_INICIAL);
	if(!tabla_datos){
		free(nuevo_hash);
		return NULL;
	}

	nuevo_hash->tabla_hash = tabla_datos;
	nuevo_hash->capacidad = CAPACIDAD_INICIAL;
	nuevo_hash->tamanio = 0;
	return nuevo_hash;
}

int guardar_elemento(hash_t* hash, const char* clave, void* elemento){
	if(!hash) return KO_NO_SE_GUARDO;

	nodo_hash_t* nuevo_elemento = crear_nodo_hash(clave, elemento);
	if(!nuevo_elemento) return KO_NO_SE_GUARDO;

	//REDIMENSIONAR_HASH
	size_t posicion = hashing(clave, hash->capacidad);
	if(!hash->tabla_hash[posicion]){
		hash->tabla_hash[posicion] = crear_lista();
		if(!hash->tabla_hash[posicion]){
			free(nuevo_elemento);
			return KO_NO_SE_GUARDO;
		}
	}
	insertar(hash->tabla_hash[posicion], nuevo_elemento);
	hash->tamanio++;

	return SE_PUDO_GUARDAR_OK;
}

int quitar_elemento(hash_t* hash, const char* clave){
	if(!hash) return KO_NO_SE_ELIMINO;

	size_t posicion = hashing(clave, hash->capacidad);
	if(!hash->tabla_hash[posicion]) return NULL;

	iterador_t* iterador = crear(hash->tabla_hash[posicion]);
	if(!iterador) return NULL;

	nodo_hash_t* nodo_hash = NULL;
	bool elimino = false;
	while(!iter_esta_al_final(iterador) &&  !elimino){
		nodo_hash = elemento_actual(iterador);
		if (strcmp(nodo_hash->clave, clave) == 0){
			elimino = iter_borrar(iterador) != NULL;
		}
		avanzar(iterador);
	}

	if(!elimino) return KO_NO_SE_ELIMINO;

	return SE_ELIMINO_OK;
}

void* obtener_elemento(const hash_t* hash, const char* clave){
	if(!hash) return NULL;

	size_t posicion = hashing(clave, hash->capacidad);
	if(!hash->tabla_hash[posicion]) return NULL;

	iterador_t* iterador = crear(hash->tabla_hash[posicion]);
	if(!iterador) return NULL;

	nodo_hash_t* nodo_hash = NULL;
	bool encontro = false;
	while(!iter_esta_al_final(iterador) &&  !encontro){
		nodo_hash = elemento_actual(iterador);
		encontro = strcmp(nodo_hash->clave, clave) == 0;
		avanzar(iterador);
	}

	if(!encontro) return NULL;

	return nodo_hash->elemento;
}

bool existe_clave(const hash_t* hash, const char* clave){
	return obtener_elemento(hash, clave) != NULL;
}

size_t cantidad(const hash_t* hash){
	return hash->tamanio;
}

int destruir_hash(hash_t* hash){
	if(!hash) return KO_NO_SE_DESTRUYO;

	for (size_t i = 0; i < hash->tamanio; ++i){
		if(hash->tabla_hash[i] != NULL){
			destruir_lista(hash->tabla_hash[i], destruir_nodo_hash, hash->destruir);
		}
	}
	free(hash->tabla_hash);
	free(hash);

	return SE_DESTRUYO_OK;
}