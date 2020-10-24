//
// Created by theuszero on 10/19/20.
//
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

    if (pid==0){ /* child process */
        printf("el valor de este hijo es: %d\n y del padre es: %d\n",getpid(),getppid());
        exit(0);
    }else if (pid>0){
        wait(NULL);
        printf("el valor del padre es: %d\n ",getpid());
    }
}