// Addition that saturates to TMin or TMax
int saturating_add(int x, int y) {
  int sum = x + y;
  // Mask of all 1s of word size
  // sizeof(int) << 3 = sizeof(int) * 8
  int word_size = (sizeof(int) << 3) - 1;
  int xneg_mask = (x >> word_size);
  int yneg_mask = (y >> word_size);
  int sumneg_mask = (sum >> word_size);
  int pos_over_mask = ~xneg_mask & ~yneg_mask & ~sumneg_mask;
  int neg_over_mask = xneg_mask & yneg_mask & sumneg_mask;
  int over_mask = pos_over_mask | neg_over_mask;
  int result = (~over_mask & sum) | (pos_over_mask & INT_MAX) | (neg_over_mask & INT_MIN);
  return result;
}