int div16(int x) {
  // Compute the bias to be 0 for x >= 0 or 15 for x < 0
  // Right arithmetic shift on two's complement number
  // produces all 1s (x < 0) or all 0s (x >= 0)
  // We then mask that with 15 (in hex) to get either
  // 0 or 15
  int bias = (x >> 31) & 0xF;
  return (x + bias) >> 4;
}