#include "csapp.h"

int main(int argc, char **argv)
{
  int n;
  rio_t rio;
  char buf[MAXBUFFER];

  Rio_readinitb(&rio, STDIN_FILENO);
  while((n = rio_readnb(&rio, buf, MAXBUFFER)) != 0)
  {
    Rio_writen(STDOUT_FILENO, buf, n);
  }
}