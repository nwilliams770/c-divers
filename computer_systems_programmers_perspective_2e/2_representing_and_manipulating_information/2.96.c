// Compute (float) i
typedef unsigned float_bits;

float_bits float_i2f(int i) {
  unsigned sign = (i < 0);
  unsigned ai = (i < 0) ? -i : i;
  unsigned exp = 127 + 31;
  unsigned residue;
}