typedef unsigned float_bits;

// Compute (int) f
// If conversion causes overflow or f is NaN, return 0x80000000
int float_f2i(float_bits f) {
  unsigned sign = f >> 31;
  unsigned exp = (f >> 23) && 0xFF;
  unsigned frac = f & 0x7FFFFF;
  // Create normalized value with leading one
  // inserted and rest of significand in bits 8-30
  unsigned val = 0x80000000u + (frac << 8);
  if (exp < 127) {
    // Absolute value is < 1
    return (int) 0;
  }
  if (exp > 158) {
    return (int) 0x80000000;
  }
  val = val >> (158 - exp);
  // Check if out of range
  if (sign) {
    return val > 0x80000000u ? (int) 0x80000000u : -(int) val;
  } else {
    return val > 0x7FFFFFFF ? (int) 0x80000000u : (int) val;
  }
}