# Organizacion-del-Computador-75.03-95.57


## TP1: representación de datos
El archivo bits.c incluido en el esqueleto tiene un total de 23 funciones que se deben implementar. Cada una de estas funciones implementa una cierta operación sobre enteros o números en punto flotante. Es el único archivo que se debe modificar.

Las funciones aparecen en el archivo en orden de dificultad creciente. Se incluye, para cada función en el archivo bits.c, una cabecera con los siguientes apartados:

Legal ops: la lista de operadores permitidos
Max ops: el número máximo de operaciones
Rating: cantidad de puntos que la función contribuye al total de puntos del lab.

## TP2: Lenguaje assembly
Se pide implementar en assembly x86_64 una cola enlazada de punteros genéricos. Para ello se dispone de los siguientes archivos:

* el archivo cola.h contiene la lista de primitivas a implementar, así como la descripción de cada una de ellas. (Nota sobre pre-condiciones: para todas las primitivas que reciben un puntero cola_t *, se puede asumir que este puntero nunca es nulo y que fue obtenido previamente mediante cola_crear).

* el archivo cola_defs.c contiene las definiciones privadas de los struct cola y nodo; la implementación en assembly debe ser compatible con estas definiciones, que no está permitido cambiar.

* en un archivo aparte, cola_asm.h, se proporcionan constantes con el tamaño de dichos structs, y los offsets de cada uno de sus miembros; así, se puede incluir este archivo desde un el archivo .S para usar constantes simbólicas en lugar de valores numéricos fijos en la implementación de las primitivas.

* el archivo cola_impl.S contiene el esqueleto de las funciones a implementar, así como el “budget” (o presupuesto) de instrucciones condicionales que se puede usar para cada una de ellas. Esto quiere decir que, para la mayoría de las funciones, se indica si se la debe implementar con saltos o conditional moves, y cuántos está permitido usar.)

Finalmente, el archivo pruebas_cola.c contiene una lista de pruebas unitarias sugeridas para verificar el correcto comportamiento de la cola. El archivo no está completo, pero se proporciona un segundo archivo, pruebas_pila.c, que se puede usar como guía para finalizar las pruebas de la cola.

## TP4: Simulador de caché
En este trabajo práctico se implementará un simulador de caché parametrizado. Serán configurables las distintas características de la caché simulada (tamaño, número de sets y asociatividad), y el programa principal leerá y simulará una secuencia de operaciones desde un archivo de trazas.

La implementación del simulador debe realizarse en C (versión del estándar C11). Se pueden usar todas las funciones de la biblioteca estándar de C, incluyendo extensiones de GNU.

## TP5: Arquitectura
Este trabajo consta de 2 partes, donde se plantea el estudio de la arquitectura Y86-64 vista en clase (ver libro [BRY15]) y su modificación utilizando el lenguaje HCL.

Parte A
Para esta primera parte se debe implementar en assembler Y86-64 las tres funciones del archivo sim/misc/examples.c. Cada función debe ir en un archivo separado:

sum.ys: programa a partir de la función sum_list()
rsum.ys: ídem, rsum_list()
copy.ys: ídem, copy_block()
Estos archivos tienen que ser programas completos ejecutables tanto por el intérprete de instrucciones yis como por el simulador ssim. Para ello, deben incluir variables globales los datos sobre los que trabajar (ver valores en archlab.pdf), así como un stack. Se puede usar como punto de partida el archivo sim/y86-code/asum.ys.

Parte B
En esta parte se desea modificar el archivo sim/seq/seq-full.hcl para añadir la instrucción IADDQ, que suma un inmediato a un registro (por ejemplo: iaddq $8,%rax). Para ello se deben configurar las distintas etapas y señales, añadiendo referencias a IIADDQ donde corresponda.

Parte C
Esta parte consiste en modificar dos archivos para lograr que la ejecución de cierto código corra lo más rápido posible. Estos archivos son el código ys de una función y la implementación PIPE de la aquitectura.

A diferencia de los anteriores, en este caso se debe trabajar en el directorio sim/pipe.

El archivo ncopy.ys contiene la implementación de una función que copia un arreglo de enteros de una dirección src a una dirección dst.

El archivo pipe-full.hcl implementa, en código HCL, la arquitectur PIPE vista en clase.
