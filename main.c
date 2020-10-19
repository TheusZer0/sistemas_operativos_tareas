#include <stdio.h>
#include "AllFunctions.h"

int main(int argc, char **argv) {
    if (argc==2){
        printf("this is %s \n",argv[1]);
        return 0;
    } else{
        return 1;
    }
}
