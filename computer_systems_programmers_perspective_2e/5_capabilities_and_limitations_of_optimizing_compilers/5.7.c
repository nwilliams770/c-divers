void combine5(vec_ptr v, data_t *dest)
{
  long int i;
  long int length = vec_length(v);
  long int limit = length - 5;
  data_t *data = get_vec_start(v);
  data_t acc = IDENT;

  // Combine 5 elements at a time
  for (i = 0; i < limit; i+=5)
  {
    acc = acc OP data[i] OP [i+1];
    acc = acc OP data[i+2] OP [i+3];
    acc = acc OP data[i+4]
  }

  for (; i < length; i++)
  {
    acc = acc OP data[i];
  }
  *dest = acc;
}