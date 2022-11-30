int loop(int x, int n)
{
  int result = 0;
  int mask;
  for (mask = 1; mask != 0; mask <<= n) {
    result |= x & mask;
  }
  return result;
}

/*
A.
%esi holds x
%ebx holds n
%edx holds mask

B.
int result = 1;
int mask = 1;

C.
mask != 0;

D.
mask <<= n

E. result |= x & mask;
*/
