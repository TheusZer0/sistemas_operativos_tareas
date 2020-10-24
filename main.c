#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AllFunctions.h"

int main(int argc, char **argv) {
    //si se ingresa solo un comando mas aparte del ./program entonces cumple y ejecuta el programa
    if (argc==2){

        int number = validation(argv[1]); //arreglar bug, cuando retorna como numero 1

        fork_process();

        fork_sucesion_Collatz(number);

        void* ptr = C_shared_memory();
        W_shared_memory(ptr);
        RD_shared_memory();
        return 0;
    } else{ //caso contrario, si no cumple retorna 1
        return EXIT_FAILURE;
    }
}