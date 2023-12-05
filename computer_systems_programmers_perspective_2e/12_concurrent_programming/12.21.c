#include <semaphore.h>

sem_t write_count_mutex, resource_mutex;
int write_count = 0;

void *reader(void *vargp)
{
  while (1)
  {
    P(&write_count_mutex);
    if (write_count > 0)
    {
      V(&write_count_mutex);
      continue;
    }
    V(&write_count_mutex);

    P(&resource_mutex);
    // Read
    V(&resource_mutex);
  }
}

void *writer(void *vargp)
{
  while (1)
  {
    P(&write_count_mutex);
    write_count++;
    V(&write_count_mutex);

    P(&resource_mutex);
    // Write
    V(&resource_mutex);

    P(&write_count_mutex);
    write_count--;
    V(&write_count_mutex);
  }
}