#define M
#define N
int arith(int x, int y) {
  int result = x*M + y/N;
  return result;
}

int optarith(int x, int y) {
  int t = x;
  x <<= 5;
  x -= t;
  if (y < 0) y += 7;
  y >>= 3;
  return x + y;
}

// M is 31 and N is N