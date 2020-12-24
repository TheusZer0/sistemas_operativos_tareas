#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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

double sub_main();

int rows_checked[9] = {0};
int cols_checked[9] = {0};
int sub_grids_checked[9] = {0};

struct sdk{
    int init_row; // fila inicial
    int fin_row; // fila final
    int init_col; // columna inicial
    int fin_col; // columna final
};

void validity_check(struct sdk); //chequea solucion de sudoku
void col_check(struct sdk);  // chequea columnas
void row_check(struct sdk); // chequea filas
void grid_check(struct sdk); //chequea los sub cuadrados
int nro_grid(struct sdk);
struct sdk create_the_struct(int, int, int, int);

int main(){
    double arreglo[1000] = {0};
    double total = 0;
    for (int i = 0; i < 1000 ; ++i) {
        arreglo[i] = sub_main();
    }
    for (int i = 0; i < 1000; ++i) {
        total= total+arreglo[i];
    }
    total = total/1000;
    printf("Time = %f sec\n",total);
}

double sub_main(){
    int flag = 0;
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);

    struct sdk grid0 = create_the_struct(0,2,0,2);
    struct sdk grid1 = create_the_struct(0,2,3,5);
    struct sdk grid2 = create_the_struct(0,2,6,8);
    struct sdk grid3 = create_the_struct(3,5,0,2);
    struct sdk grid4 = create_the_struct(3,5,3,5);
    struct sdk grid5 = create_the_struct(3,5,6,8);
    struct sdk grid6 = create_the_struct(6,8,0,2);
    struct sdk grid7 = create_the_struct(6,8,3,5);
    struct sdk grid8 = create_the_struct(6,8,6,8);

    struct sdk row0 = create_the_struct(0,0,0,8);
    struct sdk row1 = create_the_struct(1,1,0,8);
    struct sdk row2 = create_the_struct(2,2,0,8);
    struct sdk row3 = create_the_struct(3,3,0,8);
    struct sdk row4 = create_the_struct(4,4,0,8);
    struct sdk row5 = create_the_struct(5,5,0,8);
    struct sdk row6 = create_the_struct(6,6,0,8);
    struct sdk row7 = create_the_struct(7,7,0,8);
    struct sdk row8 = create_the_struct(8,8,0,8);

    struct sdk col0 = create_the_struct(0,8,0,0);
    struct sdk col1 = create_the_struct(0,8,1,1);
    struct sdk col2 = create_the_struct(0,8,2,2);
    struct sdk col3 = create_the_struct(0,8,3,3);
    struct sdk col4 = create_the_struct(0,8,4,4);
    struct sdk col5 = create_the_struct(0,8,5,5);
    struct sdk col6 = create_the_struct(0,8,6,6);
    struct sdk col7 = create_the_struct(0,8,7,7);
    struct sdk col8 = create_the_struct(0,8,8,8);

    validity_check(grid0);
    validity_check(grid1);
    validity_check(grid2);
    validity_check(grid3);
    validity_check(grid4);
    validity_check(grid5);
    validity_check(grid6);
    validity_check(grid7);
    validity_check(grid8);

    validity_check(row0);
    validity_check(row1);
    validity_check(row2);
    validity_check(row3);
    validity_check(row4);
    validity_check(row5);
    validity_check(row6);
    validity_check(row7);
    validity_check(row8);

    validity_check(col0);
    validity_check(col1);
    validity_check(col2);
    validity_check(col3);
    validity_check(col4);
    validity_check(col5);
    validity_check(col6);
    validity_check(col7);
    validity_check(col8);



    for (int k = 0; k < 9; k++) {
        if (rows_checked[k] == 0 || cols_checked[k] == 0 || sub_grids_checked[k] == 0){
            printf("La solucion del sudoku no es valida\n");
            break;
        } else if (k == 8)
            printf("La solucion del sudoku es valida\n");
    }

    gettimeofday(&tv2, NULL);
    double result = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (double) (tv2.tv_sec - tv1.tv_sec);

    return result;
}

