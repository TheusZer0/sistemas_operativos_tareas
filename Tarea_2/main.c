//
// Created by theuszero on 12/20/20.
//

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sdk create_the_struct(int init_row, int fin_row, int init_col, int fin_col);

void gridcheck(int init_row, int fin_row, int init_col, int fin_col);

/* Row */
int row_assignement(int init_row);

void row_check();

/* Column */

int column_assignement(int init_column);

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

int sudoku_array[9][9] = {
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

int main(){
    struct sdk page = create_the_struct(0,3,0,3);
    column_assignement(4);
    column_check();
    //    gridcheck(3,5,3,5);
    return 0;
}

// valor inicial 0
int rows_checked[9] = {0};
int cols_checked[9] = {0};
int sub_grids_checked[9] = {0};

struct sdk create_the_struct(int init_row, int fin_row, int init_col, int fin_col){
    struct sdk p1;
    p1.init_row = init_row;
    p1.fin_row = fin_row;
    p1.init_col = init_col;
    p1.fin_col = fin_col;
    return p1;
}

void row_check(){
    for (int i = 0; i < 9 ; ++i) {
        printf("row value: %d \n",rows_checked[i]);
    }
}

int row_assignement(int init_row){
    int cont[8] = {0};
    int contador = 0;
    for (int i = 0; i < 9; ++i) {
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

int column_assignement(int init_column){
    int cont[9] = {0};
    int contador = 0;
    for (int i = 0; i < 9; ++i) {
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
        printf("column value: %d \n",cols_checked[i]);
    }
}

void gridcheck(int init_row, int fin_row, int init_col, int fin_col){
    int cont = 0;
    for (int i = init_col; i <= fin_col; ++i) {
        for (int j = init_row; j <= fin_row; ++j) {
            printf("%d ",sudoku_array[i][j]);
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