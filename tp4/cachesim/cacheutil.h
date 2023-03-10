#ifndef __CACHEUTIL_H__
#define __CACHEUTIL_H__ 

#include <stdio.h> 
#include <stdbool.h> 

typedef enum resultados
{
    hit,
    clean_miss,
    dirty_miss
}resultados_t;

typedef struct addr
{
	size_t tag;
	size_t index;
	size_t off;
}addr_t;

typedef struct op_result
{
    char operacion; 		 
    resultados_t resultado;  
    addr_t direccion;	    
    size_t instruccion;    
    bool valido; 		 
    bool dirty_bit;      
    size_t ant_bloque_ins; 
    size_t op_bloque_off; 
}op_result_t;

#endif