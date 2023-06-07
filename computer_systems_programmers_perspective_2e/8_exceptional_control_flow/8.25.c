#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


volatile sig_atomic_t timeout_flag = 0;

void handler(int sig)
{
  timeout_flag = 1;
};

char *tfgets(char *str, int size, FILE *stream)
{
  struct sigaction sa;

  sa.sa_handler = handler; // register handler
  // initialize these otherwise they can contain garbage values
  sigemptyset(&sa.sa_mask); // initialize mask to empty set
  sa.sa_flags = 0; // set flags to 0 (default behavior)

  if (sigaction(SIGALRM, &sa, NULL) == -1)
  {
    // Error occurred while registering the signal handler
    fprintf(stderr, "Failed to register signal handler: %s\n", strerror(errno));
    return NULL;
  }

  alarm(5); // Set 5s alarm

  timeout_flag = 0; // Reset timeout flag

  char *result = fgets(str, size, stream); // Get result from fgets()

  alarm(0); // Clear alarm

  if (timeout_flag)
  {
    // Return NULL if timeout occurred
    return NULL;
  }
  else
  {
    return result;
  }
}

int main(int argc, char* argv[])
{
  return 0;
}