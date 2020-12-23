//
// Created by theuszero on 12/20/20.
//

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sdk create_the_struct(int init_row, int fin_row, int init_col, int fin_col);

int nro_grid(int inicio_x, int fin_x, int inicio_y, int fin_y);

int grid_check(int inicio_x, int fin_x, int inicio_y, int fin_y);

int validity_check(struct sdk page);

/* Row */
int row_assignement(int init_row, int fin_row);

int row_check();

/* Column */

int column_assignement(int init_column, int fin_column);

int column_check();

/* Others */

int found_duplicate(int cont[], int size);


struct sdk
{
    int init_row; // fila inicial
    int fin_row; // fila final
    int init_col; // columna inicial
    int fin_col; // columna final
};

// valor inicial 0
int rows_checked[9] = {0};
int cols_checked[9] = {0};
int sub_grids_checked[9] = {0};

int sudoku_array[9][9] = {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 1, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

int main(){
    struct sdk page = create_the_struct(1,1,0,8);
    validity_check(page);
    return 0;
}

int validity_check(struct sdk page){

    column_assignement(page.init_col,page.fin_col);
    row_assignement(page.init_row,page.fin_col);
    if (column_check() == 1 || row_check() == 1){
        printf("Sudoku Malo");
    }
    if (grid_check(6,8,0,2) == 0){
        printf("Cuadricula Buena");
    }else{
        printf("Sudoku Malo");
        return EXIT_FAILURE;
    };
}

struct sdk create_the_struct(int init_row, int fin_row, int init_col, int fin_col){
    struct sdk p1;
    p1.init_row = init_row;
    p1.fin_row = fin_row;
    p1.init_col = init_col;
    p1.fin_col = fin_col;
    return p1;
}

int row_check(){
    for (int i = 0; i < 9 ; ++i) {
        if (rows_checked[i] == 1){
            return 1;
        }
    }
}

int row_assignement(int init_row, int fin_column){
    int cont[9] = {0};
    int contador = 0;
    for (int i = 0; i <= fin_column; ++i) {
        if (sudoku_array[init_row][i] <= 9 && sudoku_array[init_row][i]>0){
            cont[i] = sudoku_array[init_row][i];
            contador++;
        } else{
            rows_checked[init_row] = 1;
            return 0;
        }
    }
    int duplicate = found_duplicate(cont,contador);
    if (duplicate == 1){
        rows_checked[init_row] = 1;
    }else{
        return 0;
    }
    return 0;
}

int column_assignement(int init_column,int fin_col){
    int cont[9] = {0};
    int contador = 0;
    for (int i = 0; i <= fin_col; ++i) {
        if (sudoku_array[i][init_column] < 10 && sudoku_array[i][init_column]>0){
            cont[i] = sudoku_array[i][init_column];
            contador++;
        } else{
            cols_checked[init_column] = 1;
        }
    }
    int duplicate = found_duplicate(cont,contador);
    if (duplicate == 1){
        cols_checked[init_column] = 1;
    }
    return 0;
}

int column_check(){
    for (int i = 0; i < 9 ; ++i) {
        if (cols_checked[i]==1){
            return 1;
        }
    }
}

int found_duplicate(int cont[], int size){
    int count=0;
    for(int i=0; i<size; i++)
    {
        for(int j=i+1; j<size; j++)
        {
            /* If duplicate found then increment count by 1 */
            if(cont[i] == cont[j])
            {
                count++;
                break;
            }
        }
    }
    if (count==0){
        return count;
    }else{
        return 1;
    }
}

int grid_check(int inicio_x, int fin_x, int inicio_y, int fin_y) {
    int var, k, x, y;
    int index = nro_grid(inicio_x, fin_x, inicio_y, fin_y);
    int tmp[9] = {0};
    for (x = inicio_x; x <= fin_x; x++) {

        for (y = inicio_y; y <= fin_y; y++) {
            /* Se recorre de fila en fila */
            var = sudoku_array[x][y];

            tmp[var - 1] = 1;
        }
    }
    for (k = 0; k < 9; k++) {
        /* Se revisa el arreglo temporal, si falto algun nro, su posicion tendra valor 0 */
        if (tmp[k] == 0) {
            sub_grids_checked[index] = 0;
            return 1;
        }
        else {
            sub_grids_checked[index] = 1;
            return 0;
        }
    }
}

int nro_grid(int inicio_x, int fin_x, int inicio_y, int fin_y){

    if (inicio_x == 0 && fin_x == 2 && inicio_y == 0 && fin_y == 2) return 0;

    if (inicio_x == 0 && fin_x == 2 && inicio_y == 3 && fin_y == 5) return 1;

    if (inicio_x == 0 && fin_x == 2 && inicio_y == 6 && fin_y == 8) return 2;

    if (inicio_x == 3 && fin_x == 5 && inicio_y == 0 && fin_y == 2) return 3;

    if (inicio_x == 3 && fin_x == 5 && inicio_y == 3 && fin_y == 5) return 4;

    if (inicio_x == 3 && fin_x == 5 && inicio_y == 6 && fin_y == 8) return 5;

    if (inicio_x == 6 && fin_x == 8 && inicio_y == 0 && fin_y == 2) return 6;

    if (inicio_x == 6 && fin_x == 8 && inicio_y == 3 && fin_y == 5) return 7;

    if (inicio_x == 6 && fin_x == 8 && inicio_y == 6 && fin_y == 8) return 8;
}