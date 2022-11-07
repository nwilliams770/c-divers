// A.
int goto_absdiff(int x, int y) {
  int result;
  if (x < y) {
    goto true;
  }
  result = x - y;
  goto done;
  true:
    result = y - x;
    goto done;
  done:
    return result;
}

// B. Choice is mainly arbitrary but original rule works better when there is
// no 'else' case