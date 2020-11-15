// What we want to do
// Prompt user for a url (maybe already have 'https://www. at the beginning?)
// Parse the input to make sure it is a valid URL (regex?)
//

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
  // 1 Define server we want to talk to
  int sock;
  struct addrinfo *my_addr_info;
  int err = getaddrinfo("google.com", "http", NULL, &my_addr_info);
  if (err) {
    printf("Failed to resolve DNS for google.com\n");
    return EXIT_FAILURE;
  }

  sock = socket(my_addr_info->ai_family, my_addr_info->ai_socktype, my_addr_info->ai_protocol);

  if (sock < 0) {
    printf("Failed to create socket :(\n");
    return EXIT_FAILURE;
  }

  printf("%d here's our lovely socket\n", sock);

  // 2 Connect to server
  err = connect(sock, my_addr_info->ai_addr, my_addr_info->ai_addrlen);

  if (err < 0) {
    printf("Failed to connect: %d\n", errno);
    return EXIT_FAILURE;
  }

  printf("We've connected, baby\n");
  // 3 Form request

  // 4 Send request to server

  // 5 Read response

  freeaddrinfo(my_addr_info);
}
