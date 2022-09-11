//  return 1 if x <= y, else 0
int float_le(float x, float y) {
  unsigned ux = f2u(x);
  unsigned uy = f2u(y);

  // Get sign bits
  unsigned sx = ux >> 31;
  unsigned sy = uy >> 31;

  return
    (ux == 0 && uy == 0) ||
    (!sx && sy) ||
    (!sx && !sy && ux >= uy) ||
    (sx && sx && ux <= uy);
}