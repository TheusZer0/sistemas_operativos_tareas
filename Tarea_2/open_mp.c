/*
* @file: main.c
* @author: Jared Soto
 * Robert Parra
* @date: 24/12/2020
* @brief: Código para tarea 02 en ELO 321, semestre 2020-2
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <omp.h>

typedef struct
{
    int init_row; // fila inicial
    int fin_row; // fila final
    int init_col; // columna inicial
    int fin_col; // columna final
}sdk;

/**
 * @brief        : realiza una medicion del tiempo empleado segun la ejecucion de codigo
 * @return       : retorna un double que corresponde al tiempo en Segundos que demoro el codigo
 */
double sub_main();

/**
 * @brief        : realiza una validacion completa al sudoku, entregando un resultado de 1 si es valido con un respectivo mensaje y si no es valido, entrega un valor de 0.
 * @param void*: puntero que finalmente apuntara a una struct
 */
void *validity_check(void*); //chequea solucion de sudoku

/**
 * @brief        : realiza una validacion completa a la columna del sudoku, entregando un resultado de 1 si es valido con un respectivo mensaje y si no es valido, entrega un valor de 0.
 * @param void*: puntero que finalmente apuntara a una struct
 */
void *col_check(void*);  // chequea columnas

/**
 * @brief        : realiza una validacion completa a la fila del sudoku, entregando un resultado de 1 si es valido con un respectivo mensaje y si no es valido, entrega un valor de 0.
 * @param void*: puntero que finalmente apuntara a una struct
 */
void *row_check(void*); // chequea filas

/**
 * @brief        : realiza una validacion completa a la fila del sudoku, entregando un resultado de 1 si es valido con un respectivo mensaje y si no es valido, entrega un valor de 0.
 * @param void*: puntero que finalmente apuntara a una struct
 */
void *grid_check(void*); //chequea los sub cuadrados

/**
 * @brief        : funcion condicional que busca en cual grid estas segun la estructura que le pasas
 * @param void*: puntero que finalmente apuntara a una struct
 * @return       : retorna el numero del GRID con respecto a una cuadricula (va del 0-8)
 */
int nro_grid(void*);

/**
 * @brief        : realiza la creacion de una struct
 * @param int, int, int, int  : recibe los valores que seran almacenados dentro de la struct
 * @return       : retorna la struct creada
 */
sdk* create_the_struct(int, int, int, int);

