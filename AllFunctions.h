/*
* @file: AllFunctions.h
* @author:
* @date: 19-10-2020
* @brief:
*/

#ifndef SISTEMAS_OPERATIVOS_TAREAS_ALLFUNCTIONS_H
#define SISTEMAS_OPERATIVOS_TAREAS_ALLFUNCTIONS_H

/**
 * @brief        : realiza una validacion completa al dato introducido por comando
 * para determinar si puede convertirse en un entero positivo de tipo int,
 * en caso de fallar, el programa termina su ejecucion.
 * @param char *number: recibe el numero como un char (que fue introducido por consola), este sera validado
 * @return       : retorna el entero numero, es decir, convierte el numero ingresado que era un char en numero (ademas de validarlo)
 */
int validation(char *number);

/**
 * @brief        : crea proceso padre y un proceso hijo, para asi determinar mediante una system call la fecha exacta
 * en que fue ejecutado el programa en el sistema. (se trabajo en un sistema linux)
 */
void fork_process();

/**
 * @brief        : funcion que imprime la hora exacta del sistema, tanto el dia y la fecha de este mismo
 * funciona con una sistem call gettimeofday().
 */
void timeofday();

/**
 * @brief        : crea un espacio de memoria compartido, de la forma POSIX, este codigo fue extraido
 * desde el aula misma, configurandolo de manera especifica para el funcionamiento de la tarea.
 * @return       : retorna un puntero void* que representa el mapeo de la

 */
void* C_shared_memory();

/**
 * @brief        : funcion que escribe dentro de la memoria compartida, esta funcion concadena los numeros
 * que son entregados mediante parametro de la misma funcion (el numero corresponderia al parametro char* str)
 * y tambien recibe el mapeo como un void *ptr, asi, una vez entregado esto, la funcion escribe sobre la memoria compartida el char* str,
 * si este char es un numero diferente de 1, entonces lo concadena con una ",", en caso de que si sea un 1, este solo concadena con el numero, sin una ",".
 * @param void *ptr: parametro que corresponde al mapeo del espacio de memoria compartida, este se recibe gracias a la funcion void* C_shared_memory().
 * @param char* str: numero convertido en un char* que sera escrito en la memoria compartida.
 */
void W_shared_memory(void *ptr, char* str);

/**
 * @brief        :
 * @param headRef:
 * @return       :
 */
int RD_shared_memory();

/**
 * @brief        : recibe el número positivo como argumento y retorna el siguiente número generado de la
 * sucesión Collatz, implementando el algoritmo antes mencionado.
 * @param unsigned int n: corresponde al número positivo
 * @return       :retorna el siguiente número generado de la sucesión Collatz
 */
int sucesion_Collatz (unsigned int n);

/**
 * @brief        : esta funcion corresponde a la creacion de un proceso padre y un proceso hijo
 * donde el proceso hijo ejecutara la funcion "int sucesion_Collatz (unsigned int n);" en un bucle hasta obtener el numero 1
 * insertando los valores dentro de un espacio de memoria compartido. Una vez el proceso hijo termina generando los numeros
 * de la sucesión Collatz e insertandolos en la memoria compartida, entonces el proceso padre que estaba en la espera puede ejecutar sus sentencias.
 * EXPLICAR PADRE
 * EXPLICAR PADRE
 * EXPLICAR PADRE
 * @param unsigned int n: recibe como argumento el numero entero positivo al que se le aplicara la sucesión Collatz.
 */
void fork_sucesion_Collatz(unsigned int n);

#endif //SISTEMAS_OPERATIVOS_TAREAS_ALLFUNCTIONS_H
