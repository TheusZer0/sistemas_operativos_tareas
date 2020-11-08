/*
* @file: AllFunctions.c
* @author: Robert Parra
 *
* @date: 11/10/2020
* @brief: realiza una validacion completa al dato introducido por comando
 * para determinar si puede convertirse en un entero positivo de tipo int,
 * en caso de fallar, el programa termina su ejecucion.
*/

#include <time.h>
#include <sys/time.h> /*declara la estructura timeval que se usara para definir el tiempo especifico de ejecucion*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include "AllFunctions.h"

//recibe el char como parametro para hacer la validacion
int validation(char *number){
    //hace la conversion para int, no para float del char que fue introducido por parametro
    int numb;
    numb = atoi(number);
    //condicional para determinar si el numero cumple con lo pedido
    if (numb<1){
        return EXIT_FAILURE; //retorna 1
    } else{
        return numb; //retorna el char convertido en numero
    }
}

void fork_process(){
    pid_t pid;
    pid = fork();

    if (pid==0){ /* codigo que ejecutara el child process */
        timeofday();
        exit(0);
    }else if (pid>0){ /* codigo que ejecutara el parent process */
        wait(NULL);
    }
}

void timeofday(){
    /* llamada al sistema con gettimeofday y localtime en base a el manual linux ma7 */
    struct timeval tv; /* struct sacada de la libreria */
    time_t t;
    struct tm *info;
    char buffer[64];

    gettimeofday(&tv, NULL); // llamada al sistema
    t = tv.tv_sec;

    /* print process */
    info = localtime(&t);
    printf("%s",asctime (info));
    strftime (buffer, sizeof buffer, "El dia corresponde a: %A, %B %d.\n", info);
    printf("%s",buffer);
    strftime (buffer, sizeof buffer, "La hora es: %I:%M %p.\n", info);
    printf("%s",buffer);
}

void* C_shared_memory(){
    const int SIZE = 4096;
    const char *name = "/shm-sucesion_Collatz";

    int shm_fd;
    void *ptr;

    /* crear el segmento de memoria compartida */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* configurar el largo del segmento de memoria compartida */
    ftruncate(shm_fd, SIZE);

    /* mapeo al segmento de memoria compartida */
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        return (void *) EXIT_FAILURE;
    }
    return ptr; /* retorna el mapeo para su facil uso */
}

void W_shared_memory(void *ptr, char* str){

    /* insertar numbs en la memoria compartida */

    int number = atoi(str);
    if (number == 1) {
        strcat(ptr, str);
    } else{
        strcat(ptr, str);
        strcat(ptr, ",");
    }
}

int RD_shared_memory(){
    const char *name = "/shm-sucesion_Collatz";
    const int SIZE = 4096;

    int shm_fd;
    void *ptr;

    /* open the shared memory segment */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        printf("shared memory failed\n");
        exit(-1);
    }

    /* volvemos a mapear el segmento de memoria compartida */
    ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }

    /* leemos el segmento de memoria compartida */
    printf("La lectura realizada desde la Región de la Memoria Compartida que fue creada corresponde a:\n");
    printf("%s\n",(char *)ptr);

    /* se elimina el segmento de memoria compartida */
    if (shm_unlink(name) == -1) {
        printf("Error removing %s\n",name);
        exit(-1);
    }

    return 0;
}

int sucesion_Collatz (unsigned int n){
    if (n % 2 == 0) {
        n = (n / 2);
    } else {
        n = (3 * n) + 1;
    }
    return n;
}

void fork_sucesion_Collatz(unsigned int n){
    pid_t pid;
    pid = fork();

    void* ptr = C_shared_memory();

    if (pid==0){ /* codigo que ejecutara el child process */
        do
        {
            /*convert n into a str */
            int length = snprintf( NULL, 0, "%d", n );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", n );

            W_shared_memory(ptr,str);

            n=sucesion_Collatz(n);

        }
        while(n != 1);
        /* convert n into a str */
        int length = snprintf( NULL, 0, "%d", n );
        char* str = malloc( length + 1 );
        snprintf( str, length + 1, "%d", n );

        W_shared_memory(ptr,str);

        exit(0);
    }else if (pid>0){ /* codigo que ejecutara el parent process */
        sleep(30);
        wait(NULL);
        RD_shared_memory();
    }
}