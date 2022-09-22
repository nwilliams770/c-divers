int signed_high_prod(int x, int y) {
  int p = (int) unsigned_high_prod((unsigned) x, (unsigned) y);

  if (x < 0) {
    p -= y;
  }
  if (y < 0) {
    p -= x;
  }
  return p;
}