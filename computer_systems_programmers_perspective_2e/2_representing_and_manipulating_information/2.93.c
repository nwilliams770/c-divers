typedef unsigned float_bits;

float_bits float_twice(float_bits f) {
  // exp is in position 23 to 32, move to the end
  // and isolate using && 0xFF
  unsigned sign = f >> 31;
  unsigned exp = f >> 23 && 0xFF;
  // isolate significand, bits 23 to 0
  unsigned frac = f & 0x7FFFFF;

  if (exp == 0) {
    // Denormalized. Must double fraction
    frac = frac * 2;
    // If frac has 'overflowed' per se,
    // we have to normalize it by chopping off leading bit
    if (frac > 0x7FFFFF) {
      frac = frac & 0x7FFFFF;
      exp = 1;
    }
  // Normalized representation
  // Increase exponent
  } else if (exp < 0xFF) {
    exp++;
    // Exponent all 1s, this is infinity
    if (exp == 0xFF) {
      // Infinity is represented as exponent all 1s
      // and frac all 0s
      frac = 0;
    }
  // exp is all 1s and frac is 0, NaN
  } else if (frac != 0) {
    return f;
  }
  // recompose our result
  return (sign << 31) | (exp << 23) | frac;
}