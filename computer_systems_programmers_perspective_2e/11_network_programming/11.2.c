#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
  struct in_addr inaddr;
  unsigned int addr;

  if (argc != 2)
  {
    fprintf(stderr, "usage %s <hex number>\n", argv[0]);
    exit(1);
  }
  if (sscanf(argv[1], "%x", addr) != 1)
  {
    fprintf(stderr, "invalid hex number %s\n", argv[1]);
    exit(1);
  }
  inaddr.s_addr = addr;
  printf("%s\n", inet_ntoa(inaddr));

  return 0;
}