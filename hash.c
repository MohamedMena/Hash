#include "hash.h"
#include "Lista/lista_se.h"
#include "Lista/iterador.h"
#include <string.h>
#define CAPACIDAD_INICIAL 20
#define SE_PUDO_GUARDAR_OK 0
#define KO_NO_SE_GUARDO -1
#define KO_NO_SE_ELIMINO -1
#define SE_ELIMINO_OK 0
#define SE_DESTRUYO_OK 0
#define KO_NO_SE_DESTRUYO -1
#define FACTOR_DE_CARGA_AUMENTO 0.72
#define FACTOR_DE_CARGA_REDUCCION 0.5
#define HASH_CONSTANTE_DE_AUMENTO 3
#define HASH_CONSTANTE_DE_REDUCCION 2

struct hash{
	lista_se_t** tabla_hash;
	hash_destruir_dato_t destruir;
	size_t tamanio;
	size_t capacidad;
};

struct nodo_hash{
	char* clave;
	void* elemento;
};

struct hash_iter{
	size_t posicion_actual;
	const hash_t* hash;
	iterador_t* iterador_lista;
};

size_t hashing(const char* clave, size_t capacidad){
	unsigned long number = 5381;
	unsigned int c;
	while ((c = (unsigned int)*clave++)){
		number = ((number << 5) + number) + c;
	}
	return (size_t)(number % capacidad);
}

// Calcula el factor de carga
float hash_calcular_factor_de_carga(size_t cantidad, size_t capacidad) {
	return ((float)cantidad/(float)capacidad);
}

void eliminar_listas_del_hash(hash_t* hash){
	lista_se_t** tabla_vieja = hash->tabla_hash;

	for(int i = 0; i < hash->capacidad; i++){
		if(tabla_vieja[i] != NULL){
			destruir_lista(tabla_vieja[i], NULL, NULL);
		}
	}
	free(tabla_vieja);
}

void inicializar_tabla_hash(lista_se_t** tabla_hash, size_t tamanio){
	for(size_t i = 0; i < tamanio; i++){
		tabla_hash[i] = NULL;
	}
}


/* Funcion que redimensiona el hash, aumentando el tamanio de la tabla o 
 * disminuyendo sin superar el tamanio original*/ 
bool hash_redimensionar(hash_t* hash, size_t tamanio_nuevo){

	lista_se_t** tabla_nueva = calloc(tamanio_nuevo, sizeof(lista_se_t*));
	/* Si malloc devuelve NULL para la pedida de memoria de la nueva tabla
	 * o si el nuevo tamanio para redimensionar es menor al inicial 
	 * retornamos false*/
	if(tabla_nueva == NULL || tamanio_nuevo < CAPACIDAD_INICIAL){
		free(tabla_nueva);
		return false;
	}
	inicializar_tabla_hash(tabla_nueva, tamanio_nuevo);

	for(int i= 0; i < hash->capacidad; i++){
		if(hash->tabla_hash[i] != NULL){
			iterador_t* iterador = iter_lista_crear(hash->tabla_hash[i]);
			nodo_hash_t* nodo_actual = NULL;

			if(iterador == NULL) return false;

			while(!iter_lista_esta_al_final(iterador)){
				nodo_actual = iter_lista_elemento_actual(iterador);
				size_t nueva_posicion = hashing(nodo_actual->clave, tamanio_nuevo);
				/* Si en nueva posicion no tiene una lista la creo*/
				if(!tabla_nueva[nueva_posicion]){
					tabla_nueva[nueva_posicion] = crear_lista();
				}

				if(insertar(tabla_nueva[nueva_posicion], nodo_actual) == -1){
					iter_lista_destruir(iterador);
					return false;
				}
				iter_lista_avanzar(iterador);
			}
			iter_lista_destruir(iterador);
		}
	}
	/* Borro las listas vacias del hash viejo*/
	eliminar_listas_del_hash(hash);

	hash->tabla_hash = tabla_nueva;
	hash->capacidad = tamanio_nuevo;
	return true;
}

