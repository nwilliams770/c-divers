int mul3div4(int x) {
 int mul3 = (x << 1) + 1;
 int mask = mul3 >> (sizeof(int) << 3 - 1);
  // Bias is (1 << k) - 1 for x < 0; thanks to our mask if x > 0, bias will be 0
 int bias = mask & 3;
 return (mul3 + bias) >> 2;
}