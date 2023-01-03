#include <iostream>

void printEvens(int n)
{
  for (int i{ 0 }; i < n; i += 2)
  {
    std::cout << i << '\n';
  }
}

int sumTo(int n)
{
  int sum{ 0 };
  for (int i{ 1 }; i <= n; i++)
  {
    sum += i;
  }
  return sum;
}

int main()
{
  printEvens(10);
  sumTo(100);
  return 0;
}