#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AllFunctions.h"

int main(int argc, char **argv) {
    //si se ingresa solo un comando mas aparte del ./program entonces cumple y ejecuta el programa
    if (argc==2){
        int number = validation(argv[1]); //arreglar bug, cuando retorna como numero 1
        fork_process();
        int x = sucesion_Collatz(number);
        printf("%d\n",x);
        return 0;
    } else{ //caso contrario, si no cumple retorna 1
        return EXIT_FAILURE;
    }
}