typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
  int i;
  for (i = 0; i < len; i++) {
      printf(" %.2x", start[i]);
  }
}

void show_short(short x) {
  show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x) {
  show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x) {
  show_bytes((byte_pointer) &x, sizeof(double));
}