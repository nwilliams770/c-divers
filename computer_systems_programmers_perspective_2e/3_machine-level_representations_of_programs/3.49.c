long fun_c(unsigned long x)
{
  long val = 0;
  int i;
  for (i = 0; i < 8; i++)
  {
    val += x & 0x01010101010101L;
    x >>= 1;
  }
  val += (val >> 32);
  val += (val >> 16);
  val += (val >> 8);
  return val & 0xFF;
}

// Sums the bits in x