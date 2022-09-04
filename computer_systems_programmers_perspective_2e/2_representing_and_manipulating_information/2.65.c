// Return 1 when x contains odd # of 1 bits
// also calculating parity
int odd_ones(unsigned x) {
  /*Use bit-wise ˆ to compute multiple bits in parallel */
  /*Xor bits i and i+16 for 0 <= i < 16 */
  unsigned p16 = (x >> 16) ^ x; /*Xor bits i and i+8 for 0 <= i < 8 */
  unsigned p8 = (p16>> 8) ^ p16; /*Xor bits i and i+4 for 0 <= i < 4 */
  unsigned p4 = (p8 >> 4) ^ p8; /*Xor bits i and i+2 for 0 <= i < 2 */
  unsigned p2 = (p4 >> 2) ^ p4; /*Xor bits 0 and 1 */
  unsigned p1 = (p2 >> 1) ^ p2; /*Least significant bit is 1 if odd number of ones */
  return !(p1 & 1);
}