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
 * @brief        :
 * @param headRef:
 * @return       :
 */
void W_shared_memory(void *ptr, char* str);

/**
 * @brief        :
 * @param headRef:
 * @return       :
 */
int RD_shared_memory();

/**
 * @brief        :
 * @param headRef:
 * @return       :
 */
int sucesion_Collatz (unsigned int n);

/**
 * @brief        :
 * @param headRef:
 * @return       :
 */
void fork_sucesion_Collatz(unsigned int n);

#endif //SISTEMAS_OPERATIVOS_TAREAS_ALLFUNCTIONS_H
