// What we want to do
// Prompt user for a url (maybe already have 'https://www. at the beginning?)
// Parse the input to make sure it is a valid URL (regex?)
//

#include <errno.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

void print_url_parse_error(char *url, char* reason) {
  printf("Error: Failed to parse input URL '%s':\n%s\n", url, reason);
}

bool split_url(char *url, char **base_url, char **route) {
  // What designates a valid url?
  // [.a-zA-Z0-9].[a-zA-Z]/[a-zA-Z]

  // Protocol Check
  for (int i = 0; i < strlen(url); i++) {
    char c = url[i];
    // chars in C are ASCII so we're checking if c is within the bounds of all letters
    bool is_letter = c >= 'A' && c <= 'z';
    if (is_letter) {
      continue;
    } else if (c == ':') {
      // http://
      if (i + 2 > strlen(url) - 1) {
        print_url_parse_error(url, "String ended before protocol definition completed");
        return false;
      } else if (url[i + 1] != '/' || url[i + 2] != '/') {
        print_url_parse_error(url, "Protocol not formatted as '://'");
        return false;
      }
      char protocol[i + 1];
      memcpy(protocol, url, i);
      protocol[i] = '\0';
      if (strcmp(protocol, "http") != 0) {
        char error[50 + i];
        sprintf(error, "%s protocol not supported\nOnly supports http", protocol);
        print_url_parse_error(url, error);
        return false;
      }

      url = &url[i + 3];
      break;
    } else {
      break;
    }
  }

  // Now, we have a URL as either:
  // google.com
  // OR
  // google.com/
  // OR
  // google.com/blah[/blah/blah/...]
  // and we can treat the second and third and ... cases the same

  // Go up to the first slash
  // If there is no slash found, we'll return URL as is, then route is '/'
  // If there is a first slash, return URL as up to (not including) the '/', then route as '/', onward
  for (int i = 0; i < strlen(url); i++) {
    char c = url[i];

    // when we find the first slash, split the domain from the route
    if (c == '/') {
      // up to but not including the current index
      *base_url = (char *)malloc(i + 1);
      memcpy(*base_url, url, i);
      (*base_url)[i] = '\0';

      // current index, to the end
      int route_len = strlen(url) - i;
      *route = (char *)malloc(route_len + 1);
      memcpy(*route, &url[i], route_len);
      (*route)[route_len] = '\0';

      return true;
    }
  }

  // if we never found a slash, the url is the domain and we default to route = '/'
  *base_url = (char *)malloc(strlen(url) + 1);
  memcpy(*base_url, url, strlen(url) + 1);

  *route = (char *)malloc(2);
  char *slash_route = "/";
  memcpy(*route, slash_route, strlen(slash_route) + 1);

  return true;
}

void free_url(char **base_url, char **route) {
  free(*base_url);
  free(*route);
}

int main(int argc, char *argv[]) {
  // Pre-Steps
  // 1 Validate # of args, only should be 2 (./nurl.out URL)
  if (argc > 2) {
    printf("Error: Too many arguments provided: %d\nUsage: nurl http://www.google.com\n", argc);
    return EXIT_FAILURE;
  } else if (argc < 2) {
    printf("Error: Too few arguments provided: %d\nUsage: nurl http://www.google.com\n", argc);
    return EXIT_FAILURE;
  }

  char *base_url;
  char *route;
  bool ok = split_url(argv[1], &base_url, &route);
  if (!ok) {
    return EXIT_FAILURE;
  }

  // 1 Define server we want to talk to
  int sock;
  struct addrinfo *my_addr_info;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
  int err = getaddrinfo(base_url, "http", &hints, &my_addr_info);
  if (err) {
    printf("Failed to resolve DNS for google.com\n");
    return EXIT_FAILURE;
  }

  sock = socket(my_addr_info->ai_family, my_addr_info->ai_socktype, my_addr_info->ai_protocol);
  if (sock < 0) {
    printf("Failed to create socket :(\n");
    return EXIT_FAILURE;
  }

  // 2 Connect to server
  err = connect(sock, my_addr_info->ai_addr, my_addr_info->ai_addrlen);

  if (err < 0) {
    printf("Failed to connect: %d\n", errno);
    return EXIT_FAILURE;
  }

  // 3 Form request
  char *request = (char *)malloc(strlen(route) + 30);
  sprintf(request, "GET %s HTTP/1.0\r\n\r\n", route);

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
    if (bytes_recv == 0) {
      break;
    }
    total_recv += bytes_recv;

    if (total_recv == max) {
      printf("We can't read everything :(\n");
      return EXIT_FAILURE;
    }
  }

  for (int i = 0; i < total_recv; i++) {
    printf("%c", buf[i]);
  }

  free(buf);
  freeaddrinfo(my_addr_info);
  free_url(&base_url, &route);
}
