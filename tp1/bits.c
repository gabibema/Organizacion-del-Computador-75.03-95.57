/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
//1

const int MASCARA_BITS_IMPAR = 0b1010;
const int BITS_TOTALES = 32;
const int BIT_SIGNO = 1;
const int FUERA_DE_RANGO = 0x80000000u;
const int MAX_E = 31;

/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
  int mascara = MASCARA_BITS_IMPAR;
  mascara = (mascara << 4)  | mascara;
  mascara = (mascara << 8)  | mascara;
  mascara = (mascara << 16) | mascara;

  return !(!(x & mascara));
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int tmin = (1 << 31);
  int tmax = tmin - 1;

  return !(x ^ tmax);
}


/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  int tmin = (1 << 31);
  return !(x ^ tmin);
}

/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  return !x;
}

/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
  int bits_impares = MASCARA_BITS_IMPAR;
  bits_impares = bits_impares << 4  | bits_impares;
  bits_impares = bits_impares << 8  | bits_impares;
  bits_impares = bits_impares << 16 | bits_impares;
  return bits_impares;
}

//2
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  x = x & (x >> 16);
  x = x & (x >> 8);
  x = x & (x >> 4);
  x = x & (x >> 2);
  return (x & 1);
}

/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
  x = x | x >> 16;
  x = x | x >> 8;
  x = x | x >> 4;
  x = x | x >> 2;
  return x & 1;
}

/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  return (x << 31) >> 31;
}

/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  return !(x ^ y);
}

/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
  return !isEqual(x,y);
}

/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  return x & (~x + 1);
}

/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
    return (x >> 31) | !!x;
}

//3
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {

  	int not_y = ~y;
    int opuesto_y = not_y + 1;
    int diferencia_x_y = x + opuesto_y;
	return  ( ( ( diferencia_x_y & ( x ^ not_y ) ) | ( x & not_y ) )>> 31 ) & 1;
}

/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  return !!(x >> 31);
}

/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  int mask_shift;

  mask_shift = BITS_TOTALES - n;

  return  ((unsigned)x << n ) | ( (unsigned)x >> mask_shift); //Casteo a unsigned para evitar problemas de desplazamiento
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int mask = ((1 << 31) >> n) << 1;
  return (x >> n) & ~mask;
}

//4
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    int mask = 0b10001;
    int bits;

    mask = mask | mask << 8;
    mask = mask | mask << 16;
    mask = mask | mask << 24;

    bits = x & mask;
    bits = bits + ((x >> 1) & mask);
    bits = bits + ((x >> 2) & mask);
    bits = bits + ((x >> 3) & mask);
    
    bits = bits + (bits >> 16);
    mask = 0b1111 | 0b1111 << 8;
    bits = (bits & mask) + ((bits >> 4) & mask);
    return (bits + (bits >> 8)) & 0x3F;
}


/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int signo;
    int bit_0, bit_1, bit_2, bit_4, bit_8, bit_16;

    signo = x >> 31;
    x = (signo & ~x) | (~signo & x); //invierto los números negativos
    

    //calculo un log2(x) para ver la cantidad de bits necesarios


    bit_16 = !!(x >> 16) << 4;
    x = x >> bit_16;
    
    bit_8 = !!(x >> 8) << 3;
    x = x >> bit_8;
    
    bit_4 = !!(x >> 4) << 2;
    x = x >> bit_4;
    
    bit_2 = !!(x >> 2) << 1;
    x = x >> bit_2;
    
    bit_1 = !!(x >> 1);
    x = x >> bit_1;
    
    bit_0 = x;

    return BIT_SIGNO + bit_0 + bit_1 + bit_2 + bit_4 + bit_8 + bit_16;  
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  int positivo = !(x>>31);
  int potencia_2 = !((x + ~0) & x); //1 si es potencia 2
  return ( (!!x) & positivo & potencia_2);
}

