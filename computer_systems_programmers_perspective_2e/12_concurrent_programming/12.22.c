#include <stdlib.h>

void echo(int connfd) {
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, connfd);

  n = Rio_readlineb(&rio, buf, MAXLINE);
  if (n > 0) {
      Rio_writen(connfd, buf, n); // Echo back the received line
  }
}