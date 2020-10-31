#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int numArray [50];

float avg_value;
int min_value;
int max_value;

pthread_t ID1, ID2, ID3;

void insert_numArray();
void* return_avg(void* null);
void* return_min(void* null);
void* return_max(void* null);

void main(){

    insert_numArray();
    pthread_t tid[3];
    pthread_attr_t attr[3];
    /* se crean los 3 thread*/
    pthread_attr_init(&attr[0]);
    pthread_create(&tid[0], &attr[0], return_avg, NULL);

    pthread_attr_init(&attr[1]);
    pthread_create(&tid[1], &attr[1], return_min, NULL);

    pthread_attr_init(&attr[2]);
    pthread_create(&tid[2], &attr[2], return_max, NULL);
    /*se espera su ejecucion*/
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);

    pthread_t threadID[3] = {ID1, ID2, ID3};

    printf(" Thread ID: %lu calculó promedio y su valor es %f.\n Thread ID: %lu calculó mínimo y su valor es %d.\n Thread ID: %lu calculó máximo y su valor es %d.\n",threadID[0],avg_value,threadID[1],min_value,threadID[2],max_value);
    printf("\n\n%lu\n%lu",ID1,ID2);
}


void insert_numArray()
{
    int numb;
    srand(time(0));

    for(int i = 0; i<50; i++){
        numb=rand()%100;
        if ((numb>0)&&(numb<=100)){
            numArray[i]=numb;
        }else{
            --i;
        }
    }
}

void* return_avg(void* null){
    ID1 = pthread_self();
    float count = 0;
    for (int i = 0; i < 50; ++i) {
        count = count+numArray[i];
    }
    count=count/50;
    avg_value=count;
    return null;
}

void* return_min(void* null){
    ID2 = pthread_self();
    int c, location = 0;

    for (c = 1; c < 50; c++)
        if (numArray[c] < numArray[location])
            location = c;
    min_value = numArray[location];
    return 0;
}

void* return_max(void* null){
    ID3 = pthread_self();
    int location = 0;
    for (int i = 0; i < 50; ++i) {
        if (numArray[i] > numArray[location])
            location = i;
    }
    max_value = numArray[location];
}