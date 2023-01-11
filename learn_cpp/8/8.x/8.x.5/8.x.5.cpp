#include <iostream>

template <typename T>
T add(T x, T y)
{
  return x + y;
}

template <typename T>
T mult(T x, int y)
{
  return x * y;
}

template <typename T, typename U>
auto sub(T x, U y)
{
  return x - y;
}

// C++20 abbreviated function template
// auto sub(auto x, auto y)
// {
//   return x - y;
// }

int main()
{
	std::cout << add(2, 3) << '\n';
	std::cout << add(1.2, 3.4) << '\n';

  std::cout << mult(2, 3) << '\n';
	std::cout << mult(1.2, 3) << '\n';

	return 0;
}