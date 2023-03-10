#ifndef __CACHE_H__
#define __CACHE_H__ 
#include <stdbool.h>
#include <stdio.h>
#include "cacheutil.h"

#define HIT 1
#define PENALTY 100 

typedef struct cache cache_t;

/*
*	Crea una matriz cache inicializada y devuelve su puntero
* 	o NULL en caso error.
*/
cache_t* cache_crear(size_t tam, size_t asociatividad, size_t num_sets);


/*
*   Desrtuye hasta la posicion indicada por el tope o destruye todo (debe pasarse la cantidad de sets)
*/
void cache_destruir(cache_t* cache);

/*
*	Realiza y procesa una operacion de la cache y devuelve un registro con datos relevantes de la operacion.
* 	En caso de fallo devuelve NULL.
*/
op_result_t* cache_operar(cache_t* cache, char op, size_t dir, size_t instruccion);

#endif //__CACHE_H__ 