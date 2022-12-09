# define N 16
typedef int fix_matrix[N][N];
void fix_set_diag_opt(fix_matrix A, int val)
{
  int *Abase = A[0][0];
  int index = 0;
  do {
    Abase[index] = val;
    index += (N + 1);
  } while (index != (N + 1) * N);
}