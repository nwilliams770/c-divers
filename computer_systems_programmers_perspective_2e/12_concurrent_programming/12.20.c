#include <semaphore.h>

sem_t mutex;

void reader(void)
{
  while(1)
  {
    P(&mutex);
    // Critical reading
    V(&mutex);
  }
}

void writer(void)
{
  while (1)
  {
    P(&mutex);
    // Critical writing
    V(&mutex);
  }
}