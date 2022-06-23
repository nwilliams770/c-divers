// size_t strlen(const char *s);

int strlonger(char *s, char *t) {
  return strlen(s) - strlen(t) > 0;
}

// A. Incorrect results will come about when strlen(s) - strlen(t) < 0
// B. size_t is unsigned int  strlen(s) - strlen(t) < 0 it will actually
// evaluate to a much larger number than expected
// C. This can be fixed by updating  strlen(s) - strlen(t) > 0 to  strlen(s) - strlen(t)