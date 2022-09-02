unsigned srl(unsigned x, int k) {
  unsigned xsra = (int) x >> k;
}

int sra(int x, int k) {
  int xsra = (unsigned) x >> k;
}