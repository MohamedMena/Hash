#include "hash.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int comparar(void* clave1, void* clave2){
	int* claveUno = clave1, *claveDos = clave2;
	if(*claveUno < *claveDos){
		return -1;
	}else if(*claveUno > *claveDos){
		return 1;
	}

	return 0;
}

int comparar_char(void* clave1, void* clave2){
	char* claveUno = clave1, *claveDos = clave2;
	return strcmp(claveUno, claveDos);
}

void liberar(void* elemento){
	free(elemento);
}

int obtener_posicion_random(int tamanio){
	return rand()%tamanio;
}

void swap_posiciones(long* pos1, long* pos2){
	long auxiliar = *pos1;
	*pos1 = *pos2;
	*pos2 = auxiliar;
}

void inicializar_arreglo(long* arreglo, int tamanio){
	for(int i = 0; i < tamanio; i++){
		arreglo[i] = obtener_posicion_random(1+tamanio*i*i);
	}
}

void desordenar_arreglo(long* arreglo, int tamanio){
	int pos_random;

	for (int i = 0 ; i < tamanio; i++){
		pos_random = obtener_posicion_random(tamanio);
		swap_posiciones(&arreglo[i], &arreglo[pos_random]);
	}
}

void pruebas_hash_sin_elementos(){
	printf(".:INICIO PRUEBAS HASH SIN ELEMENTOS:.\n");
	hash_t* hash = crear_hash(NULL);

	printf("Crear hash vacio: %s\n", (hash != NULL) ? "OK" : "ERROR");
	printf("El hash no contiene elementos: %s\n", cantidad(hash)==0 ? "OK" : "ERROR");
	printf("Existe clave 'A' es false, no existe en el hash: %s\n", !existe_clave(hash, "A") ? "OK" : "ERROR");
	printf("Obtener el elemento con clave 'A' es NULL, no existe en el hash: %s\n", obtener_elemento(hash, "A") == NULL ? "OK" : "ERROR");
	printf("Borrar clave 'A' es -1: %s\n", (quitar_elemento(hash, "A") == -1) ? "OK" : "ERROR");

	destruir_hash(hash);
	printf("\n");
}

