// Rotating left shift. 0 <= n < w
unsigned rotate_left(unsigned x, int n) {
  // x = 0b0111 0001 => 0b 1000 1011
  // n = 3
  // x << 3
  // 0b1000 1000

  // x >> (sizeof(unsigned) << 3 - n)
  // 0b0000 0011
  return (x >> n) | ((sizeof(unsigned) << 3) - n);
}