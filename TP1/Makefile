CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror
CFLAGS += -Wbad-function-cast
CFLAGS += -Wtype-limits -Wshadow -Wno-unused-variable
CFLAGS += -Wpointer-arith -Wunreachable-code -Wformat=2
CFLAGS += -pedantic

glider: conway
	./$< 5 10 10 $@

conway: conway.o matrix.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f conway *.pbm
