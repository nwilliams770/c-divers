// Return 1 if x and y can be added without overflow
int uadd_ok(unsigned x, unsigned y) {
  if ((__UINTMAX_MAX__ - x) > y) {
    return 1;
  }
  return 0;

  // unsigned sum = x + y;
  // return sum >= x;
}