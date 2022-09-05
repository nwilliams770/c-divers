// 4 byte where each byte represents a signed byte
// 0 is least significant byte, 3 is most significant
typedef unsigned packed_t;

// Failed attempt at xbyte
int xbyte(packed_t word, int bytenum) {
  return (word >> (bytenum << 3)) & 0xFF;
}

// word = 0b1111 1111 1111 1111
// bytenum = 0
// bytenum << 3 => 0
//

// A. What's wrong with this code?
// Does not perform sign extension. Extracting byte 0 from word 0x(000000)FF will yield
// 255 instead of -1.

// B. Give correct implementation using only left/right shifts, along with
// subtraction.
int xbyte_right(packed_t word, int bytenum) {
  // We need to place the desired byte at the beginning of our 32-bit int output
  // because we need to do sign extension (using arithemetic right shifts)
  int left = word << ((3 - bytenum) << 3); // 3 << 3 = 24; 2 << 3 = 12; 1 << 3 = 8; 0 << 3 = 0;

  // extend for the rest of the 3 bytes
  return (left >> 24);
}