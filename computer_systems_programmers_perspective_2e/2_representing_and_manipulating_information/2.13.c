// bit set, sets result to 1 at each bit position where m is 1
// 0011 0011, 1100 1100 => 1111 1111
// x | m
int bis(int x, int m);
// bit clear, sets result to 0 at each bit position where m is 1
// 0011 0011, 0010 0010 => 0001 0001
// x ^ m
int bic(int x, int m);

int bool_or(int x, int y) {
  int result = bis(x, y);
  return result;
}

int bool_xor(int x, int y) {
  int result = bic(x, y);
  return result;
}