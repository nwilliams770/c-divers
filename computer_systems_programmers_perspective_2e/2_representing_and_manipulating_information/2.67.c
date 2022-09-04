int bad_int_size_is_32() {
  // Set most significant bit (msb) of 32-bit machine
  int set_msb = 1 << 31;
  // Shift past msg of 32-bit word
  int beyond_msb = 1 << 32;

  // set_msb is nonzero when word size >= 32
  // beyond_msb is zero when word size <= 32
  return set_msb && !beyond_msb;
}

// A. In what way does our code fail to comply with C standard
// The C standard does not define the effect of a shift by 32 of a 32-bit datum.
// On the SPARC (and many other machines), the expression x << k shifts by kmod
// 32, i.e., it ignores all but the least significant 5 bits of the shift amount.
// 1 << 32 => 1 << (32 % 32) => 1 << 0 => 1

// B. Modify the code to run properly on any machine for which data type int
// is at least 32 bits.
// To get around the mod effect; we can do 2 << 31

// C. Modify the code to run properly on any machine for which data type int
// is at least 16 bits
// set_msb = 2 << 15 << 15
// beyond_msb = set_msb << 1