char *duplicar_clave(const char *clave){
	size_t largo = strlen(clave) + 1;
	char *dup_clave = malloc(sizeof(char)*largo);
	if(!dup_clave) return NULL;

	strcpy(dup_clave, clave);
	return dup_clave;
}

nodo_hash_t* crear_nodo_hash(const char* clave, void* elemento){
	nodo_hash_t* nuevo_nodo = malloc(sizeof(nodo_hash_t));
	if(!nuevo_nodo) return NULL;
	nuevo_nodo->clave = duplicar_clave(clave);
	nuevo_nodo->elemento = elemento;

	return nuevo_nodo;
}

void destruir_nodo_hash(void* nodo_hash, hash_destruir_dato_t destruir){

	nodo_hash_t* nodo_a_destruir = nodo_hash;
	if(destruir != NULL){
		destruir(nodo_a_destruir->elemento);
	}
	free(nodo_a_destruir->clave);

	free(nodo_a_destruir);
}

hash_t* crear_hash(hash_destruir_dato_t destruir_elemento){
	hash_t* nuevo_hash = malloc(sizeof(hash_t));
	if(!nuevo_hash) return NULL;

	lista_se_t** tabla_datos = malloc(sizeof(lista_se_t*)*CAPACIDAD_INICIAL);
	if(!tabla_datos){
		free(nuevo_hash);
		return NULL;
	}
	inicializar_tabla_hash(tabla_datos, CAPACIDAD_INICIAL);

	nuevo_hash->tabla_hash = tabla_datos;
	nuevo_hash->capacidad = CAPACIDAD_INICIAL;
	nuevo_hash->tamanio = 0;
	nuevo_hash->destruir = destruir_elemento;
	return nuevo_hash;
}

int guardar_elemento(hash_t* hash, const char* clave, void* elemento){
	if(!hash) return KO_NO_SE_GUARDO;

	//REDIMENSIONAR_HASH
	if (hash_calcular_factor_de_carga(hash->tamanio, hash->capacidad) > FACTOR_DE_CARGA_AUMENTO){
		if(!hash_redimensionar(hash, hash->capacidad * HASH_CONSTANTE_DE_AUMENTO) && hash->tamanio == hash->capacidad){
			return KO_NO_SE_GUARDO;
		}
	}

	nodo_hash_t* nuevo_elemento = crear_nodo_hash(clave, elemento);
	if(!nuevo_elemento) return KO_NO_SE_GUARDO;

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
	if(!hash->tabla_hash[posicion]) return KO_NO_SE_ELIMINO;

	iterador_t* iterador = iter_lista_crear(hash->tabla_hash[posicion]);
	if(!iterador) return KO_NO_SE_ELIMINO;

	nodo_hash_t* nodo_hash = NULL;
	bool elimino = false;
	while(!iter_lista_esta_al_final(iterador) &&  !elimino){
		nodo_hash = iter_lista_elemento_actual(iterador);
		if (strcmp(nodo_hash->clave, clave) == 0){
			elimino = iter_lista_borrar(iterador) != NULL;
		}
		iter_lista_avanzar(iterador);
	}
	iter_lista_destruir(iterador);

	if(!elimino) return KO_NO_SE_ELIMINO;
	destruir_nodo_hash(nodo_hash, hash->destruir);
	if(hash_calcular_factor_de_carga(hash->tamanio, hash->capacidad) < FACTOR_DE_CARGA_REDUCCION){
		hash_redimensionar(hash, hash->capacidad/HASH_CONSTANTE_DE_REDUCCION);
	}
	hash->tamanio--;
	return SE_ELIMINO_OK;
}

