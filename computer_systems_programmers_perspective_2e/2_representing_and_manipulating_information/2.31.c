int tadd_ok_buggy(int x, int y) {
  int sum = x+y;
  // This statement will always evaluate to true whether or not an overflow
  // occurs. Two's complement addition forms an abelian group.
  return (sum-x == y) && (sum-y == x);
}