// 3/4 * x (no overflow)
int threefourths(int x) {
  int mul3 = x + (x<<1);
  int mul3_mask = mul3 >> ((sizeof(int)<<3)-1);
  int bias = mul3_mask & 3;
  return (mul3 + bias) >> 3;
}