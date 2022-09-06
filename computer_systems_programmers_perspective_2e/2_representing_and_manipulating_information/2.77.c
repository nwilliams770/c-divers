int divide_power2(int x, int k) {
  // Generate a mask to calculate bias
  // If x < 0; arithmetic shift will yield a mask of all 1s
  // all 0s for x > 0
  int mask = x >> (sizeof(int) << 3 - 1);
  // Bias is (1 << k) - 1 for x < 0; thanks to our mask if x > 0, bias will be 0
  int bias = mask & ((1 << k) - 1);
  return (x + bias) >> k;
}