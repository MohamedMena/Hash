# README TDA HASH
# Alumno: Mohamed Mena
# Padron: 95334
# Algoritmos II - Mendez

# Detalle de la entrega:
Se entrega una implementación en lenguaje C del TDA Hash usando un vector dinámico de punteros a Lista como estructura de almacenamiento de los datos.
Para esto se creó un struct nodo_hash_t, que se compone de la clave y el dato a guardar en el Hash;

Para aprovechar el espacio de la tabla de hash ésta se comporta como un vector dinámico, el cual se redimensiona a traves de las funciones internas:
'hash_redimensionar'y 'hash_calcular_factor_de_carga'.
La primera tiene como fin el ajuste del tamanio del vector de datos de acuerdo a la capacidad en uso.
La segunda calcula el factor de carga del hash, que es la razón entre el tamanio ocupado/capacidad total del hash. El factor de carga va entre 0 y 1.
La capacidad inicial de la tabla_hash es de 20 elementos.

Como criterio de redimension se toma lo siguiente:
-AUMENTAR TAMANIO cuando la tabla_hash se llena por encima al 75% (factor de carga > 0.75) y se quiere guardar un nuevo elemento, en este caso el nuevo tamanio será del triple del tamanio actual.
-REDUCIR TAMANIO cuando se borra un elemento y la tabla_hash esta llena por debajo del 50% (factor de carga < 0.5) de la capacidad, en este caso el nuevo tamanio será la mitad del actual.

Se adjunta también un set de pruebas para verificar el correcto funcionamiento de las primitivas del TDA.

pruebas_hash_sin_elementos()
  Se crea un hash y se verifica que esté vacío inicialmente, se prueba que al llamar a borrar o obtener algun elemento del hash el programa 
  responde sin fallas devolviendo el resultado correspondiente.

pruebas_hash_insertar_y_borrar()
  Se crean 6 elementos del tipo entero con sus respectivas claves y se procede a hacer repetidas operaciones de insercion, 
  consultando en cada paso que los elementos se hayan cargado correctamente y una vez insertados se recorre el hash usando un iterador.
  Después se realizan operaciones de borrado de los elementos, controlando en cada paso que al consultar por clave no existan en el hash.

pruebas_hash_volumen()
  Se crea un hash y se procede a cargarlo con 10000 elementos del tipo entero controlando al final que todos y cada uno de los elementos se hayan 
  cargado correctamente y validando que el hash no esté vacío al terminar la carga.
  A continuación se borran todos los elementos verificando que se hayan eliminado correctamente y quedando el hash vacío.
  Finalmente se consulta que el hash haya regresado al estado inicial (vacío).

prueba_hash_iterar()
 Se crea un hash y se lo carga con 3 elementos para luego recorrerlo usando un iterador, consultando en cada paso la clave en la posicion del iterador, si se pudo avanzar o se llegó al final del hash.

# Linea de compilacion:
gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 hash.o Lista/lista_se.o Lista/iterador.o pruebas_mohamed.c -o hash

# Linea de valgrind:
  valgrind --leak-check=full --track-origins=yes --show-reachable=yes hash

# Linea de ejecucion:
./hash
