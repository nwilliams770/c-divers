#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define N 2

int main()
{
  int status, i;
  pid_t pid;

  /* Parent creates N children */
  for (i = 0; i < N; i++)
  {
    if ((pid = fork()) == 0) /* Child */
    {
      // Create segmentation fault
      int *ptr = NULL;
      *ptr = 1;
    }
  }

  /* Parent reaps N children in no particular order */
  while ((pid = waitpid(-1, &status, 0)) > 0)
  {
    if (WIFEXITED(status))
    {
      printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
      char message[100];

      snprintf(message, sizeof(message), "child %d terminated by signal %d", pid, WTERMSIG(status));
      psignal(WTERMSIG(status), message);
    }
    else
    {
      printf("child %d terminated abnormally\n", pid);
    }
  }

  /* The only normal termination is if there are no more children */
  if (errno != ECHILD)
  {
    perror("waitpid error");
  }

  exit(0);
}