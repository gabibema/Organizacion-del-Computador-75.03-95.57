#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "simulador.h"
#include "cache.h"
#include "cacheutil.h"
#include "estadisticas.h"

#define CLEAN_MISS "2a"
#define DIRTY_MISS "2b"

struct simulador{
    cache_t* cache;
    size_t cache_tam;
    size_t cache_asociatividad;
    size_t cache_sets;

    size_t modo_verb_inicio;
    size_t modo_verb_final;

    estadisticas_t* estadisticas;
};

simulador_t* simulador_crear(size_t cache_tamanio, size_t cache_asociatividad, size_t cache_sets, size_t inicio, size_t fin){
    simulador_t* simulador = malloc(sizeof(simulador_t));
    if(!simulador){
        return NULL;
    }
    simulador->cache = cache_crear(cache_tamanio, cache_asociatividad, cache_sets);
    if(!simulador->cache){
        free(simulador);
        return NULL;
    }

    simulador->estadisticas = estadisticas_crear();
    if(!simulador->estadisticas){
        cache_destruir(simulador->cache);
        free(simulador);
        return(NULL);
    }

    simulador->modo_verb_final = fin;
    simulador->modo_verb_inicio = inicio;

    simulador->cache_tam = cache_tamanio;
    simulador->cache_asociatividad = cache_asociatividad;
    simulador->cache_sets = cache_sets;
    
    return simulador;
}

void simulador_destruir(simulador_t* simulador){
    if(!simulador) return;
    cache_destruir(simulador->cache);
    estadisticas_destruir(simulador->estadisticas);
    free(simulador);
}


void simulador_modo_verboso(op_result_t* result, size_t instruccion, size_t asociatividad){
    printf("%ld ", instruccion);                                            
    if(result->resultado == hit) printf("%d ", HIT);
    else if(result->resultado == clean_miss) printf("%s ", CLEAN_MISS);     
    else printf("%s ", DIRTY_MISS);                                         

    printf("%lx ", result->direccion.index);                                
    printf("%lx ", result->direccion.tag);                                 
    printf("%ld ", result->op_bloque_off);                                   
    
    if(result->valido == 1) printf("%lx ", result->direccion.tag);          
    else  printf("-1 ");

    if(result->valido) printf("1 ");                                       
    else printf("0 ");

    if(result->dirty_bit) printf("1 ");                                    
    else printf("0 ");

    if(asociatividad > 1)
        printf("%ld", result->ant_bloque_ins);                            
    printf("\n");
}

void simulador_operar(simulador_t* simulador, char* operacion, size_t direccion, size_t instruccion){

    if(!simulador){
        return;
    }
    
    op_result_t* result = cache_operar(simulador->cache, *operacion, direccion, instruccion);
    if(!result) return;

    if(instruccion == simulador->modo_verb_inicio && instruccion <= simulador->modo_verb_final && simulador->modo_verb_final != 0 ){
        simulador_modo_verboso(result, instruccion, simulador->cache_asociatividad);
        simulador->modo_verb_inicio++; 
    }

    cargar_estadisticas(simulador->estadisticas, result);
    free(result);
}

void simulador_imprimir_estadisticas(simulador_t* simulador){
    imprimir_estadisticas(simulador->estadisticas, simulador->cache_sets, simulador->cache_asociatividad, simulador->cache_tam);
}