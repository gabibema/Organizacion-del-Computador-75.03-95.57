#define _POSIX_C_SOURCE 200809L
#include "strutil.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char* substr(const char* str, size_t n){
    return strndup(str, n);
}

char **split(const char *str, char separador){
    if(str == NULL) {
        return NULL;
    }
    
    if(str[0] == '\0'){
        char** lista = malloc(sizeof(char*) * 2);
        lista[0] = substr("",0);
        lista[1] = NULL;
        return lista;
    }

    size_t cantidad_separadores = 0;
    for(int i = 0; str[i] != '\0'; i++){
        cantidad_separadores += str[i] == separador;
    }

    char** lista = malloc(sizeof(char*) * (cantidad_separadores + 2));
    if(lista == NULL) return NULL;

    for(int i = 0, comienzo_siguiente_subcadena = 0, lista_index = 0; str[i] != '\0'; i++){
        if(str[i] == separador){
            lista[lista_index] = substr(str + comienzo_siguiente_subcadena, (size_t) (i - comienzo_siguiente_subcadena));
            lista_index++;
            comienzo_siguiente_subcadena = i + 1;
        }
        if(str[i + 1] == '\0'){
            lista[lista_index] = substr(str + comienzo_siguiente_subcadena, (size_t) (i + 1 - comienzo_siguiente_subcadena));
        }
    }
    lista[cantidad_separadores + 1] = NULL;
    return lista;
}

char *join(char **strv, char sep){
    size_t len_cadena = 0;
    for(int i = 0; strv[i] != NULL; i++){
        len_cadena += strlen(strv[i]) + (sep != '\0'); 
    }
    char* cadena = calloc(sizeof(char), (len_cadena + 1));
    char* ultimo_lugar = cadena;
    for(int i = 0; strv[i] != NULL; i++){   
        ultimo_lugar = stpcpy(ultimo_lugar, strv[i]);
        if(strv[i + 1] != NULL){
            *ultimo_lugar = sep;
            ultimo_lugar += sep != '\0';
        }
    }
    return cadena;
}

bool es_string_numerico(char* cad){
    for(int i = 0; cad[i] != '\0'; i++){
        if(isdigit(cad[i]) == 0){
            return false;
        }
    }
    return true;
}

void free_strv(char *strv[]){
    for(int i = 0; strv[i] != NULL; i++)
        free(strv[i]);
    free(strv);
    return;
}

size_t tamanio_split(char** strv){
    if(!strv) return 0;
    size_t cantidad = 0;
    while(strv[cantidad] != NULL)
        cantidad++;
    return cantidad;
}