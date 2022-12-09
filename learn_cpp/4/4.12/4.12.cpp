#include <iostream>

int main()
{
  char input{ getInput() };
  std::cout << "You entered '" << input << "', which has ASCII code" << static_cast<int>(input) << ".\n";

  int ascii{ input };
  std::cout << "You entered '" << input << "', which has ASCII code" << ascii << ".\n";
  return 0;
}

char getInput()
{
  std::cout << "Enter a single character: ";
  char input{};
  std::cin >> input;

  return input;
}