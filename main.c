#include <stdio.h>

int main(int argc, char **argv) {
    printf("argc: %d\n",argc);
    if (argc==2){
        printf("argv %s\n",argv[0]);
        printf("argv %s\n",argv[1]);
    } else{
        return 0;
    }
    return 0;
}
