#ifndef __ESTADISTICAS_H__
#define __ESTADISTICAS_H__ 

#define HIT 1
#define PENALTY 100
#define KB 1024

#include <stdio.h>
#include <stdbool.h>
#include "cacheutil.h"

typedef struct estadisticas estadisticas_t;

/*
*	Devuelve un puntero a una estadistica inicializada o NULL en caso de error.
*/
estadisticas_t* estadisticas_crear();

/*
*	Destruye la memoria reservada para una estadistica.
*/
void estadisticas_destruir(estadisticas_t* estadisticas);

/*
*	Recibe la operacion procesada y carga los resultados en la estadistica pasada por parametro.
*/
void cargar_estadisticas(estadisticas_t* estadisticas, op_result_t* op_result);

/*
*  Recibe el tamanio_cache como cantidad de bytes, los sets y la accesibilidad deben estar validados.
*  Imprime y calcula todas las estadisticas relevantes del archivo.
*/
void imprimir_estadisticas(estadisticas_t* estadisticas, size_t sets, size_t E, size_t tamanio_cache);

#endif //__ESTADISTICAS_H__ 