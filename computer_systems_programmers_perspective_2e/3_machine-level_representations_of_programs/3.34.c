// B.
int rfun(unsigned x)
{
  if (x == 0) {
    return 0;
  }
  unsigned nx = x >> 1;
  int rv = rfun(nx);
  return (x & 0x1) + rv;
}

// A. Register %ebx holds the value of parameter x.
// C. This function recursively computes the sum of the bits in argument x