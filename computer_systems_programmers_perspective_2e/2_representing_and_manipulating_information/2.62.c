int int_shifts_are_arithmetic() {
  // 0b1000  < 0
  // Logical shift => 0b0100 > 0
  // Arithmetic shift => 0b1100 < 0
  return (INT_MIN >> 1) < 0;
}