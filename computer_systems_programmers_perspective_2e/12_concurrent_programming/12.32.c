#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

char *tfgets_select(char *str, int n, FILE *stream)
{
  fd_set read_fds;
  struct timeval timeout;

  FD_ZERO(&read_fds);
  FD_SET(STDIN_FILENO, &read_fds);

  timeout.tv_sec = 5; // 5-second timeout
  timeout.tv_usec = 0;

  int ready = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);
  if (ready == -1)
  {
    perror("select");
    return NULL;
  }
  else if (ready > 0)
  {
    if (FD_ISSET(STDIN_FILENO, &read_fds))
    {
      char *result = fgets(str, n, stream);
      return result;
    }
  }
  else
  {
    // timed out
    return NULL;
  }
}