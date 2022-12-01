#include <iostream>

int main()
{
  int num_a{};
  int num_b{};

  std::cout << "Enter an integer: ";
  std::cin >> num_a;

  std::cout << "\nEnter another integer: ";
  std::cin >> num_b;

  std::cout << "\n" << num_a << " + " << num_b << "=" << (num_a + num_b) << "\n";
  std::cout << "\n" << num_a << " + " << num_b << "=" << (num_a - num_b) << "\n";

  return 0;
}