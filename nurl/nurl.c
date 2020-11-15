// What we want to do
// Prompt user for a url (maybe already have 'https://www. at the beginning?)
// Parse the input to make sure it is a valid URL (regex?)
//

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main() {
  // 1 Define server we want to talk to
  int sock;
  struct addrinfo *my_addr_info;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
  int err = getaddrinfo("google.com", "http", &hints, &my_addr_info);
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
  char request[] = "GET / HTTP/1.0\r\n\r\n";

  // 4 Send request to server
  int total_sent = 0;
  while (total_sent < strlen(request)) {
    int sent = send(sock, (void *)&request[total_sent], (size_t)strlen(&request[total_sent]), 0);

    if (sent < 0) {
      printf("Something went wrong sending: %d\n", errno);
      return EXIT_FAILURE;
    }
    total_sent += sent;
  }

  printf("We've sent everything, el capitaine. All %d bytes!\n", total_sent);

  // 5 Read response
  int max = 10000000;
  char *buf = malloc(max);
  int total_recv = 0;
  while (total_recv < max) {
    int bytes_recv = recv(sock, (void *)&buf[total_recv], max - total_recv, 0);
    if (bytes_recv < 0) {
      printf("Failure on recv :((((\n");
      return EXIT_FAILURE;
    }
    printf("> read %d more bytes\n", bytes_recv);
    if (bytes_recv == 0) {
      break;
    }
    total_recv += bytes_recv;

    if (total_recv == max) {
      printf("We can't read everything :(\n");
      return EXIT_FAILURE;
    }
  }

  printf("Received!\n");
  for (int i = 0; i < total_recv; i++) {
    printf("%c", buf[i]);
  }
  printf(" <--dis wut we got\n");

  free(buf);
  freeaddrinfo(my_addr_info);
}
