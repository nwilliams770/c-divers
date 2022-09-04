int int_shifts_are_arithmetic() {
  // 0b1000  < 0
  // Logical shift => 0b0100 > 0
  // Arithmetic shift => 0b1100 < 0
  return (INT_MIN >> 1) < 0;
}

int int_shifts_are_logical() {
  int x = -1; // all 1s for twos complement representation
  return (x >> 1) > 0; // logical: 0b011... arithmetic: 0b111...
}