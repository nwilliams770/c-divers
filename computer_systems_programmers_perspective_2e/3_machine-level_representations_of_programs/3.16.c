// A.
void goto_cond(int a, int *p) {
  if (p == 0) {
    goto done;
  }
  if (a <= 0) {
    goto done;
  }
  *p += a;
  done:
    return;
}

// B.C code is using && operator, which is effectively running two conditional
// statements