cmake_minimum_required(VERSION 3.17)
project(sistemas_operativos_tareas C)

set(CMAKE_C_STANDARD 11)

add_executable(sistemas_operativos_tareas Tarea_1/parte_Dos/main.c Tarea_2/main.c Tarea_2/main.h Tarea_2/threads.c Tarea_2/open_mp.c)