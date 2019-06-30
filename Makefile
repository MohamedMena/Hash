CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
HEADERS = hash.h Lista/lista_se.h iterador.h
ZIPFILES = abb.c abb.h pruebas_mohamed.c README.txt tda_arbol.pdf minipruebas_abb.c
OBJ = hash.o Lista/lista_se.o Lista/iterador.o

EXEC = hash
FILENAME = $(EXEC)_MENA_95334_$(shell date +%Y%m%d).zip

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

%.o: %.c %.h Lista/%.c Lista/%.h
	$(CC) $(CFLAGS) -c $< 

build: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) pruebas_mohamed.c -o $(EXEC)

run: build
	./$(EXEC)

all: build
	valgrind $(VFLAGS) ./$(EXEC)

zip:
	zip $(FILENAME) $(ZIPFILES)

clean: 
	rm -f *.o $(EXEC) $(FILENAME)

