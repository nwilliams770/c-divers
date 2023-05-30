#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[], char* env[])
{
  if (execve("/bin/ls", argv, env) == -1) {
    fprintf(stderr, "execve error: %s\n", strerror(errno));
    exit(1);
  }
};