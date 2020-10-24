//
// Created by theuszero on 10/19/20.
//

#ifndef SISTEMAS_OPERATIVOS_TAREAS_ALLFUNCTIONS_H
#define SISTEMAS_OPERATIVOS_TAREAS_ALLFUNCTIONS_H

/*
* @file: AllFunctions.h
* @author:
* @date: 19-10-2020
* @brief: realiza una validacion completa al dato introducido por comando
 * para determinar si puede convertirse en un entero positivo de tipo int,
 * en caso de fallar, el programa termina su ejecucion.
*/
int validation(char *number);
void fork_process();
void timeofday();
void* C_shared_memory();
void W_shared_memory();
int RD_shared_memory();
int sucesion_Collatz (unsigned int n);
void fork_sucesion_Collatz(unsigned int n);

#endif //SISTEMAS_OPERATIVOS_TAREAS_ALLFUNCTIONS_H
