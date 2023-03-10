#include "cola_asm.h"

.global cola_crear
.global cola_destruir
.global cola_encolar
.global cola_desencolar
.global cola_esta_vacia
.global cola_ver_primero


cola_crear:                /* Se recomienda usar calloc() */
  movq $0x2C, %rdi
  movq $0x8C, %rsi
  call calloc
  	ret



cola_esta_vacia:           /* Se debe usar un conditional move (cmovXX/setXX) */
	movq $1, %rsi
	movq $0, %rax
	cmp %rax, (%rdi)
	cmove %rsi,%rax
  	ret



cola_ver_primero:          /* Se debe usar un salto condicional */
	movq $0, %rax
	movq (%rdi), %rsi
	cmp $0, %rsi
	je fin
	movq (%rsi), %rax

fin:
  ret



cola_encolar:              /* Se debe usar un conditional move */
  push %r12
  push %r13
  push %r14
	movq %rsi, %r12
	movq %rdi, %r13
	movq $2, %rdi
	movq $8, %rsi
  call calloc
  movq %rax, %r14
	movq %r13, %rax
	movq %rax, %rdi
	call cola_esta_vacia
	cmpl $1, %eax
    jne L1
      movq %r13, %rax
      movq %r14, %rdx
      movq %rdx, (%rax)
    jmp L2

L2: 
    movq %r14, %rax
    movq %r12, %rdx
    movq %rdx, (%rax)
    movq %r13, %rax
    movq %r14, %rdx
    movq %rdx, 8(%rax)
    movl $1, %eax
    pop %r14
    pop %r13
    pop %r12
  ret
L1:
    movq %r13, %rax
    movq 8(%rax), %rax
    movq %r14, %rdx
    movq %rdx, 8(%rax)




cola_desencolar:           /* Se recomienda usar dos saltos condicionales + un cmov */
  push %rbp
  movq %rdi, 16(%rbp)
	movq 16(%rbp), %rax
    movq %rax, %rdi
    movl $0, %eax
    call cola_esta_vacia
	test %eax, %eax
    jmp	 fin_desencolar
      movq 16(%rbp), %rax
      movq (%rax), %rax
      movq %rax, 8(%rbp)
      movq 8(%rax), %rdx
      movq 16(%rbp), %rax
      cmpq %rax, %rdx
    jne  desencolar
    movq $0, 8(%rax)
	  movq %r12, %rax

desencolar:
    movq 0(%rbp), %rax
    movq 8(%rax), %rdx
    movq 16(%rbp), %rax
    movq %rdx, (%rax)
    movq 0(%rbp), %rax
    movq (%rax), %rax
    movq %rax, %r12
    movq 0(%rbp), %rax
    movq %rax, %rdi
    call free
    pop %rbp  



fin_desencolar:
    pop %rbp
	  leave
  ret



cola_destruir:             /* Sin restricciones */
    movl $0, %eax
    test %eax,%eax
    call cola_desencolar
    call free
	ret