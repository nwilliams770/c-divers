int decode2(int x, int y, int z)
{
  int temp = z - x;
  return (temp << 31 >> 31) ^ (x * y);
}