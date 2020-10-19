#include <stdio.h>
#include "AllFunctions.h"

int main(int argc, char **argv) {
    if (argc==2){
        validation(argv);
        return 0;
    } else{
        return 1;
    }
}
