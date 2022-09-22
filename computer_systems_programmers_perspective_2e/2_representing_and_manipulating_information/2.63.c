unsigned srl(unsigned x, int k) {
  // Perform shift arithmetically, e.g. replaced with 0s
  unsigned xsra = (int) x >> k;
  // make mask of low order w-k bits
  unsigned mask = k ? ((1 << (8*sizeof(int) - k)) - 1) : ~0;

  return xsra & mask;
}

int sra(int x, int k) {
  // Perform shift logically, e.g. replaced with 1s
  int xsrl = (unsigned) x >> k;

  // make a mask of the high order bits w - k
  // if we've done any shifts, e.g. k > 0, generate a mask where
  // from word size w...k is 1s and k...least significant bit is 0s

  // sizeof(int) = 8, k = 3
  // 1 << (sizeof(int) - k) => 0b00001000
  // 0b00001000 - 1 => 0b00000111
  // ~0b00000111 => 0b11111000
  unsigned mask = k ? ~((1 << (8*sizeof(int) - k)) - 1) : 0;

  // number is twos-complement so if it's negative, we have to preserve that
  // by re-adding 1s back in
  return (x < 0) ? mask | xsrl : xsrl;
}