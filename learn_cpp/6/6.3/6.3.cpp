#include <iostream>

int getInt()
{
  int input{};
  std::cin >> input;
  return input;
}

int main()
{
  std::cout << "Enter an integer: ";
  int smaller{ getInt() };

  std::cout << "Enter a larger integer: ";
  int larger{ getInt() };

  if (smaller > larger)
  {
    int temp{ smaller };
    smaller = larger;
    larger = temp;
    std::cout << "Values swapped";
  } // temp dies here

  std::cout << "The larger value is " << larger << '\n';
  std::cout << "The smaller value is " << smaller << '\n';

  return 0;
} // smaller and larger die here