int sudoku_array[9][9] =  {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 9, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

int rows_checked[9];
int cols_checked[9];
int sub_grids_checked[9];

int main(){
    double arreglo[100] = {0};
    double total = 0;
    for (int i = 0; i < 100 ; ++i) {
        arreglo[i] = sub_main();
    }
    for (int i = 0; i < 100; ++i) {
        total= total+arreglo[i];
    }
    total = total/100;
    printf("Time = %f sec\n",total);
}

double sub_main(){
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    /* Creando las varibles para los thread */
    pthread_t thread_row0, thread_row1, thread_row2, thread_row3, thread_row4, thread_row5, thread_row6, thread_row7, thread_row8,
            thread_col0, thread_col1, thread_col2, thread_col3, thread_col4, thread_col5, thread_col6, thread_col7, thread_col8,
            thread0, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8;

    for (int k = 0; k < 9; k++)
        printf("row: %d col: %d grid: %d\n", rows_checked[k], cols_checked[k], sub_grids_checked[k]);

#pragma omp parallel
    {
        sdk *row0 = create_the_struct(0, 0, 0, 8);
        sdk *row1 = create_the_struct(1, 1, 0, 8);
        sdk *row2 = create_the_struct(2, 2, 0, 8);
        sdk *row3 = create_the_struct(3, 3, 0, 8);
        sdk *row4 = create_the_struct(4, 4, 0, 8);
        sdk *row5 = create_the_struct(5, 5, 0, 8);
        sdk *row6 = create_the_struct(6, 6, 0, 8);
        sdk *row7 = create_the_struct(7, 7, 0, 8);
        sdk *row8 = create_the_struct(8, 8, 0, 8);

        sdk *col0 = create_the_struct(0, 8, 0, 0);
        sdk *col1 = create_the_struct(0, 8, 1, 1);
        sdk *col2 = create_the_struct(0, 8, 2, 2);
        sdk *col3 = create_the_struct(0, 8, 3, 3);
        sdk *col4 = create_the_struct(0, 8, 4, 4);
        sdk *col5 = create_the_struct(0, 8, 5, 5);
        sdk *col6 = create_the_struct(0, 8, 6, 6);
        sdk *col7 = create_the_struct(0, 8, 7, 7);
        sdk *col8 = create_the_struct(0, 8, 8, 8);

        sdk *grid0 = create_the_struct(0, 2, 0, 2);
        sdk *grid1 = create_the_struct(0, 2, 3, 5);
        sdk *grid2 = create_the_struct(0, 2, 6, 8);
        sdk *grid3 = create_the_struct(3, 5, 0, 2);
        sdk *grid4 = create_the_struct(3, 5, 3, 5);
        sdk *grid5 = create_the_struct(3, 5, 6, 8);
        sdk *grid6 = create_the_struct(6, 8, 0, 2);
        sdk *grid7 = create_the_struct(6, 8, 3, 5);
        sdk *grid8 = create_the_struct(6, 8, 6, 8);


        /* threads para las filas */
        pthread_create(&thread_row0, NULL, validity_check, row0);
        pthread_create(&thread_row1, NULL, validity_check, row1);
        pthread_create(&thread_row2, NULL, validity_check, row2);
        pthread_create(&thread_row3, NULL, validity_check, row3);
        pthread_create(&thread_row4, NULL, validity_check, row4);
        pthread_create(&thread_row5, NULL, validity_check, row5);
        pthread_create(&thread_row6, NULL, validity_check, row6);
        pthread_create(&thread_row7, NULL, validity_check, row7);
        pthread_create(&thread_row8, NULL, validity_check, row8);

        /* threads para las columnas */
        pthread_create(&thread_col0, NULL, validity_check, col0);
        pthread_create(&thread_col1, NULL, validity_check, col1);
        pthread_create(&thread_col2, NULL, validity_check, col2);
        pthread_create(&thread_col3, NULL, validity_check, col3);
        pthread_create(&thread_col4, NULL, validity_check, col4);
        pthread_create(&thread_col5, NULL, validity_check, col5);
        pthread_create(&thread_col6, NULL, validity_check, col6);
        pthread_create(&thread_col7, NULL, validity_check, col7);
        pthread_create(&thread_col8, NULL, validity_check, col8);

        /* threads para los girds */
        pthread_create(&thread0, NULL, validity_check, grid0);
        pthread_create(&thread1, NULL, validity_check, grid1);
        pthread_create(&thread2, NULL, validity_check, grid2);
        pthread_create(&thread3, NULL, validity_check, grid3);
        pthread_create(&thread4, NULL, validity_check, grid4);
        pthread_create(&thread5, NULL, validity_check, grid5);
        pthread_create(&thread6, NULL, validity_check, grid6);
        pthread_create(&thread7, NULL, validity_check, grid7);
        pthread_create(&thread8, NULL, validity_check, grid8);

    }
    /* Esperando los threads */
    pthread_join(thread_row0, NULL);
    pthread_join(thread_row1, NULL);
    pthread_join(thread_row2, NULL);
    pthread_join(thread_row3, NULL);
    pthread_join(thread_row4, NULL);
    pthread_join(thread_row5, NULL);
    pthread_join(thread_row6, NULL);
    pthread_join(thread_row7, NULL);
    pthread_join(thread_row8, NULL);

    pthread_join(thread_col0, NULL);
    pthread_join(thread_col1, NULL);
    pthread_join(thread_col2, NULL);
    pthread_join(thread_col3, NULL);
    pthread_join(thread_col4, NULL);
    pthread_join(thread_col5, NULL);
    pthread_join(thread_col6, NULL);
    pthread_join(thread_col7, NULL);
    pthread_join(thread_col8, NULL);

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);
    pthread_join(thread8, NULL);

    for (int k = 0; k < 9; k++)
        printf("row: %d col: %d grid: %d\n", rows_checked[k], cols_checked[k], sub_grids_checked[k]);

    gettimeofday(&tv2, NULL);
    double result = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (double) (tv2.tv_sec - tv1.tv_sec);
    return result;
}

