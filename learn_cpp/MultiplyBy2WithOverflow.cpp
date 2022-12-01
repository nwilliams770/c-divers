#include <iostream>

int main()
{
  std::cout << "Enter an integer: ";

  int num_input{ };
  std::cin >> num_input;

  int double_num{ num_input * 2 };
  int overflowed{ mult_overflow(num_input, 2) };

  if (overflowed) {
    std::cout << "Overflow detected!\n Double " << num_input << " evaluated to "
      << double_num << "\n";
  } else {
    std::cout << "Double that number is " << double_num << "\n";
  }
  return 0;
}

int mult_overflow(int x, int y)
{
  int product = x * y;
  return (!x) || (product / x == y);
}