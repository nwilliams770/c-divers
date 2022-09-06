int tsub_ok(int x, int y) {
  int diff = x - y;
  // we've subtracted so large an amount diff becomes positive
  int neg_over = x < 0 && y >= 0 && diff >= 0;
  // we've subtracted so large a negative amount diff becomes negative
  int pos_over = x > 0 && y <= 0 && diff <= 0;
  return neg_over || pos_over;
}