#include <stdio.h>

unsigned int snooze(unsigned int secs)
{
  unsigned int slept_for = sleep(secs);
  printf("Slept for %d out of %d secs\n", slept_for, secs);
  return slept_for;
}