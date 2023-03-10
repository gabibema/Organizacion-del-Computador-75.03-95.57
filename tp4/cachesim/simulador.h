#ifndef __SIMULADOR_H__
#define __SIMULADOR_H__ 

#include <stddef.h> //size_t

typedef struct simulador simulador_t;

/*
*	Dados los parametros recibidos por argumento, devuelve un puntero a un simulador o en caso de error devuelve NULL.	
*/
simulador_t* simulador_crear(size_t cache_tamanio, size_t cache_asociatividad, size_t cache_sets, size_t inicio, size_t fin);

/*
*	Destruye la memoria reservada para un simulador.
*/
void simulador_destruir(simulador_t* simulador);

/*
*	Dados un simulador, la operacion y la direccion en la cual operar, simula una sola operacion en de cache, tambien
* 	registra los datos necesarios para las estadisticas.
*/
void simulador_operar(simulador_t* simulador, char* operacion, size_t direccion, size_t instruccion);

/*
*	Imprime las estadisticas acumuladas hasta el momento:
*   lectuas, escrituras, clean misses, dirty misses, bytes leidos y bytes escritos.
*/
void simulador_imprimir_estadisticas(simulador_t* simulador);

#endif