float sum_elements(float a[], unsigned length) {
  int i;
  float result = 0;

  for (i = 0; i <= length-1; i++) {
    result += a[i];
  }
  return result;
}
// unsigned arithmetic is modular addition (https://en.wikipedia.org/wiki/Modular_arithmetic)
// unsigned 0 - (int) 1 => unsigned 0 - unsigned 1 => UMAX
// To resolve this code:
// - length should be type int
// OR
// - i < length