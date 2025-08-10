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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    // 主要是德摩根律的运用
  return ~((~x)&(~y)) & ~(x&y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    //补码的最小值是10000....(32bits),注意不是1111...(32bits),后者是-1,让1左移31位即可
  return 1<<31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // Tmax即为补码的最大值,左边判断的是x是否为Tmax
  // Tmax 0111.... 满足 Tmax + 1 = 10000....(-Tmax),即为正溢出,再对1000...按位取反之后,得到的还是Tmax
  // 右边是验证x != -1 (111....)这种特殊情况,因为-1(111...) + 1 变成00000,也满足x + 1 ^ x == 1 .
  //第一个条件：~(x+1) == x
  //第二个条件：x+1 != 0
  return (!((~(x + 1)) ^ x)) & (!!((x + 1) ^ 0x0));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    //0xA 是二进制 1010，其中奇数位是 1，偶数位是 0。
    int A = 0xA;
    //(A << 4) 把 1010 左移 4 位，得到 1010 0000。
    int AA = A | (A << 4);     //A | (A << 4) 就是：1010 1010 (AA)
    //(AA << 8) 得到 1010 1010 0000 0000
    // 再用 0000 0000 1010 1010 
    // |    1010 1010 0000 0000
    int AAAA = AA | (AA << 8); //得到1010 1010 1010 1010 (AAAA)
    //下面同理
    int mask = AAAA | (AAAA << 16);
    return !((x & mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // 对于正数补码,将其按位取反之后 + 1 就可以得到它的相反值
  // e.g 1 = 0000...01 ; ~1 = 1111..10  
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) { 
  
  // 1. 检查是否为 ASCII 数字的高两位是 00（ASCII 数字的二进制前两位是 00 11）
  //    将 x 右移 6 位，如果结果不是 0，说明高位不符合要求
  int a = x >> 6;
  int cond1 = !a; // cond1 = 1 表示高 2 位是 00
  // 2. 检查 ASCII 数字的高 4 位是否是二进制 0011 (即十进制 3)
  //    将 x 右移 4 位，得到高 4 位；与 0b0011 比较是否相等
  int b = x >> 4;
  int cond2 = !(b ^ 0b11); // cond2 = 1 表示高 4 位是 0011
  // 3. 检查低 4 位是否小于十进制 10
  //    先取低 4 位 (0xF = 1111b)，再减去 0xA，看是否为负数
  int c = x & (0xF); // 取低 4 位
  int res = c + negate(0xA); // 等价于 c - 0xA
  int cond3 = !!(res >> 31); // 如果为负数，则最高位是 1 → cond3 = 1
  // 只有 cond1、cond2、cond3 都为 1 时，才是 '0' ~ '9'
  return cond1 & cond2 & cond3;

}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
//功能：如果 x ≠ 0，则返回 y，否则返回 z
int conditional(int x, int y, int z) {


  //1. !!x : 归一化为布尔值（0 → 0，非 0 → 1）
  //e.g !!5 = 1, !!0 = 0
  int mask = ((!!x) << 31) >> 31;
  /*
     2. mask 的构造：
        (!!x)   → 1 或 0
        << 31   → 如果是 1 则变成 0x80000000，0 则是 0x00000000
        >> 31   → 进行算术右移（保留符号位）
                   如果是 1 → 变成全 1 (0xFFFFFFFF)
                   如果是 0 → 变成全 0 (0x00000000)
        所以：
        当 x ≠ 0 → mask = 0xFFFFFFFF
        当 x = 0 → mask = 0x00000000
  */
  return ((~mask) & z ) | (mask & y);
  /*
     如果 x ≠ 0：
         mask = 全 1 → (~mask) = 全 0
         (~mask) & z = 0
         (mask) & y = y
         → 返回 y
     
     如果 x = 0：
         mask = 全 0 → (~mask) = 全 1
         (~mask) & z = z
         (mask) & y = 0
         → 返回 z
  */
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int a = x >> 31;
  int b = y >> 31;
  int c = a ^ b;
  int case1 = c & a;
  int case2 = ~c & ( ~((y + (~x + 1)) >> 31));
  int result = case1 | case2;
    return !!result;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    int bit16 = x | ( x >> 16);
    int bit8 = bit16 | (bit16 >> 8);
    int bit4 = bit8 | (bit8 >> 4);
    int bit2 = bit4 | (bit4 >> 2);
    int bit1 = bit2 | (bit2 >> 1);
    return (bit1 & 1) ^ 1;
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
  int b16, b8, b4, b2, b1, b0;
    int sign = x >> 31;
    x = (sign & ~x) | (~sign & x);

    b16 = !!(x >> 16) << 4;
    x = x >> b16;
    b8 = !!(x >> 8) << 3;
    x = x >> b8;
    b4 = !!(x >> 4) << 2;
    x = x >> b4;
    b2 = !!(x >> 2) << 1;
    x = x >> b2;
    b1 = !!(x >> 1);
    x = x >> b1;
    b0 = x;
    return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int exp = (uf >> 23) & 0xFF;
    int sign = uf & (1 << 31);
    if (exp == 0xFF) {
        return uf;
    }

    if (exp == 0x0) {
        return (uf << 1) | sign;
    }

    exp = exp + 1;
    if (exp == 0xFF) {
        return 0x7F800000 | sign;
    }
    else {
        int frac = uf & 0x7FFFFF;
        return (frac | exp << 23) | sign;
    }
}
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
int floatFloat2Int(unsigned uf) {
  int exp = (uf >> 23) & 0xFF;
    int frac = uf & 0x7FFFFF;
    int sign = uf & (1 << 31);  // negative 0x80000000, positive 0x0.
    int frac1 = frac | 0x800000;  // Add the hidden 1 in front of frac
    int biasedExp = exp - 127; // E = e - Bias, Bias = 127 = 0x7F, -bias = 0xFFFFFF81

    if (exp == 0xFF) return 0x80000000u;  // if out of range, return 0x80000000

    if (exp == 0x0) return 0;  // if de-norm number, means its range is (-1, 1)

    if (biasedExp > 31) return 0x80000000;
    else if (biasedExp < 0) return 0;

    if (biasedExp > 23) frac1 <<= (biasedExp - 23);
    else frac1 >>= (23 - biasedExp);

    if (sign) return ~frac1 + 1;  // if negative number
    else if (frac1 >> 31) return 0x80000000;  // if frac1 overflows, return 0x80000000;
    else return frac1;
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
unsigned floatPower2(int x) {
    int exp = x + 127;
    if (exp <= 0) return 0;
    if (exp >= 255) return 0xff << 23;
    return exp << 23;
}
