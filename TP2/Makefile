CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror
CFLAGS += -Wbad-function-cast
CFLAGS += -Wtype-limits -Wshadow -Wno-unused-variable
CFLAGS += -Wpointer-arith -Wunreachable-code -Wformat=2
CFLAGS += -pedantic

all: build
	./cache pruebas/prueba1.mem
	./cache pruebas/prueba2.mem
	./cache pruebas/prueba3.mem
	./cache pruebas/prueba4.mem
	./cache pruebas/prueba5.mem
	./cache pruebas/prueba6.mem

build: main.c cache.h cache.c
	$(CC) $(CFLAGS) $^ -o cache
