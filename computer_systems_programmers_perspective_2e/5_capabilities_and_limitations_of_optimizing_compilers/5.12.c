void psum1(float a[], float p[], long int n)
{
  long int i;
  float last_value, value;
  last_value = p[0] = a[0];

  for (i = 0; i < n; i++)
  {
    value = last_value + a[i];
    p[i] = value;
    last_value = value;
  }
}