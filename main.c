#include <stdio.h>

int main(int argc, char *argv[1]) {
    for (int i = 0; i < 2; ++i) {
        printf("argumento %d, %s \n",i,argv[i]);
    }
    return 0;
}
