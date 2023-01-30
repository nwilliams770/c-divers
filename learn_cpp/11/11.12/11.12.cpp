#include <iostream>

int getNameCount()
{
  std::cout << "How many names would you like to enter? ";
  int count{};
  std::cin >> count;

  return count;
}

int getNames(std::string* names, int length)
{
  for (int i{ 0 }; i < length; ++i)
  {
    std::cout << "Enter name #" << (i + 1) << ": ";
    std::getline(std::cin >> std::ws, names[i]);
  }
}

void printNames(std::string* names, int length)
{
  std::cout << "\nHere is your sorted list of names:\n";
  for (int i{ 0 }; i < length; ++i)
  {
    std::cout << "Name #" << (i + 1) << ": " << names[i] << "\n";
  }
}

int main()
{
  int length { getNameCount() };

  std::string* names { new std::string[length]{} };

  getNames(names, length);

  std::sort(names, names + length);

  printNames(names, length);

  delete[] names;

  return 0;
}