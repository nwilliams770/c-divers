#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

extern char** environ;  // Declare the external variable

int mysystem(char *command)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == -1)
  {
    perror("fork failed");
    exit(EXIT_FAILURE);
  }
  else if (pid == 0)
  {
    char *argv[3] = {"-c", command, NULL};
    execve("/bin/sh", argv, environ);
    // only returns if execve fails
    perror("execve failed");
    exit(EXIT_FAILURE);
  }
  else
  {
    waitpid(pid, &status, 0);
    if WIFEXITED(status)
    {
      return WEXITSTATUS(status);
    }

    if WIFSIGNALED(status)
    {
      return WTERMSIG(status);
    }
  };

  // waitpid failed
  return -1;
};

int main(int argc, char *argv[])
{
  int exitStatus = mysystem("ls -l");

  if (exitStatus == -1)
  {
    printf("Command execution failed.\n");
  }
  else if (WIFEXITED(exitStatus))
  {
    printf("Command exited with status: %d\n", WEXITSTATUS(exitStatus));
  }
  else if (WIFSIGNALED(exitStatus))
  {
    printf("Command terminated by signal: %d\n", WTERMSIG(exitStatus));
  }


    return 0;

  return 0;
};