struct sdk create_the_struct(int init_row, int fin_row, int init_col, int fin_col){
    struct sdk p1;
    p1.init_row = init_row;
    p1.fin_row = fin_row;
    p1.init_col = init_col;
    p1.fin_col = fin_col;
    return p1;
}

void validity_check(struct sdk sudoku){
    if (sudoku.init_row == sudoku.fin_row) {
        /* chequea fila */
        row_check(sudoku);
    }
    else if (sudoku.init_col == sudoku.fin_col) {
        /* chequea columna */
        col_check(sudoku);
    }
    else {
        /* chequea grid */
        grid_check(sudoku);
    }
}

void row_check(struct sdk sudoku){
    int tmp[9] = {0};
    int k,var;
    for (k = sudoku.init_col; k <= sudoku.fin_col; k++) {
        /* recorre las columnas y actualiza el arreglo temporal */
        var = sudoku_array[sudoku.init_row][k];
        tmp[var - 1] = 1;
    }
    for (k = 0; k < 9; k++) {
        /* consulta el arreglo temporal */
        if (tmp[k] == 0){
            /* si la columna esta correcta, actualiza el arreglo global */
            rows_checked[sudoku.init_row] = 0;
            break;
        }
        else {
            rows_checked[sudoku.init_row] = 1;
        }
    }

}

void col_check(struct sdk sudoku){
    int tmp[9] = {0};
    int k,var;
    for (k = sudoku.init_row; k <= sudoku.fin_row; k++) {
        /* recorre las columnas y actualiza el arreglo temporal */
        var = sudoku_array[k][sudoku.init_col];
        tmp[var - 1] = 1;
    }
    for (k = 0; k < 9; k++) {
        /* consulta el arreglo temporal */
        if (tmp[k] == 0){
            /* si la columna esta correcta, actualiza el arreglo global */
            cols_checked[sudoku.init_col] = 0;
            break;
        }
        else {
            cols_checked[sudoku.init_col] = 1;
        }
    }
}

void grid_check(struct sdk sudoku) {
    int var, k, x, y;
    int index = nro_grid(sudoku);
    int tmp[9] = {0};
    for (x = sudoku.init_row; x <= sudoku.fin_row; x++) {

        for (y = sudoku.init_col; y <= sudoku.fin_col; y++) {
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

int nro_grid(struct sdk sudoku){

    if (sudoku.init_row == 0 && sudoku.fin_row == 2 && sudoku.init_col == 0 && sudoku.fin_col == 2) return 0;

    if (sudoku.init_row == 0 && sudoku.fin_row == 2 && sudoku.init_col == 3 && sudoku.fin_col == 5) return 1;

    if (sudoku.init_row == 0 && sudoku.fin_row == 2 && sudoku.init_col == 6 && sudoku.fin_col == 8) return 2;

    if (sudoku.init_row == 3 && sudoku.fin_row == 5 && sudoku.init_col == 0 && sudoku.fin_col == 2) return 3;

    if (sudoku.init_row == 3 && sudoku.fin_row == 5 && sudoku.init_col == 3 && sudoku.fin_col == 5) return 4;

    if (sudoku.init_row == 3 && sudoku.fin_row == 5 && sudoku.init_col == 6 && sudoku.fin_col == 8) return 5;

    if (sudoku.init_row == 6 && sudoku.fin_row == 8 && sudoku.init_col == 0 && sudoku.fin_col == 2) return 6;

    if (sudoku.init_row == 6 && sudoku.fin_row == 8 && sudoku.init_col == 3 && sudoku.fin_col == 5) return 7;

    if (sudoku.init_row == 6 && sudoku.fin_row == 8 && sudoku.init_col == 6 && sudoku.fin_col == 8) return 8;
}
