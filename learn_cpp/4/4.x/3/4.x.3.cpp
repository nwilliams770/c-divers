#include <iostream>

double getDouble()
{
  std::cout << "Enter a double value: ";
  double input{};
  std::cin >> input;
  return input;
}

char getOperation()
{
  std::cout << "Enter an operator (+, -, *, /): ";
  char input{};
  std::cin >> input;
  return input;
}

void printResult(double x, double y, char operation)
{
  if (operation == '+') {
    std::cout << x << " + " << y << " is " << x+y << '\n';
  } else if (operation == '-') {
    std::cout << x << " - " << y << " is " << x-y << '\n';
  } else if (operation == '*') {
    std::cout << x << " * " << y << " is " << x*y << '\n';
  } else if (operation == '/') {
    std::cout << x << " / " << y << " is " << x/y << '\n';
  } else {
    std::cout << "Invalid operator. Expected: '+', '-', '*', '/'. Got: " <<
    operation << '\n';
  }
}

int main()
{
  double x{ getDouble() };
  double y{ getDouble() };
  char operation{ getOperation() };
  printResult(x, y, operation);

  return 0;
}
