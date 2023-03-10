#ifndef STRUTIL_H
#define STRUTIL_H


#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * Devuelve una nueva cadena con los primeros ‘n’ caracteres de la cadena
 * ‘str’. 
 * Devuelve NULL en caso de error.
 */
char *substr(const char *str, size_t n);

/*
 * Devuelve un vector de strings a partir de los substrings del string original separados por el carácter enviado. 
 * En la última posición habrá un NULL. Devuelve NULL en caso de error.
 */
char **split(const char *str, char sep);

/*
 * Devuelve la cadena resultante de unir todas las cadenas del arreglo
 * terminado en NULL ‘str’ con ‘sep’ entre cadenas. 
 * Devuelve NULL en caso de error.
 */
char *join(char **strv, char sep);

/*
 * Recibe una cadena y devuelve true si todos los caracteres de la cadena son digitos,
 * de lo contrario, devuelve false.
 */
bool es_string_numerico(char* cad);

/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene hasta el primer NULL que encuentre.
 */
void free_strv(char *strv[]);


/*
 * Recibe un arreglo dinámico de cadenas, y devuelve la cantidad de cadenas que contiene.
 */
size_t tamanio_split(char** strv);

#endif  // STRUTIL_H