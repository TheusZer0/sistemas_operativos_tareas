//
// Created by theuszero on 12/20/20.
//



#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sdk create_the_struct(int init_row, int fin_row, int init_col, int fin_col);

void validate(int init_row, int fin_row, int init_col, int fin_col);

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

// valor inicial 0
int rows_checked[9];
int cols_checked[9];
int sub_grids_checked[9] ;

int main(){
    struct sdk page = create_the_struct(3,5,3,5);
    validate(page.init_row,page.fin_row,page.init_col,page.fin_col);
    return 0;
}

struct sdk create_the_struct(int init_row, int fin_row, int init_col, int fin_col){
    struct sdk p1;
    p1.init_row = init_row;
    p1.fin_row = fin_row;
    p1.init_col = init_col;
    p1.fin_col = fin_col;
    return p1;
}

void validate(int init_row, int fin_row, int init_col, int fin_col){
    int cont = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("%d",sudoku_array[i][j]);
            if (cont = )
            cont++
        }
    }
}
