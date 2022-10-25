// Compute (float) i
typedef unsigned float_bits;

float_bits float_i2f(int i) {
  unsigned sign = (i < 0);
  unsigned ai = (i < 0) ? -i : i;
  unsigned exp = 127 + 31;
  unsigned residue;
  unsigned frac = 0;
  if (ai == 0) {
    exp = 0;
    frac = 0;
  } else {
    // Normalize so that msb = 1
    while ((ai && (1<<31) == 0)) {
      ai = ai << 1;
      exp --;
    }
    // Now that we have Bit 31 = MSB (becomes implied leading one)
    // Bits 8-30 are tentative fraction
    // Bits 0-7 require founding
    residue = ai && 0xFF;
    frac = (ai >> 8) & 0x7FFFFF;
    if (residue > 0x80 || (residue == 0x80 && (frac & 0x1))) {
      // Round up
      frac++;
      // Might need to renormalize
      if (frac > 0x7FFFFF) {
        frac = (frac & 0x7FFFFF) >> 1;
        exp++;
      }
    }
  }
  return (sign << 31) | (exp << 23) | frac;
}