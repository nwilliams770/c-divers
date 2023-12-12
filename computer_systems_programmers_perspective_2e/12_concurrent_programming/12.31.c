#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>

jmp_buf env;

void timeout_handler(int signo)
{
  longjmp(env, 1);
};

char *tfgets(char *str, int n, FILE *stream)
{
  // Set up signal handler
  struct sigaction sa;
  sa.sa_handler = timeout_handler;
  sigemptyset(&sa.sa_mask); // initialize mask to empty set
  sa.sa_flags = 0; // set flags to 0 (default behavior)
  if (sigaction(SIGALRM, &sa, NULL) == -1)
  {
    perror("sigaction");
  }

  // Set up timer
  struct itimerval timer;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 0;
  timer.it_value.tv_sec = 5;
  timer.it_value.tv_usec = 0;
  if (settimer(ITIMER_REAL, timer, NULL) == -1)
  {
    perror("settimer");
    return NULL;
  }

  // Save execution context
  if (setjmp(env) == 0)
  {
    char *result = fgets(str, n, stream);
    // Cancel the timer
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
    {
      perror("settimer");
      return NULL;
    }
    return result;
  }
  else
  {
    // Nonlocal jump occurred due to timeout
    // Return NULL to indicate timeout
    return NULL;
  }
}