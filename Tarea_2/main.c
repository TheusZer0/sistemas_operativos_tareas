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

int rows_checked[9];
int cols_checked[9];
int sub_grids_checked[9];

int validity_check(int, int, int, int); //chequea solucion de sudoku
void col_check(int);  // chequea columnas
void row_check(int); // chequea filas
void grid_check(int, int, int, int); //chequea los sub cuadrados
int nro_grid(int, int, int, int);

typedef struct {
    int init_row; // fila inicial
    int fin_row; // fila final
    int init_col; // columna inicial
    int fin_col; // columna final
}pos;

pos posiciones = {0,0,0,0};

void main(){
    int i, flag;
    for(i = 0; i < 9; i++){
        rows_checked[i] = 0;
        cols_checked[i] = 0;
        sub_grids_checked[i] = 0;
    }

    /*
    printf("%d\n",rows_checked[5]);
    row_check(5);
    printf("%d\n",rows_checked[5]);

    printf("%d\n",cols_checked[0]);
    col_check(0);
    printf("%d\n",cols_checked[0]);
    */

    printf("%d\n",sub_grids_checked[4]);
    grid_check(3,5,3,5);
    printf("%d\n",sub_grids_checked[4]);


    /*
    if (flag)
      printf("La solucion correcta\n");
    else
      printf("La solución NO es correcta\n");
    */

}

int validity_check(int xi, int yi, int xf, int yf){
    posiciones.init_row = xi;
    posiciones.fin_row = xf;
    posiciones.init_col = yi;
    posiciones.fin_col = yf;
    int x,y,i;

    for (x = xi; x < xf; x++) {
        /* pregunta si todas las filas sirven */
        row_check(x);
    }
    for (y = yi; y < yf; y++) {
        /* pregunta si todas las columnas sirven */
        col_check(y);
    }



    for (i = 0; i < 9; i++) {
        /* verifica los arreglos para saber si estamos ante una solucion */
        if (rows_checked[i] == 0 || cols_checked[i] == 0 || sub_grids_checked[i] == 0)
            return 0;
    }
    return 1;
}

void row_check(int i){
    int tmp[9] = {0};
    int k,var;
    for (k = 0; k < 9; k++) {
        /* recorre las columnas y actualiza el arreglo temporal */
        var = sudoku_array[i][k];
        tmp[var - 1] = 1;
    }
    for (k = 0; k < 9; k++) {
        /* consulta el arreglo temporal */
        if (tmp[k] == 0){
            /* si la columna esta correcta, actualiza el arreglo global */
            rows_checked[i] = 0;
            break;
        }
        else {
            rows_checked[i] = 1;
        }
    }

}

void col_check(int i){
    int tmp[9] = {0};
    int k,var;
    for (k = 0; k < 9; k++) {
        /* recorre las columnas y actualiza el arreglo temporal */
        var = sudoku_array[k][i];
        tmp[var - 1] = 1;
    }
    for (k = 0; k < 9; k++) {
        /* consulta el arreglo temporal */
        if (tmp[k] == 0){
            /* si la columna esta correcta, actualiza el arreglo global */
            cols_checked[i] = 0;
            break;
        }
        else {
            cols_checked[i] = 1;
        }
    }
}

void grid_check(int inicio_x, int fin_x, int inicio_y, int fin_y) {
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
            break;
        }
        else {
            sub_grids_checked[index] = 1;
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
