#include <semaphore.h>

int read_count;
sem_t read_count_mutex, write_mutex;

void reader(void)
{
  while(1)
  {
    P(&read_count);
    read_count++;
    if (read_count == 1)
    {
      P(&write_mutex);
    }
    V(&read_count_mutex);

    // Critical reading

    P(&read_count_mutex);
    read_count--;
    if (read_count == 0)
    {
      V(&write_mutex);
    }
    V(&read_count_mutex);
  }
}

void writer(void)
{
  while (1)
  {
    P(&read_count_mutex);
    if (read_count > 0)
    {
      V(&read_count_mutex);
      continue;
    }
    V(&read_count_mutex);

    P(&write_mutex);
    // Critical writing
    V(&write_mutex);
  }
}