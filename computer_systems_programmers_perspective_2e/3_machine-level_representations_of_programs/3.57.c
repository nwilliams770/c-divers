// Write in such a way that will compile to a conditional move
int cread_alt(int *xp)
{
  int zero = 0;
  if (!xp) xp = &zero;
  return *xp;
}