// return 1 if any odd bit is 1, w=32
int any_odd_one(unsigned x) {
  // 1010
  // set all even bits to 0, then check if any bit is set
  return (x & 0xAAAAAAAA) != 0;
}

int any_even_one(unsigned x) {
  // 1010
  // set all odd bits to 0, then check if any bit is set
  return (x & 0x55555555) != 0;
}