void pruebas_hash_insertar_y_borrar(){
	printf(".:INICIO PRUEBAS GUARDAR/BORRAR ELEMENTOS HASH:.\n");
	hash_t* hash = crear_hash(NULL);
	int num6 = 6, num1 = 1;
	int num15 = 15, num4 = 4;
	int num10 = 10, num16 = 16;
	char* clave6 = "seis", *clave1 = "uno";
	char* clave15 = "quince", *clave4 = "cuatro";
	char* clave10 = "diez", *clave16 = "dieciseis";

	printf("Crear hash vacio: %s\n", (hash != NULL) ? "OK" : "ERROR");
	printf("Guardar clave 'seis', elemento '6': %s\n", (guardar_elemento(hash, clave6, &num6) == 0) ? "OK" : "ERROR");
	printf("El hash NO esta vacio: %s\n", cantidad(hash) == 1 ? "OK" : "ERROR");
	printf("Existe clave 'seis' es true, existe en el hash: %s\n", existe_clave(hash, clave6) ? "OK" : "ERROR");
	printf("Guardar clave 'uno', elemento '1': %s\n", (guardar_elemento(hash, clave1, &num1) == 0) ? "OK" : "ERROR");
	printf("Guardar clave 'quince', elemento '15': %s\n", (guardar_elemento(hash, clave15, &num15) == 0) ? "OK" : "ERROR");
	printf("Guardar clave 'cuatro', elemento '4': %s\n", (guardar_elemento(hash, clave4, &num4) == 0) ? "OK" : "ERROR");
	printf("Guardar clave 'diez', elemento '10': %s\n", (guardar_elemento(hash, clave10, &num10) == 0) ? "OK" : "ERROR");
	printf("Guardar clave 'dieciseis', elemento '16': %s\n", (guardar_elemento(hash, clave16, &num16) == 0) ? "OK" : "ERROR");

	printf("Existe clave 'uno' es true, existe en el hash: %s\n", existe_clave(hash, clave1) ? "OK" : "ERROR");
	printf("Existe clave 'quince' es true, existe en el hash: %s\n", existe_clave(hash, clave15) ? "OK" : "ERROR");
	printf("Existe clave 'cuatro' es true, existe en el hash: %s\n", existe_clave(hash, clave4) ? "OK" : "ERROR");
	printf("Existe clave 'diez' es true, existe en el hash: %s\n", existe_clave(hash, clave10) ? "OK" : "ERROR");
	printf("Existe clave 'dieciseis' es true, existe en el hash: %s\n", existe_clave(hash, clave16) ? "OK" : "ERROR");
	printf("La cantidad de claves guardadas es: %i\n", cantidad(hash));

	hash_iter_t* iter = crear_iterador(hash);
	int listados = 0;
	while(avanzar_iterador(iter)){
		listados++;
		const char* clave = elemento_actual(iter);
		printf("Clave: %s -- Elemento: %i\n", clave, *(int*)obtener_elemento(hash, clave));
	}
	hash_iterador_destruir(iter);

	printf("Cantidad de claves guardadas: %zu. Cantidad de claves listadas: %i -- %s\n", cantidad(hash), listados, (cantidad(hash)==listados)?"OK":"ERROR");

	printf("Borrar clave 'seis': %s\n", (quitar_elemento(hash, clave6) == 0) ? "OK" : "ERROR");
	printf("Existe clave 'seis' es false, no existe en el hash: %s\n", !existe_clave(hash, clave6) ? "OK" : "ERROR");

	printf("Borrar clave 'cuatro': %s\n", (quitar_elemento(hash, clave4) == 0) ? "OK" : "ERROR");
	printf("Existe clave 'cuatro' es false, no existe en el hash: %s\n", !existe_clave(hash, clave4) ? "OK" : "ERROR");

	printf("Borrar clave 'quince': %s\n", (quitar_elemento(hash, clave15) == 0) ? "OK" : "ERROR");
	printf("Existe clave 'quince' es false, no existe en el hash: %s\n", !existe_clave(hash, clave15) ? "OK" : "ERROR");

	printf("La cantidad de claves guardadas es: %i\n", cantidad(hash));

	iter = crear_iterador(hash);
	listados = 0;
	while(avanzar_iterador(iter)){
		listados++;
		const char* clave = elemento_actual(iter);
		printf("Clave: %s -- Elemento: %i\n", clave, *(int*)obtener_elemento(hash, clave));
	}
	printf("Cantidad de claves guardadas: %zu. Cantidad de claves listadas: %i -- %s\n", cantidad(hash), listados, (cantidad(hash)==listados)?"OK":"ERROR");

	hash_iterador_destruir(iter);
	printf("Borrar clave 'uno': %s\n", (quitar_elemento(hash, clave1) == 0) ? "OK" : "ERROR");
	printf("Existe clave 'uno' es false, no existe en el hash: %s\n", !existe_clave(hash, clave1) ? "OK" : "ERROR");
	printf("Borrar clave 'dieciseis': %s\n", (quitar_elemento(hash, clave16) == 0) ? "OK" : "ERROR");
	printf("Existe clave 'dieciseis' es false, no existe en el hash: %s\n", !existe_clave(hash, clave16) ? "OK" : "ERROR");
	printf("Borrar clave 'diez': %s\n", (quitar_elemento(hash, clave10) == 0) ? "OK" : "ERROR");
	printf("Existe clave 'diez' es false, no existe en el hash: %s\n", !existe_clave(hash, clave10) ? "OK" : "ERROR");

	printf("El hash esta vacio: %s\n", cantidad(hash) == 0 ? "OK" : "ERROR");

	destruir_hash(hash);
	printf("\n");
}
/*
void pruebas_abb_volumen(){
	printf(".:INICIO PRUEBAS DE VOLUMEN hash:.\n");
	abb_t* hash = crear_arbol(comparar, NULL);

	printf("Crear hash vacio: %s\n", (hash != NULL) ? "OK" : "ERROR");
	int tamanio_arreglo = 10000;

	long* arreglo_de_enteros = malloc(sizeof(int)*(size_t)tamanio_arreglo);
	bool se_agregaron_correctamente = true;
	srand((unsigned) time(NULL));
	inicializar_arreglo(arreglo_de_enteros, tamanio_arreglo);
	desordenar_arreglo(arreglo_de_enteros, tamanio_arreglo);

	int i = 0;
	while(i < tamanio_arreglo && se_agregaron_correctamente){
		se_agregaron_correctamente &= Guardar(hash, &arreglo_de_enteros[i]) == 0;
		i++;
	}

	printf("Se agregaron 10000 elementos correctamente: %s\n", se_agregaron_correctamente ? "OK" : "ERROR");
	printf("El hash NO esta vacio: %s\n", !vacio(hash) ? "OK" : "ERROR");

	bool se_eliminaron_correctamente = true;
	i = 0;
	while(i < tamanio_arreglo && se_eliminaron_correctamente){
		se_eliminaron_correctamente &= borrar(hash, &arreglo_de_enteros[i]) == 0;
		i++;
	}
	printf("Se eliminaron 10000 elementos correctamente: %s\n", se_eliminaron_correctamente ? "OK" : "ERROR");
	printf("El hash esta vacio: %s\n", vacio(hash) ? "OK" : "ERROR");

	destruir_arbol(hash);
	free(arreglo_de_enteros);
}*/

int main(){

	pruebas_hash_sin_elementos();
	pruebas_hash_insertar_y_borrar();
	//pruebas_abb_volumen();

	return 0;
}