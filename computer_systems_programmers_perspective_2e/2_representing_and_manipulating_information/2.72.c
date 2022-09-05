// Copy integer into buffer if space is available
// Buggy implementation
void copy_int(int val, void *buf, int maxbytes) {
  if (maxbytes-sizeof(val) >= 0) {
    memcpy(buf, (void *) &val, sizeof(val));
  }
}

// A. Explain why conditional in this buggy code always succeeds. Hint: sizeof
// operator returns a value of type size_t
// size_t is unsigned and when an operation is performed where one operand is signed
// and the other is unsigned, C will use unsigned arithmetic so the result will
// never be negative.

// B. Show how you can rewrite the conditional test to make it work properly.
void copy_int_corrected(int val, void *buf, int maxbytes) {
  if (maxbytes >= sizeof(val)) {
    memcpy(buf, (void *) &val, sizeof(val));
  }
}