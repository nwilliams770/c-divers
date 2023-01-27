#include <iostream>
#include <iterator>

int* findValue(int* begin, int* end, int target)
{
  for (int* p{ begin }; p != end; ++p)
  {
    if (*p == target)
    {
      return p;
    }
  }
  return end;
}

int main()
{
  int arr[]{ 1, 2, 3, 4, 5 };
  int* found{ findValue(std::begin(arr), std::end(arr), 3) };

  if (found != std::end(arr))
  {
    std::cout << "Found " << *found << "!";
  }
  return 0;
}