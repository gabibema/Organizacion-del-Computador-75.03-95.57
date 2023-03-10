#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cache.h"

#define ESCRITURA 'W'
#define LECTURA 'R'

typedef struct bloque{
    size_t tam; 
	bool es_valido;  
	bool dirty_bit; 
	size_t tag;  
	void* data;
    size_t ins;
}bloque_t;

typedef struct set{
    size_t E; 			 
	bloque_t* bloques; 	
}set_t;

typedef struct cache{
    size_t S;   
    set_t* sets;
}cache_t;


void destruir_bloques(bloque_t* bloque, size_t tope);

void cache_destruir_hasta(cache_t* cache, size_t tope);

bloque_t* crear_bloques(size_t asociatividad, size_t tam_bloque){   
    bloque_t* bloque = calloc(asociatividad, sizeof(bloque_t)); 
    if(!bloque) return NULL;

    for(size_t i = 0; i < asociatividad; ++i){   
        bloque[i].tam = tam_bloque;
        bloque[i].data = malloc(tam_bloque); 
        if(!bloque[i].data){                
            destruir_bloques(bloque, i);
            return NULL;
        }else bloque[i].tag = i;         
    }
    return bloque;
}

cache_t* cache_crear(size_t tam, size_t asociatividad, size_t num_sets){
    size_t tam_bloque = tam / (asociatividad * num_sets);

    cache_t* cache = malloc(sizeof(cache_t));  
    if(!cache) return NULL;
    
    cache->S = num_sets;
    cache->sets = calloc(num_sets, sizeof(set_t)); 
    if(!cache->sets){
        free(cache);
        return NULL;
    }

    for(size_t i = 0; i < num_sets; i++){
        cache->sets[i].E = asociatividad;
        cache->sets[i].bloques = crear_bloques(asociatividad, tam_bloque); 
        if(!cache->sets[i].bloques){
            cache_destruir_hasta(cache, i);
            return NULL;
        }
    }
    return cache;
}

void destruir_bloques(bloque_t* bloque, size_t tope){
    for (size_t i = tope-1; i > 0; i--)
        free(bloque[i].data);
    free(bloque->data);
    free(bloque);
}

void cache_destruir(cache_t* cache){
    if(!cache) return;

    for(size_t i = 0; i < cache->S; i++){
        for(size_t k = 0; k < cache->sets[i].E; k++){
            free(cache->sets[i].bloques[k].data);
        }
        free(cache->sets[i].bloques);
    }
    free(cache->sets);
    free(cache);
}


void cache_destruir_hasta(cache_t* cache, size_t tope){
    if(!cache) return;
    if(!cache->sets){
        free(cache);
        return;
    } 

    for(size_t i = tope -1; i > 0; i--){
        if(cache->sets[i].bloques != NULL)
            destruir_bloques(cache->sets[i].bloques, cache->sets[i].E);   
        else free( &(cache->sets[i]) );                                  
    } 

    free(cache->sets); 
    free(cache);      
} 


/*
*   Dado una matriz cache devuelve el bloque menos usado del set (local), siempre devuelve uno. 
*/
bloque_t* encontrar_LRU(bloque_t* bloques, size_t tope, size_t* extra){
    size_t ins_menor; 
    long int pos_menor = -1;

    for (size_t i = 0; i < tope; ++i){
        if(!bloques[i].es_valido){      
            *extra = i;
            return &bloques[i];
        }
        if(pos_menor == -1 || bloques[i].ins < ins_menor){
            *extra = i;
            ins_menor = bloques[i].ins; 
            pos_menor = i;              
        }
    }
    return &bloques[pos_menor];
}

addr_t addr_crear(size_t dir, size_t block_size, size_t num_sets){
    addr_t addr;
    addr.off = dir & (block_size - 1);
    size_t index = (dir >> ((int)log2((double)block_size)));
    addr.index = index & (num_sets - 1);
    addr.tag = index >> ((int)log2((double)num_sets));
    return addr;
}

void configurar_remplazo(bloque_t* remplazo, char op, addr_t addr, size_t instruccion){
    remplazo->es_valido = true;
    remplazo->tag = addr.tag;
    remplazo->ins = instruccion;
    remplazo->dirty_bit = false;
    if(op == ESCRITURA){
        remplazo->dirty_bit = true;
    }
}


op_result_t* cache_operar(cache_t* cache, char op, size_t dir, size_t instruccion){
    if(!cache) return NULL;
    
    op_result_t* result = malloc(sizeof(op_result_t));
    if(!result) return NULL;
    
    addr_t addr = addr_crear(dir, cache->sets->bloques->tam, cache->S);

    result->operacion = op;
    result->direccion = addr;
    result->instruccion = instruccion;

    set_t set = cache->sets[addr.index];
    for(size_t i = 0; i < set.E; i++){
        
        if(set.bloques[i].es_valido && set.bloques[i].tag == addr.tag){

            result->ant_bloque_ins = set.bloques[i].ins; 
            set.bloques[i].ins = instruccion;
            result->dirty_bit = set.bloques[i].dirty_bit;
            result->op_bloque_off = i;
            
            if(op == ESCRITURA) set.bloques[i].dirty_bit = true;
            
            result->resultado = hit;
            result->valido = set.bloques[i].es_valido;
            return result;
        }
    }

    size_t pos_bloque = 0;
    bloque_t* remplazo = encontrar_LRU(set.bloques, set.E, &pos_bloque);
    result->valido = remplazo->es_valido;
    result->dirty_bit = remplazo->dirty_bit;
    result->ant_bloque_ins = 0;
    result->op_bloque_off = pos_bloque;

    if(!remplazo->es_valido || !remplazo->dirty_bit){

        configurar_remplazo(remplazo, op, addr, instruccion);
        result->resultado = clean_miss;
    }else{

        configurar_remplazo(remplazo, op, addr, instruccion);
        result->resultado = dirty_miss;
    }

    return result;
}