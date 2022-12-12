int var_prod_ele_opt (int n, int A[n][n], int B[n][n], int i, int k)
{
  char *Arow = (char *) (A[i]);
  char *Bptr = (char *) (&B[0][k]);
  int result = 0;
  int j4;
  int n4 = n * 4;
  for (j4 = 0; j4 < n4; j4+=4) {
    int a = *(int *) (Arow + j4);
    int b = *(int *) Bptr;
    result += a * b;
    Bptr += n4;
  }
  return result;
}