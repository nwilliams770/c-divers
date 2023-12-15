#include <stdlib.h>
#include <pthread.h>

typedef struct ThreadInfo {
  int row;
  int col;
  int **multiplier;
  int **multiplicand;
  int num_cols_multiplier;
  int num_rows_multiplicand;
  int **product;
} ThreadInfo;

void *compute_dot_product(void *arg)
{
  struct ThreadInfo *info = (struct ThreadInfo*)arg;

  int dot_product = 0;

  for (int i = 0; i < info->num_cols_multiplier; i++)
  {
    dot_product += info->multiplier[info->row][i] * info->multiplicand[i][info->col];
  }

  info->product[info->row][info->col] = dot_product;

  pthread_exit(NULL);
}

void free_matrix(int **matrix, int num_rows)
{
  for (int i = 0; i < num_rows; i++)
  {
    free(matrix[i]);
  }

  free(matrix);
}

int **multiply_matrix(
  int **multiplier,
  int **multiplicand,
  int num_rows_multiplier,
  int num_cols_multiplier,
  int num_rows_multiplicand,
  int num_cols_multiplicand
  )
{
  // Allocate memory for result matrix
  int **result = (int **)malloc(sizeof(int*) * num_rows_multiplier);
  if (result == NULL)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < num_rows_multiplier; i++)
  {
    result[i] = (int *)malloc(sizeof(int) * num_cols_multiplicand);
    if (result[i] == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
  }

  // Calculate # threads needed
  int num_threads_needed = num_rows_multiplier * num_rows_multiplicand;
  pthread_t threads[num_threads_needed];

  for (int i = 0; i < num_rows_multiplier; i++)
  {
    for (int j = 0; j < num_cols_multiplicand; j++)
    {
      ThreadInfo info = {
        .row = i,
        .col = j,
        .multiplier = multiplier,
        .multiplicand = multiplicand,
        .num_cols_multiplier = num_cols_multiplier,
        .num_rows_multiplicand = num_rows_multiplicand,
        .product = result,
      };
      // linear indexing for threads[]
      if (pthread_create(&threads[i * num_cols_multiplicand + j], NULL, compute_dot_product, &info) != 0)
      {
        perror("pthread_create");
        free_matrix(result, num_rows_multiplier);
        exit(EXIT_FAILURE);
      }
    }
  }

  for (int i = 0; i < num_threads_needed; i++)
  {
    if (pthread_join(threads[i], NULL) != 0)
    {
      perror("pthread_join");
      free_matrix(result, num_rows_multiplier);
      exit(EXIT_FAILURE);
    }
  }

  return result;
}