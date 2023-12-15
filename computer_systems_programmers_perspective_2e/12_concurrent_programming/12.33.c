#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// #include <time.h>
#include <errno.h>

typedef struct ThreadArgs
{
  char *s;
  int size;
  FILE *stream;
  char *read_value;
} ThreadArgs;

void *thread_read(void *vargp)
{
  ThreadArgs *args = (ThreadArgs *)vargp;
  args->read_value = fgets(args->s, args->size, args->stream);
  return NULL;
};

char *tfgets_thread(char *s, int size, FILE *stream)
{
  pthread_t tid_read;
  ThreadArgs args = {s, size, stream, NULL};

  pthread_create(&tid_read, NULL, thread_read, &args);

  struct timespec timeout;
  timeout.tv_nsec = 0;
  timeout.tv_sec = 5;

  if (pthread_timedjoin_np(tid_read, NULL, &timeout) == ETIMEDOUT)
  {
    pthread_cancel(&tid_read);
    return NULL;
  }

  return args.read_value;
}