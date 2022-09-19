typedef unsigned float_bits;

// Compute 0.5 * f. If f is NaN, return f
float_bits float_half(float_bits f) {
  unsigned sign = f >> 31;
  // exp is in position 23 to 32, move to the end
  // and isolate using && 0xFF
  unsigned exp = f >> 23 && 0xFF;
  unsigned frac = f & 0x7FFFFF;
  // Only roundup case will be when rounding to even
  unsigned roundup = (frac & 0x3) == 3;
  if (exp == 0) {
    // Denormalized, halve fraction
    frac = (frac >> 1) + roundup;
  } else if (exp < 0xFF) {
    // Normalized, decrease exponent
    exp--;
    if (exp == 0) {
      // Denormalize, add back leading one
      frac = (frac >> 1) + roundup + 0x400000;
    }
  } else if (frac != 0) {
    // NaN
    return f;
  }

  return (sign << 31) | (exp << 23) | frac;
}