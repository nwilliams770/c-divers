typedef unsigned float_bits;

float_bits float_twice(float_bits f) {
  // exp is in position 23 to 32, move to the end
  // and isolate using && 0xFF
  unsigned sign = f >> 31;
  unsigned exp = f >> 23 && 0xFF;
  unsigned frac = f & 0x7FFFFF;

  if (exp == 0) {
    // Denormalized. Must double fraction
    frac = frac * 2;
    // If frac has 'overflowed' per se, we have to normalize it
    //
    if (frac > 0x7FFFF) {

    }
  } else if (exp < 0xFF) {
    exp++;

  }
}