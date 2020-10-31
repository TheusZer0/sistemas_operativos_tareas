//
// Created by theuszero on 10/30/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int numArray [50];

float avg_value;
int min_value;
int max_value;

void insert_numArray();
void* return_Avg(void* null);
void* return_Min(void* null);
void* return_Max(void* null);

int main(int argc, char **argv){

    insert_numArray(); //creacion del array

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, return_Avg, argv);
    pthread_join(tid,NULL);

    printf("\n%f\n",avg_value);


    return 0;
}

void insert_numArray()
{
    int numb;
    // Use current time as seed for random generator
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

void* return_Avg(void* null){
    float count = 0;
    for (int i = 0; i < 50; ++i) {
        count = count+numArray[i];
    }
    count=count/50;
    avg_value=count;
    return null;
}

void* return_Min(void* null){
    int c, location = 0;

    for (c = 1; c < 50; c++)
        if (numArray[c] < numArray[location])
            location = c;
    min_value = numArray[location];
    return 0;
}

void* return_Max(void* null){
    int location = 0;
    for (int i = 0; i < 50; ++i) {
        if (numArray[i] > numArray[location])
            location = i;
    }
    max_value = numArray[location];
}