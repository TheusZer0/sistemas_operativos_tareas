/*
* @file: main.c
* @author: Robert Parra
*          Jared Soto
* @date: 11/10/2020
* @brief:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AllFunctions.h"

int main(int argc, char **argv) {
    //si se ingresa solo un comando mas aparte del ./program entonces cumple y ejecuta el programa
    if (argc==2){

        int number = validation(argv[1]); //arreglar bug, cuando retorna como numero 1

        if (number==1){
            printf("valor invalido.\n");
        }else{
            fork_process();
            fork_sucesion_Collatz(number);
        }
        return 0;
    } else{ //caso contrario, si no cumple retorna 1
        printf("ingreso un parametro mas por la linea de comandos, esto es invalido.\n");
        return EXIT_FAILURE;
    }
}