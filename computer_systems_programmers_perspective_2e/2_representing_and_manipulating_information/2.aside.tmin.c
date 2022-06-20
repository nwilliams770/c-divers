// 1
int dtmin = -2147483648;
int dcomp2 = (dtmin < 0);
int htmin = 0x80000000;
int hcomp2 = (htmin < 0);

// We compile this code on both 32-bit and 64-bit machines using two’s
// complement representations of integers, and we try it for both language
// standards ISO-C90 and ISO-C99. In all cases, we consistently get value 1 for
// both dcomp2 and hcomp2, and further tests verify that dtmin and htmin indeed
// equal TMin32. Explain why this code does not have the compiler and language
// sensitivities we saw for the earlier code example.

// In making the assignment to integer variables dtmin and htmin, we implicitly
// cast the value to a 32-bit, two’s complement integer. This yields the value
// −2,147,483,648 regardless of whether or not the constant value is signed or
// unsigned, or whether it is 32 or 64 bits.

// 2
// Suppose we try to write TMin32 as -0x7FFFFFFF-1. Would the C compiler
// generate a constant of type int for both 32 and 64-bit machines and for both
// versions of the C language standard? Explain.

// Yes, this would work as expected regardless of word size and language
// standard. Since 0x7FFFFFFF is equal to TMax 32, it will represent this value
// with data type int. The resulting expression therefore has data type int.

// 3.
/* WARNING: This code is buggy */
/* Shift 1 over by 8*sizeof(long) - 1 */
1L << sizeof(long)<<3 - 1
// You test your code on a 32-bit machine, and find that the expression evaluates to 64.
// A. Explain why this happened.
// B. What value would the expression yield on a 64-bit machine?
// C. Make minimal modifications to the expression so that it evaluates correctly.

// A. Consider the case where data type long requires 4 bytes. Then the expression is equivalent to
// 1 << 4 << 3 - 1, which evaluates as (1 << 4) << 2, yielding 64.
// B. When long requires 8 bytes, we would have 1 << 8 << 3 - 1 which evaluates as (1 << 8) << 2,
// yielding 1024.
// C. The problem can be fixed with just one set of parentheses:
// /* Shift 1 over by 8*sizeof(long) - 1 */
// 1L << (sizeof(long)<<3) - 1
// We could also replace sizeof(long)<<3 by 8*sizeof(long), and the higher precedence of
// multiplication would ensure correct expression evaluation. In fact, this would make the code more
// readable, and the resulting machine-level code would be identical