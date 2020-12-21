## Nombres:

- Robert Parra - ROL:201930022-9 - robert.parra@usm.cl
- Jared Soto - ROL:201604003-k - jared.soto@sansano.usm.cl

## MakeFile: como compilar los archivos:

#### Ejercicio 1:

OPT_GCC = -std=c99 -Wall -Wextra
OPT = -D_XOPEN_SOURCE=700
LIB = -lrt

all: program

program: shm-posix-consumidor.c
	gcc $(OPT_GCC) $(OPT) -o a.out main.c AllFunctions.c $(LIB)

run: a.out
	./a.out

clean:
	rm -f a.out

En resumen seria lo siguiente:
```
gcc -std=c99 -Wall -Wextra -D_XOPEN_SOURCE=700 -o a.out main.c AllFunctions.c -lrt
```

#### Ejercicio 2

OPT_GCC = -std=c99
LIB = -lpthread 

all: program

program: main.c
	gcc $(OPT_GCC) $(OPT) $(LIB) -o a.out main.c

run: a.out
	./a.out

clean:
	rm -f a.out

En resumen seria lo siguiente:
```
gcc -std=c99 -lpthread main.c
```