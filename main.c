#include <stdio.h>
#include "AllFunctions.h"

int main(int argc, char **argv) {
    if (argc==2){
        int number = validation(argv[1]);
        printf("su numero elejido corresponde a %d\n",number);
        return 0;
    } else{
        return 1;
    }
}
