int switcher(int a, int b, int c)
{
  int answer;
  switch(a) {
    case 5:
      c = b ^ 15;
    case 0:
      answer = c + 112;
      break;
    case 2:
    case 7:
      answer = (c + b) << 2;
      break;
    case 4:
      answer = a;
      break;
    default:
      answer = b;
  }
  return answer;
}