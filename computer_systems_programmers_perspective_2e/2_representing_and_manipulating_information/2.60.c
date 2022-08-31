unsigned replace_byte(unsigned x, int i, unsigned char b) {
  x = x & (0x00 << (i * 8));
  return x | (b << (i * 8));
}