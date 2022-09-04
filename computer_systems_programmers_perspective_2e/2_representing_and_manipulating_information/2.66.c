// Generate mask indicating leftmost 1 in x
// 0xF (0b11111111) => 0x8 (0b10000000)
int leftmost_one(unsigned x) {
  // Create a cascade of 1s from the leftmost 1 onward so that
  // something like this 0b01000 0000 becomes 0b0111 1111
  // Then xor it with itself >> 1; this will knock out all 1s except the
  // most significant: 0b0111 1111 ^ (0b0111 1111 >> 1)
  x |= (x>>1);
  x |= (x>>4);
  x |= (x>>8);
  x |= (x>>16);

  x ^= (x>>1);

  return x;
}

