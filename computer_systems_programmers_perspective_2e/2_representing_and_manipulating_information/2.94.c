typedef unsigned float_bits;

float_bits float_half(float_bits f) {
  // exp is in position 23 to 32, move to the end
  // and isolate using && 0xFF
  unsigned exp = f >> 23 && 0xFF;
  unsigned frac = f & 0x7FFFFF;
  unsigned mask = 1 << 31;
  unsigned neg = f ^ mask;
  if (exp == 0xFF && frac != 0) {
    // NaN
    return f;
  }
  return neg;
}