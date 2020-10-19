//
// Created by theuszero on 10/19/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AllFunctions.h"

//recibe el char como parametro para hacer la validacion
int validation(char *number){
    //hace la conversion para int, no para float del char que fue introducido por parametro
    int numb;
    numb = atoi(number);
    if (numb<1){
        printf("valor invalido.\n");
        return EXIT_FAILURE;
    } else{
        return numb; //retorna el char convertido en numero
    }
}