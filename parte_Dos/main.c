/*
* @file: main.c
* @author: Robert Parra
*          Jared Soto
* @date: 11/10/2020
* @brief: Código para tarea 01 en ELO 321, semestre 2020-2
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int numArray [50]; //arreglo de numeros al azar

float avg_value;
int min_value;
int max_value;

pthread_t ID1, ID2, ID3;

/**
 * @brief        : función que recorre el array de datos insertando en este
 * números al azar desde el 1 al 100, en total son 50 números que serán ingresados
 * al arreglo
 */
void insert_numArray();

/**
 * @brief        : realiza el cálculo del valor promedio que contiene el array
 * global llamado numArray.
 */
void* return_avg(void* null);

/**
 * @brief        : realiza el cálculo del valor mínimo que contiene el array.
 * global llamado numArray.
 */
void* return_min(void* null);

/**
 * @brief        : realiza el cálculo del valor máximo que contiene el array.
 * global llamado numArray.
 */
void* return_max(void* null);

void main(){

    insert_numArray();
    pthread_t tid[3];
    pthread_attr_t attr[3];
    
    /* se inicializan las variables con valores estándar para el thread*/
    pthread_attr_init(&attr[0]);
    pthread_attr_init(&attr[1]);
    pthread_attr_init(&attr[2]);
    
    /* se crean los thread*/
    pthread_create(&tid[0], &attr[0], return_avg, NULL);
    pthread_create(&tid[1], &attr[1], return_min, NULL);    
    pthread_create(&tid[2], &attr[2], return_max, NULL);
    
    /*se espera a que cada thread termine su ejecución*/
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    
    /* se guardan los ID en un arreglo*/
    pthread_t threadID[3] = {ID1, ID2, ID3};

    printf(" Thread ID: %lu calculó promedio y su valor es %f.\n Thread ID: %lu calculó mínimo y su valor es %d.\n Thread ID: %lu calculó máximo y su valor es %d.\n",threadID[0],avg_value,threadID[1],min_value,threadID[2],max_value);
}


void insert_numArray()
{
    int numb;
    srand(time(0)); // Es una función que permite que con cada ejecución del programa, se obtengan números random.

    for(int i = 0; i<50; i++){
        numb=rand()%100;
        if ((numb>0)&&(numb<=100)){
            numArray[i]=numb;
        }else{
            --i;
        }
    }
}

void* return_avg(void* ptr_avg_value){
    ID1 = pthread_self();  // obtiene el ID del thread que realiza esta función.
    float *avg_value;
    avg_value = (float *)ptr_avg_value;  // asigna el puntero de la varibale que queremos cambiar.
    float count = 0;
    for (int i = 0; i < 50; ++i) {
        count = count+numArray[i];
    }
    count=count/50;
    *avg_value=count;
}

void* return_min(void* ptr_min_value){
    ID2 = pthread_self(); // obtiene el ID del thread que realiza esta función.
    int *min_value;
    min_value = (int *)ptr_min_value; // asigna el puntero de la varibale que queremos cambiar.
    int c, location = 0;

    for (c = 1; c < 50; c++)
        if (numArray[c] < numArray[location])
            location = c;
    *min_value = numArray[location];
    return 0;
}

void* return_max(void* ptr_max_value){
    ID3 = pthread_self();  // obtiene el ID del thread que realiza esta función.
    int *max_value;
    max_value = (int *)ptr_max_value; // asigna el puntero de la varibale que queremos cambiar.
    int location = 0;
    for (int i = 0; i < 50; ++i) {
        if (numArray[i] > numArray[location])
            location = i;
    }
    *max_value = numArray[location];
}
