/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    //if x is positive, get its negative by ~x+1, then the sign bit will be 1
    //if x is negative, its sigh bit is 1
    //only if x is 0, both will result in 0
    return ((((x>>31)&1) | (((~x+1)>>31)&1))^1);
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    int m = 0x11 | (0x11<<8);
    int mask = m | (m<<16); //make a mask 0x11111111
    int count = (x&mask) + ((x>>1)&mask) + ((x>>2)&mask) + ((x>>3)&mask); //4 bit a unit, sum num of 1s
    count = (count&0xF) + ((count>>4)&0xF) + ((count>>8)&0xF) + ((count>>12)&0xF) + ((count>>16)&0xF)
            + ((count>>20)&0xF) + ((count>>24)&0xF) + ((count>>28)&0xF);
    //sum num of 1s in all 4-bit-unit (8 units in total)
  return count;
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
    return ~(~x&~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
    unsigned repeat;
    int sign, result;
    repeat= (x << (32-n));
    repeat = repeat >> (32-n); //n bits repeat pattern with 0s before it
    result = (repeat | ((repeat << (n-1)) << 1));
    sign = (n<<1) - 32; //if n*2 < 32, sign bit will be 1, else 0
    //sign>>31 get -1 or 0, -1*sign is either positive or 0
    result = result | ((result << (31 - (sign>>31)*sign))<<1);
    sign = (n<<2) -32;
    result = result | ((result << (31 - (sign>>31)*sign))<<1);
    sign = (n<<3) -32;
    result = result | ((result << (31 - (sign>>31)*sign))<<1);
    sign = (n<<4) -32;
    result = result | ((result << (31 - (sign>>31)*sign))<<1);
  return result;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    ///for positive int, 0000 can be omit, for negative int, 1111 can be omit
    /// ~ bitwise negation
    int sign = x>>31; //0xFFFFFFFF or 0x00000000
    // sign & ~x: ~x or 0
    // ~sign & x: 0 or x
    // +: ~x or x
    // >>(n + (~1+1)) must result 0 in order to fit
    return !(((~x & sign) + (x & ~sign)) >> (n + (~1+1)));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    return ((x>>(n<<3))&0xFF);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //consider MSB only, if x and y have different sign, use sign to determine the result
    //if x and y have same sign, use value to determine the result
    int sign = (x^y)&x; //the MSB is 1 only when x is negative and y is postive
    int diff = y + (~x+1); //y-x
    int equal = !diff; //diff=0, true, else false
    // ~(x^y) & ~diff: return true if x and y have same sign, and y >= x
    int value = ~(x^y) & ~diff;
    // value | sign: either one is true (i.e. MSB is 1)
    // & (1<<31): convert the result to 1000000(negative) or 0(positive)
    int result = (value | sign) & (1<<31);
    // !!result: negative-true, positive-false; equal: true. either true returns true
    return ((!!result) | equal);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    // x>>31 get the signed bit, 0 positive, 1 negative
    // if x is 0, !x is 1(true)
    // | either negative or zero gets true
    // ! revert it
  return !((x>>31) | !x ) ;
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
    //(~0)<<(31-n))<<1: ~0 is 0xFFFFFFFF, cannot shift 32 at once so shift 31 then shift 1.
    //revert it to get 0..01111 (cannot use ^ since the MSB can be 0)
  return (x>>n)&~(((~0)<<(31+(~n+1)))<<1);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return (1<<31);
}
