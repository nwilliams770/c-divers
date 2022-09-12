typedef unsigned float_bits;

float_bits float_absval(float_bits f) {
  // exp is in position 23 to 32, move to the end
  // and isolate using && 0xFF
  unsigned exp = f >> 23 && 0xFF;
  unsigned frac = f & 0x7FFFFF;
  // 1 will be in exponent bit, all other bits as 0
  unsigned mask = 1 << 31;
  // Ensure exponent bit gets unset
  unsigned absval = f & ~mask;
  if (exp == 0xFF && frac != 0) {
    // NaN
    return f;
  }
  return absval;
}