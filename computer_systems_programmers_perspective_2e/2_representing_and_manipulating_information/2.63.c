unsigned srl(unsigned x, int k) {
  // Perform shift arithmetically
  unsigned xsra = (int) x >> k;


}

int sra(int x, int k) {
  // Perform shift logically
  int xsra = (unsigned) x >> k;
  unsigned mask = k ? ((1 << (8*sizeof(int) - k)) - 1) : 0;


}