#include <iostream>
#include <vector>

// 1
int factorialOptimized(int n)
{
  // 0! 1!, 2!
  static std::vector<int> results{ 1, 1, 2 };

  if (n < static_cast<int>(std::size(results)))
  {
    return results[n];
  }

  results.push_back(n * factorial(n - 1));

  return results[n];
}

int factorial(int n)
{
  if (n <= 0) {
    return 1;
  }

  return n * factorial(n - 1);
}

// 2
int sumDigits(int x)
{
	if (x < 10)
		return x;

	return sumDigits(x / 10) + x % 10;
}

// 3
void printBinary(unsigned int x)
{
  if (x > 1)
  {
    printBinary(x / 2);
  }

  std::cout << (x % 2);
}


int main()
{
  std::cout << "Enter an integer: ";
  int x{};
  std::cin >> x;

}