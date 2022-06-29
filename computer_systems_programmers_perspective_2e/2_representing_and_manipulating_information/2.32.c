int tadd_ok();

int tsub_ok_buggy(int x, int y) {
  // Will give correct values EXCEPT when y is TMin and x is negative.
  // EX: x = -1, y = TMin (-10)
  // sum = x + (-y) => 9
  // x < 0 && y < 0 && sum >= 0 | FALSE detection of overflow
  return tadd_ok(x, -y);
}