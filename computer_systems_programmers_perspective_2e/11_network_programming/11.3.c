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
    fprintf(stderr, "usage %s <ip address>\n", argv[0]);
    exit(1);
  }
  if (inet_aton(argv[1], &inaddr) == 0)
  {
    fprintf(stderr, "inet_aton error %s\n", argv[1]);
    exit(1);
  }
  addr = ntohl(inaddr.s_addr);
  printf("0x%x\n", addr);

  return 0;
}