sdk* create_the_struct(int init_row, int fin_row, int init_col, int fin_col)
{
    sdk *p1 = (sdk*)malloc(sizeof(sdk));
    p1->init_row = init_row;
    p1->fin_row = fin_row;
    p1->init_col = init_col;
    p1->fin_col = fin_col;
    return p1;
}

void *validity_check(void *area){
    sdk *sudoku = (sdk*)area;
    if (sudoku->init_row == sudoku->fin_row) {
        /* chequea fila */
        row_check(sudoku);
    }
    else if (sudoku->init_col == sudoku->fin_col) {
        /* chequea columna */
        col_check(sudoku);
    }
    else {
        /* chequea grid */
        grid_check(sudoku);
    }
}


void *row_check(void *init_row){
    sdk *ROW = (sdk *)init_row;
    int tmp[9] = {0};
    int k,var;
    for (k = ROW->init_col; k <= ROW->fin_col; k++) {
        /* recorre las filas y actualiza el arreglo temporal */
        var = sudoku_array[ROW->init_row][k];
        tmp[var - 1] = 1;
    }
    for (k = 0; k < 9; k++) {
        /* consulta el arreglo temporal */
        if (tmp[k] == 0){
            /* si la fila esta correcta, actualiza el arreglo global */
            rows_checked[ROW->init_row] = 0;
            break;
        }
        else {
            rows_checked[ROW->init_row] = 1;
        }
    }
}

void *col_check(void *init_col){
    sdk *COL = (sdk *)init_col;
    int tmp[9] = {0};
    int k,var;
    for (k = COL->init_row; k <= COL->fin_row; k++) {
        /* recorre las columnas y actualiza el arreglo temporal */
        var = sudoku_array[k][COL->init_col];
        tmp[var - 1] = 1;
    }
    for (k = 0; k < 9; k++) {
        /* consulta el arreglo temporal */
        if (tmp[k] == 0){
            cols_checked[COL->init_col] = 0;
            break;
        }
        else {
            /* si la columna esta correcta, actualiza el arreglo global */
            cols_checked[COL->init_col] = 1;
        }
    }
}

void *grid_check(void* sub_grid) {
    sdk *GRID = (sdk *)sub_grid;
    int var, k, x, y;
    //printf("init row %d fin row %d init col %d fin col %d\n",GRID->init_row, GRID->fin_row, GRID->init_col, GRID->fin_col);
    int index = nro_grid(GRID);

    int tmp[9] = {0};
    for (x = GRID->init_row; x <= GRID->fin_row; x++) {

        for (y = GRID->init_col; y <=  GRID->fin_col; y++) {
            /* Se recorre de fila en fila */
            var = sudoku_array[x][y];
            tmp[var - 1] = 1;
        }
    }
    for (k = 0; k < 9; k++) {
        /* Se revisa el arreglo temporal, si falto algun nro, su posicion tendra valor 0 */
        if (tmp[k] == 0) {
            sub_grids_checked[index] = 0;
            break;
        }
        else {
            sub_grids_checked[index] = 1;
        }
    }
}

int nro_grid(void *sudoku){
    sdk *index = (sdk *)sudoku;

    if (index->init_row == 0 && index->fin_row == 2 && index->init_col == 0 && index->fin_col == 2) return 0;

    if (index->init_row == 0 && index->fin_row == 2 && index->init_col == 3 && index->fin_col == 5) return 1;

    if (index->init_row == 0 && index->fin_row == 2 && index->init_col == 6 && index->fin_col == 8) return 2;

    if (index->init_row == 3 && index->fin_row == 5 && index->init_col == 0 && index->fin_col == 2) return 3;

    if (index->init_row == 3 && index->fin_row == 5 && index->init_col == 3 && index->fin_col == 5) return 4;

    if (index->init_row == 3 && index->fin_row == 5 && index->init_col == 6 && index->fin_col == 8) return 5;

    if (index->init_row == 6 && index->fin_row == 8 && index->init_col == 0 && index->fin_col == 2) return 6;

    if (index->init_row == 6 && index->fin_row == 8 && index->init_col == 3 && index->fin_col == 5) return 7;

    if (index->init_row == 6 && index->fin_row == 8 && index->init_col == 6 && index->fin_col == 8) return 8;
}

