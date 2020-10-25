/*
* @file: AllFunctions.c
* @author:
* @date: 19-10-2020
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
        printf("valor invalido.\n");
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
    struct timeval tv;
    time_t t;
    struct tm *info;
    char buffer[64];

    gettimeofday(&tv, NULL);
    t = tv.tv_sec;

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

/*        const char *message0= "ELO321 ";
        const char *message1= "Teoría de Sistemas Operativos ";
        const char *message2= "Departamento de Electrónica! \n";
*/
    int shm_fd;
    void *ptr;

    /* create the shared memory segment */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* configure the size of the shared memory segment */
    ftruncate(shm_fd, SIZE);

    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        return (void *) EXIT_FAILURE;
    }
    return ptr;
}

void W_shared_memory(void *ptr, char* str){
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

    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }

    /* now read from the shared memory region */
    printf("La lectura realizada desde la Región de la Memoria Compartida que fue creada corresponde a:\n");
    printf("%s\n",(char *)ptr);

    /* remove the shared memory segment */
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
        /*convert n into a str */
        int length = snprintf( NULL, 0, "%d", n );
        char* str = malloc( length + 1 );
        snprintf( str, length + 1, "%d", n );

        W_shared_memory(ptr,str);

        exit(0);
    }else if (pid>0){ /* codigo que ejecutara el parent process */
        wait(NULL);
        RD_shared_memory();
    }
}