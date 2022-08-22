int is_little_endian() {
  int x = 1;
  return *(char *)&x == 1;
}