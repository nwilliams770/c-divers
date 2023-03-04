#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

void inner4(vec_ptr u, vec_ptr v, data_t *dest)
{
  long int i;
  int length = vec_length(u);
  data_t *udata = get_vec_start(u);
  data_t *vdata = get_vec_start(v);

  data_t sum = (data_t) 0;
  data_t sum1 = (data_t) 0;
  data_t sum2 = (data_t) 0;
  data_t sum3 = (data_t) 0;

  for (i = 0; i < length-4; i+=4)
  {
    sum = udata[i] * vdata[i];
    sum1 = udata[i+1] * vdata[i+1];
    sum2 = udata[i+2] * vdata[i+2];
    sum3 = udata[i+3] * vdata[i+3];
  }

  for (; i < length; i++)
  {
    sum += udata[i] * vdata[i];
  }

  *dest = sum + sum1 + sum2 + sum3;
}