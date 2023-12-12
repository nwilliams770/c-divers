#include <netdb.h>
#include <pthread.h>
#include <string.h>


static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct hostent* gethostbyname_ts(const char *name) {
  struct hostent *result = NULL;

  // Lock the mutex
  pthread_mutex_lock(&mutex);

  // Call gethostbyname within the critical section
  struct hostent *original_result = gethostbyname(name);

  if (original_result != NULL)
  {
    // Deep copy the hostent structure
    result = malloc(sizeof(struct hostent));

    if (result != NULL)
    {
      // Copy individual fields
      result->h_name = strdup(original_result->h_name);
      result->h_aliases = strdup_list(original_result->h_aliases);
      result->h_addrtype = original_result->h_addrtype;
      result->h_addr_list = strdup_list(original_result->h_aliases);
      result->h_length = original_result->h_length;
    }
  }

  pthread_mutex_unlock(&mutex);

  return result;
}

// Helper function to deep copy a string list
char** strdup_list(char** list) {
  if (list == NULL)
  {
    return NULL;
  }

  int count = 0;
  while (list[count] != NULL)
  {
    count++;
  }

  char** new_list = malloc(sizeof(char*) * (count + 1));
  if (new_list != NULL)
  {
    for (int i = 0; i < count; i++)
    {
        new_list[i] = strdup(list[i]);
    }
    new_list[count] = NULL;
  }

  return new_list;
}