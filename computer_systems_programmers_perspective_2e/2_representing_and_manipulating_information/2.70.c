// Return 1 when x can be represented as n-bit, 2's complement number;
// 0 otherwise
// Assume 1 <= n <= w
int fits_bits(int x, int n) {
  // Mask to 0 out n bits of x
  int mask = ~(2 << (n- 1) - 1);
  // Determine if any bits set
  return !(x & mask);
}

int fits_bits(int x, int n) {
// Use left shift then right shift to sign extend from n bits to full int
  int count = (sizeof(int)<<3)-n;
  int leftright = (x << count) >> count;
  // See if still have same value
  return x == leftright;
}