/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x) {
    int contador;
    int mask1_aux = (0b1010101)|(0b1010101<<8);
    int mask1 = (mask1_aux)|(mask1_aux<<16);

    int mask2_aux = (0b110011)|(0b110011<<8);
    int mask2 = (mask2_aux)|(mask2_aux<<16);

    int mask3_aux = (0b1111)|(0b1111<<8);
    int mask3 = (mask3_aux)|(mask3_aux<<16);
    
    int mask4 = (0b11111111)|(0b11111111<<16);
    int mask5 = (0b11111111)|(0b11111111<<8);
    
    x=~x;
    x=((x)>>1)|x;
    x=((x)>>2)|x;
    x=((x)>>4)|x;
    x=((x)>>8)|x;
    x=((x)>>16)|x;

    contador = (x&mask1)+((x>>1)&mask1);
    contador = (contador&mask2)+((contador>>2)&mask2);
    contador = (contador + (contador >> 4)) & mask3;
    contador = (contador + (contador >> 8)) & mask4;
    contador = (contador + (contador >> 16)) & mask5;
    return  32 + (~contador+1); // 32 - contador
}
//float
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

const int MASK_EXP = 0x7F800000; // 0111 1111 1000....
const int MASK_LIMPIA_FRACCION = 0xFF800000; //	1111 1111 10000 ...
const int MASK_FRACCION = 0x7FFFFF;
const int MASK_SIGNO = 0x80000000; // 1000.... bit 32

const int BIAS = 127;
const int MAX_EXP = 255;


int floatFloat2Int(unsigned uf) {

  int sign = uf & MASK_SIGNO; //signo del número
  int exp = (uf & MASK_EXP) >> 23; //exponente
  int frac = uf & MASK_FRACCION; //fracción
  int result = 0;
  int e = 0;

  //Caso infinito o NaN
  if(exp  == MAX_EXP)
    return FUERA_DE_RANGO;
  
  //caso de números entre 0 y 1 sin incluir el 1
  if((exp < BIAS) || !(uf << 1)) 
    return 0;
  
  e = exp - BIAS;

  //Representación fuera del rango de e
  if (e >= MAX_E)
    return FUERA_DE_RANGO;
  
  frac = frac | (MASK_FRACCION + 1);

  if(e < 23)
    result = frac >> (23 - e);
  else
    result = frac << (e - 23);

  if (sign < 0)
    return (~result + 1);
  else
    return result;	
}
/* 
 * floatUnsigned2Float - Return bit-level equivalent of expression (float) u
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

unsigned floatUnsigned2Float(unsigned x) {

  unsigned exp = BIAS+31;
  unsigned residuo;
  unsigned frac = 0;


  if (x == 0) {
    exp = 0;
    frac = 0;

  } else {
    
    while ((x & (1<<31)) == 0) {
      x = x << 1;
      exp--;
    }

    residuo = x & 255;
    frac = (x >> 8) & MASK_FRACCION; /* 23 bits */
    if (residuo > 128 || (residuo == 128 && (frac & 0x1))) {
      
      frac ++;
      
      if (frac > MASK_FRACCION) {
        frac = (frac & MASK_FRACCION) >> 1;
        exp++;
      }
    }
  }
  return (exp << 23) | frac;

}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */

const int INFINITO = 2139095040U;
unsigned floatPower2(int x) {
 int exp=x+BIAS;            

  if(exp<=0) //Caso número negativo o 0
    return 0;       

  else if(exp>=255) //Infinito
    return INFINITO;

  return exp<<23;
}
/* 
 * floatScale64 - Return bit-level equivalent of expression 64*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 35
 *   Rating: 4
 */


unsigned floatScale64(unsigned uf) {
    int sign = uf & MASK_SIGNO; // 1000.....
    int i = 6;

    while (i > 0) {

      int exp = uf & MASK_EXP;
      int es_exponente_nulo = !exp;

      if (es_exponente_nulo) {
        uf = sign | (uf << 1);
      } else if (exp != MASK_EXP) {
        uf = uf + 0x800000;
        exp = uf & MASK_EXP;
        
        //Caso infinito
        if (exp == MASK_EXP) {
            uf = uf & MASK_LIMPIA_FRACCION;
        }
      }
      i--;
    }

    return uf;
}
