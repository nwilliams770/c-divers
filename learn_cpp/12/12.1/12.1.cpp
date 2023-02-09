#include <functional>
#include <iostream>

using ArithmeticFunction = std::function<int(int, int)>;

int getInteger()
{
  std::cout << "Enter an integer: ";
  int input{};
  std::cin >> input;
  return input;
}

char getOperator()
{
  char op{};

  do
  {
    std::cout << "Enter an operation ('+', '-', '/', '*'): ";
    std::cin >> op;
  } while (op != '+' && op != '-' && op != '/' && op != '*');

  return op;
}

int add(int x, int y)
{
  return x + y;
}

int subtract(int x, int y)
{
  return x + y;
}

int divide(int x, int y)
{
  return x / y;
}

int multiply(int x, int y)
{
  return x * y;
}

ArithmeticFunction getArithmeticFunction(char operation)
{
  switch (operation)
  {
    case '+': return &add;
    case '-': return &subtract;
    case '/': return &divide;
    case '*': return &multiply;
  }

  return nullptr;
}

int main()
{
  int x{ getInteger() };
  int op{ getOperator() };
  int y{ getInteger() };

  ArithmeticFunction fnc{ getArithmeticFunction(op) };
  if (fnc) {
    std::cout << x << ' ' << op << ' ' << y << " = " << fnc(x, y) << '\n';
  }

  return 0;
}