void* obtener_elemento(const hash_t* hash, const char* clave){
	if(!hash) return NULL;

	size_t posicion = hashing(clave, hash->capacidad);
	if(!hash->tabla_hash[posicion]) return NULL;

	iterador_t* iterador = iter_lista_crear(hash->tabla_hash[posicion]);
	if(!iterador) return NULL;

	nodo_hash_t* nodo_hash = NULL;
	bool encontro = false;
	while(!iter_lista_esta_al_final(iterador) &&  !encontro){
		nodo_hash = iter_lista_elemento_actual(iterador);
		encontro = strcmp(nodo_hash->clave, clave) == 0;
		iter_lista_avanzar(iterador);
	}
	iter_lista_destruir(iterador);

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

	for (size_t i = 0; i < hash->capacidad; ++i){
		if(hash->tabla_hash[i] != NULL){
			destruir_lista(hash->tabla_hash[i], destruir_nodo_hash, hash->destruir);
		}
	}
	free(hash->tabla_hash);
	free(hash);

	return SE_DESTRUYO_OK;
}

size_t buscar_siguiente_posicion(lista_se_t** tabla_hash, size_t capacidad, size_t posicion_actual){
	size_t siguiente_pos = capacidad;

	bool hay_siguiente = false;
	while(!hay_siguiente && posicion_actual < capacidad){
		hay_siguiente = tabla_hash[posicion_actual] != NULL && !vacia(tabla_hash[posicion_actual]);
		if(hay_siguiente){
			siguiente_pos = posicion_actual;
		}
		posicion_actual++;
	}

	return siguiente_pos;
}

hash_iter_t* crear_iterador(const hash_t* hash){
	hash_iter_t* iterador_hash = malloc(sizeof(hash_iter_t));
	if(!iterador_hash) return NULL;

	iterador_hash->posicion_actual = hash->capacidad;
	iterador_hash->hash = hash;
	iterador_hash->iterador_lista = NULL;
	return iterador_hash;
}

bool avanzar_iterador(hash_iter_t* iterador){
	if(!iterador) return false;

	if((iterador->posicion_actual == iterador->hash->capacidad) && (!iterador->iterador_lista)){
		size_t siguiente_pos = buscar_siguiente_posicion(iterador->hash->tabla_hash, iterador->hash->capacidad, 0);
		iterador->iterador_lista = iter_lista_crear(iterador->hash->tabla_hash[siguiente_pos]);
		iterador->posicion_actual = siguiente_pos;
		return true;
	}
	iter_lista_avanzar(iterador->iterador_lista);

	if(iter_lista_esta_al_final(iterador->iterador_lista)){
		size_t siguiente_pos = buscar_siguiente_posicion(iterador->hash->tabla_hash, iterador->hash->capacidad, iterador->posicion_actual+1);
		if(siguiente_pos == iterador->hash->capacidad) return false;
		iter_lista_destruir(iterador->iterador_lista);
		iterador->iterador_lista = iter_lista_crear(iterador->hash->tabla_hash[siguiente_pos]);
		iterador->posicion_actual = siguiente_pos;
	}
	return true;
}

const char* elemento_actual(const hash_iter_t* iterador){
	if(!iterador) return NULL;
	if(iter_lista_esta_al_final(iterador->iterador_lista)) return NULL;

	nodo_hash_t* nodo_hash = iter_lista_elemento_actual(iterador->iterador_lista);
	return nodo_hash->clave;
}

bool esta_al_final(const hash_iter_t* iterador){
	size_t siguiente_pos = buscar_siguiente_posicion(iterador->hash->tabla_hash, iterador->hash->capacidad, iterador->posicion_actual+1);
	if(iter_lista_esta_al_final(iterador->iterador_lista) && siguiente_pos == iterador->hash->capacidad) return true;

	return false;
}

int hash_iterador_destruir(hash_iter_t* iterador){
	if(!iterador) return KO_NO_SE_DESTRUYO;

	iter_lista_destruir(iterador->iterador_lista);
	free(iterador);

	return SE_DESTRUYO_OK;
}