#include <iostream>
#include <utility>

int main()
{
  return 0;
}

void bubbleSort(int arr[], const int len)
{
  bool swapsOccurred { false };
  int i { len - 1 };
  do
  {
    for (int j { 0 }; j < i; ++j)
    {
      if (arr[j] > arr[j + 1])
      {
        std::swap(arr[j], arr[i]);
        swapsOccurred = true;
      }
    }

    if (!swapsOccurred && i > 0)
    {
      std::cout << "Early termination: completed sorting in" << (len - i)
       << "iterations.\n";
    }
    --i; // last element has been sorted so do not re-evaluate it
  } while (!swapsOccurred);

  for (int index { 0 }; index < len; ++index)
  {
    std::cout << arr[index] << " ";
  }
  std::cout << "\n";
}
