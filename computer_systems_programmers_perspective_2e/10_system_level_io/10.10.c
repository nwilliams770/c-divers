#include "csapp.h"

int main(int argc, char **argv) {
  int n;
  rio_t rio;
  char buf[MAXLINE];
  int srcfd = STDIN_FILENO;

  if (argc > 1)
  {
    srcfd = Open(argv[1], O_RDONLY);
    if (srcfd < 0)
    {
      perror("Open");
      exit(1);
    }
  }

  Rio_readinitb(&rio, STDIN_FILENO);
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    Rio_writen(STDOUT_FILENO, buf, n);
  }
}