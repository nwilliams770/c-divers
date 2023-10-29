#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  struct stat fileStat;
  char *type, *readok;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  if (fstat(argv[1], &fileStat) < 0)
  {
    perror("fstat");
    exit(2);
  }

  if (S_ISREG(fileStat.st_mode))
  {
    type = "regular";
  }
  else if (S_ISDIR(fileStat.st_mode))
  {
    type = "directory";
  }
  else
  {
    type = "other";
  }

  if ((fileStat.st_mode & S_IRUSR))
  {
    readok = "yes";
  }
  else
  {
    readok = "no";
  }

  printf("type: %s, read: %s\n", type, readok);
  exit(0);
}
