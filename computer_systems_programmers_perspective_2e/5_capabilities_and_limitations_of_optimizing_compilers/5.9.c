void merge(int src1[], int src2[], int dest[], int n)
{
  int i1 = 0;
  int i2 = 0;
  int id = 0;
  while (i1 < n && i2 < n)
  {
    int v1 = src1[i1];
    int v2 = src2[i2];
    int take1 = v1 < v2;
    dest[id++] = take1 ? v1 : v2;
    i1 += take1;
    i2 += (1-take1);
  }

}