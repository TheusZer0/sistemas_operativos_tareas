#include <stdio.h>
#include "AllFunctions.h"

int main(int argc, char **argv) {
    if (argc==2){
        int number = validation(argv[1]); //arreglar bug, cuando retorna como numero 1
        return 0;
    } else{
        return 1;
    }
}
