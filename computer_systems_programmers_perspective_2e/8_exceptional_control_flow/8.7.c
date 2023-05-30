#include <signal.h>
#include <stdio.h>

void handler(int signal)
{
  return;
}

unsigned int snooze(unsigned int secs)
{
  // sleep() will be interrupted by the signal in MOST systems
  unsigned int slept_for = sleep(secs);
  printf("Slept for %d out of %d secs\n", slept_for, secs);
  return slept_for;
}

int main(int argc, char *argv[], char *envp[])
{
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <seconds>\n", argv[0]);
  }

  if (signal(SIGINT, handler) == SIG_ERR)
  {
    unix_error("signal error\n");
  }
  (void)snooze(atoi(argv[1]));
  exit(0);
}