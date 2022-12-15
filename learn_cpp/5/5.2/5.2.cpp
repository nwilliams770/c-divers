#include <iostream>

int getInt()
{
  std::cout << "Enter a number: ";
  int input{};
  std::cin >> input;
  return input;
}

bool isEven(int a)
{
  return (a % 2) == 0;
}

int main()
{
  int input{ getInt() };
  if (isEven(input))
    std::cout << input << "is even.\n";
  else
    std::cout << input << "is odd.\n";
  return 0;
}

