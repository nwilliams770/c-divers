#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* hello_world();

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Usage: %s <nthreads>", argv[0]);
    exit(EXIT_FAILURE);
  }

  int num_threads = atoi(argv[1]);

  pthread_t tid[num_threads];

  for (int i = 0; i < num_threads; i++)
  {
    if (pthread_create(&tid[i], NULL, hello_world, NULL) != 0)
    {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < num_threads; i++)
  {
    if (pthread_join(tid[i], NULL) != 0)
    {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}

void* hello_world(void* arg)
{
  printf("Hello world!\n");
  return NULL;
}