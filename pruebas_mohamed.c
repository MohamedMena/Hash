#include "hash.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

void liberar(void* elemento){
	free(elemento);
}

void destruir_arreglo(char** arreglo_de_claves, size_t tamanio){
	for(size_t i = 0; i < tamanio; i++){
		free(arreglo_de_claves[i]);
	}

	free(arreglo_de_claves);
}

void inicializar_arreglo(long* arreglo, int tamanio){
	for(int i = 0; i < tamanio; i++){
		arreglo[i] = i;
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
	printf("\n");
	hash_iter_t* iter = crear_iterador(hash);
	int listados = 0;
	while(avanzar_iterador(iter)){
		listados++;
		const char* clave = elemento_actual(iter);
		printf("Clave: %s -- Elemento: %i\n", clave, *(int*)obtener_elemento(hash, clave));
	}
	hash_iterador_destruir(iter);

	printf("Cantidad de claves guardadas: %zu. Cantidad de claves listadas: %i -- %s\n", cantidad(hash), listados, (cantidad(hash)==listados)?"OK":"ERROR");
	printf("\n");
	printf("Borrar clave 'seis': %s\n", (quitar_elemento(hash, clave6) == 0) ? "OK" : "ERROR");
	printf("Existe clave 'seis' es false, no existe en el hash: %s\n", !existe_clave(hash, clave6) ? "OK" : "ERROR");

	printf("Borrar clave 'cuatro': %s\n", (quitar_elemento(hash, clave4) == 0) ? "OK" : "ERROR");
	printf("Existe clave 'cuatro' es false, no existe en el hash: %s\n", !existe_clave(hash, clave4) ? "OK" : "ERROR");

	printf("Borrar clave 'quince': %s\n", (quitar_elemento(hash, clave15) == 0) ? "OK" : "ERROR");
	printf("Existe clave 'quince' es false, no existe en el hash: %s\n", !existe_clave(hash, clave15) ? "OK" : "ERROR");

	printf("La cantidad de claves guardadas es: %i\n", cantidad(hash));
	printf("\n");
	iter = crear_iterador(hash);
	listados = 0;
	while(avanzar_iterador(iter)){
		listados++;
		const char* clave = elemento_actual(iter);
		printf("Clave: %s -- Elemento: %i\n", clave, *(int*)obtener_elemento(hash, clave));
	}
	printf("Cantidad de claves guardadas: %zu. Cantidad de claves listadas: %i -- %s\n", cantidad(hash), listados, (cantidad(hash)==listados)?"OK":"ERROR");
	printf("\n");
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

void pruebas_hash_volumen(){
	printf(".:INICIO PRUEBAS DE VOLUMEN HASH:.\n");
	hash_t* hash = crear_hash(NULL);

	printf("Crear hash vacio: %s\n", (hash != NULL) ? "OK" : "ERROR");
	size_t tamanio_arreglo = 10000;

	long* arreglo_de_enteros = malloc(sizeof(int)*tamanio_arreglo);
	char** arreglo_de_claves = malloc(sizeof(char*)*tamanio_arreglo);
	bool se_agregaron_correctamente = true;
	inicializar_arreglo(arreglo_de_enteros, (int)tamanio_arreglo);

	int i = 0;
	while(i < tamanio_arreglo && se_agregaron_correctamente){
		arreglo_de_claves[i] = malloc(sizeof(char)*10);
		sprintf(arreglo_de_claves[i], "%05d", i);
		se_agregaron_correctamente &= guardar_elemento(hash, arreglo_de_claves[i], &arreglo_de_enteros[i]) == 0;
		i++;
	}

	printf("Se agregaron 10000 elementos correctamente: %s\n", se_agregaron_correctamente ? "OK" : "ERROR");
	printf("El hash NO esta vacio: %s\n", cantidad(hash) == 10000 ? "OK" : "ERROR");

	bool se_eliminaron_correctamente = true;
	i = 0;
	while(i < tamanio_arreglo && se_eliminaron_correctamente){
		se_eliminaron_correctamente &= quitar_elemento(hash, arreglo_de_claves[i]) == 0;
		i++;
	}
	printf("Se eliminaron 10000 elementos correctamente: %s\n", se_eliminaron_correctamente ? "OK" : "ERROR");
	printf("El hash esta vacio: %s\n", cantidad(hash)==0 ? "OK" : "ERROR");

	destruir_hash(hash);
	destruir_arreglo(arreglo_de_claves, tamanio_arreglo);
	free(arreglo_de_enteros);
}

static void prueba_hash_iterar(){
	printf(".:INICIO PRUEBAS DE ITERADOR HASH:.\n");
	hash_t* hash = crear_hash(NULL);

	char *claves[] = {"AC123BD", "OPQ976", "A421ACB"};
	char *valores[] = {"Auto de Mariano", "Auto de Lucas", "Moto de Manu"};

	printf("Guardar clave 'AC123BD', elemento 'Auto de Mariano': %s\n", (guardar_elemento(hash, claves[0], valores[0]) == 0) ? "OK" : "ERROR");
	printf("Guardar clave 'OPQ976', elemento 'Auto de Lucas': %s\n", (guardar_elemento(hash, claves[1], valores[1]) == 0) ? "OK" : "ERROR");
	printf("Guardar clave 'A421ACB', elemento 'Moto de Manu': %s\n", (guardar_elemento(hash, claves[2], valores[2]) == 0) ? "OK" : "ERROR");

	hash_iter_t* iter = crear_iterador(hash);
	avanzar_iterador(iter);
	printf("Iterador esta al final, es false: %s\n", !esta_al_final(iter) ? "OK" : "ERROR");

	printf("Iterador elemento actual, es: %s\n", elemento_actual(iter));
	printf("Iterador avanzar es true: %s\n", avanzar_iterador(iter)? "OK" : "ERROR");
	printf("Iterador esta al final, es false %s\n", !esta_al_final(iter)? "OK" : "ERROR");

	printf("Iterador elemento actual, es: %s\n", elemento_actual(iter));
	printf("Iterador avanzar es true: %s\n", avanzar_iterador(iter) ? "OK" : "ERROR");
	printf("Iterador esta al final, es false %s\n", !esta_al_final(iter) ? "OK" : "ERROR");

	printf("Iterador elemento actual, es: %s\n", elemento_actual(iter));
	printf("Iterador avanzar es false: %s\n", !avanzar_iterador(iter)? "OK" : "ERROR");
	printf("Iterador esta al final, es true %s\n", esta_al_final(iter)? "OK" : "ERROR");

	printf("Iterador ver actual, es NULL: %s\n", !elemento_actual(iter) ? "OK" : "ERROR");
	printf("Iterador avanzar es false: %s\n", !avanzar_iterador(iter) ? "OK" : "ERROR");
	printf("Iterador esta al final, es true: %s\n", esta_al_final(iter) ? "OK" : "ERROR");

	hash_iterador_destruir(iter);
	destruir_hash(hash);
}

int main(){

	pruebas_hash_sin_elementos();
	pruebas_hash_insertar_y_borrar();
	pruebas_hash_volumen();
	prueba_hash_iterar();

	return 0;
}