//
// Created by theuszero on 10/19/20.
//
#include <time.h>
#include <sys/time.h> /*declara la estructura timeval que se usara para definir el tiempo especifico de ejecucion*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
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