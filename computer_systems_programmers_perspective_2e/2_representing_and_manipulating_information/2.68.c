// Mask with least significant n bits set to 1
// n = 6 => 0x2F, n = 17 => 0x1FFFF
// (1 << n) - 1 will produce a mask of n 1s
// (1 << 3) => 0b1000
// 0b1000 - 0b1 = 0b111
int lower_one_mask(int n) {
  // To handle case for when n might be the word size, we do n - 1
  return (2 << (n - 1)) - 1;
}
// n = 4
// (2 << 3) => 0b10000
// 0b10000 - 0b1 = 0b1111