# Memoria caché asociativa por conjuntos de 4 vías

```
$ make
gcc -g -std=c99 -Wall -Werror -Wbad-function-cast -Wtype-limits -Wshadow -Wno-unused-variable -Wpointer-arith -Wunreachable-code -Wformat=2 -pedantic main.c cache.h cache.c -o cache
./cache pruebas/prueba1.mem
INIT
WRITE: 0 <- 255
WRITE: 1024 <- 254
WRITE: 2048 <- 248
WRITE: 4096 <- 96
WRITE: 8192 <- 192
READ: 0 -> 255
READ: 1024 -> 254
READ: 2048 -> 248
READ: 8192 -> 192
MISS_RATE: 100.00%
./cache pruebas/prueba2.mem
INIT
READ: 0 -> 0
READ: 127 -> 0
WRITE: 128 <- 10
READ: 128 -> 10
WRITE: 128 <- 20
READ: 128 -> 20
MISS_RATE: 50.00%
./cache pruebas/prueba3.mem
INIT
WRITE: 128 <- 1
WRITE: 129 <- 2
WRITE: 130 <- 3
WRITE: 131 <- 4
READ: 1152 -> 0
READ: 2176 -> 0
READ: 3200 -> 0
READ: 4224 -> 0
READ: 128 -> 1
READ: 129 -> 2
READ: 130 -> 3
READ: 131 -> 4
MISS_RATE: 75.00%
./cache pruebas/prueba4.mem
INIT
WRITE: 0 <- 255
WRITE: 1 <- 2
WRITE: 2 <- 3
WRITE: 3 <- 4
WRITE: 4 <- 5
READ: 0 -> 255
READ: 1 -> 2
READ: 2 -> 3
READ: 3 -> 4
READ: 4 -> 5
READ: 4096 -> 0
READ: 8192 -> 0
READ: 2048 -> 0
READ: 1024 -> 0
READ: 0 -> 255
READ: 1 -> 2
READ: 2 -> 3
READ: 3 -> 4
READ: 4 -> 5
MISS_RATE: 57.89%
./cache pruebas/prueba5.mem
INIT
ERR: ADDR_TOO_BIG [131072]
READ: 4096 -> 0
READ: 8192 -> 0
READ: 4096 -> 0
READ: 0 -> 0
READ: 4096 -> 0
MISS_RATE: 60.00%
./cache pruebas/prueba6.mem
INIT
WRITE: 0 <- 1
WRITE: 1024 <- 2
WRITE: 2048 <- 3
WRITE: 4096 <- 4
WRITE: 8192 <- 0
READ: 0 -> 1
READ: 1024 -> 2
READ: 2048 -> 3
READ: 4096 -> 4
READ: 8192 -> 0
MISS_RATE: 100.00%
```
