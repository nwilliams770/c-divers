#include <array>
#include <iostream>
#include <numeric> // std::reduce
#include <vector>

// ***** #1 *****
enum ItemType
{
  item_health_potion,
  item_torch,
  item_arrow,
  max_items
};

using Inventory = std::array<int, ItemType::max_items>;

int countTotalItems(const Inventory& items)
{
  return std::reduce(items.begin(), items.end());
};

// ***** #2 *****
struct Student {
  std::string name {};
  int grade {};
};

int getNumberOfStudents()
{
  int numStudents{};

  do
  {
    std::cout << "How many students do you want to enter?\n";
    std::cin >> numStudents;

  } while (numStudents <= 0);

  return numStudents;
}

std::vector<Student> getStudents()
{
  using Students = std::vector<Student>;

  int numStudents{ getNumberOfStudents() };

  Students students(static_cast<Students::size_type>(numStudents));

  int studentNumber{ 1 };

  for (auto& student : students )
  {
    std::cout << "Enter name #" << studentNumber << ": ";
    std::cin >> student.name;
    std::cout << "Enter grade #" << studentNumber << ": ";
    std::cin >> student.grade;

    ++studentNumber;
  }

  return students;
};

bool compareStudents(const Student& a, const Student& b)
{
  return a.grade > b.grade;
};

// ****** #3 *****
void swap(int& a, int& b)
{
  int temp{ a };

  a = b;
  b = temp;
}

// ****** #4 *****
void printCString(const char* str)
{
  if (!str)
    return;

  while (*str != '\0')
  {
    std::cout << *str;

    ++str;
  }
}

int main()
{
  // #1
  Inventory items{ 2, 5, 10 };

  std::cout << "The player has " << countTotalItems(items) << "item(s) in total.\n";

  std::cout << "The player has" << items[ItemType::item_torch] << "torch(es)\n";

  // #2
  auto students{ getStudents() };

  std::sort(students.begin(), students.end(), compareStudents);

  for (const auto& student : students)
  {
    std::cout << student.name << " got a grade of " << student.grade << '\n';
  }

  // #3
  int a{ 6 };
  int b{ 2 };
  swap(a, b);

  if (a == 6 && b == 2)
  {
    std::cout << "swap() works\n";
  } else {
    std::cout << "swap() doesn't work\n";
  }

  // #4
  printCString("Hello universe!");
  std::cout << '\n';

  return 0;
}

// #5
// a. loop has an off-by-one err, should use operator< instead of operator<=.

// b. pointer points to a const int so it cannot be re-assigned.

// c. array will decay into a pointer when passed to a function which does not
// support range-based loops. opt for std::array instead for built-in fixed arrays.

// d. array is of fixed-length but being instantiated using a non-compile time constant.
// will also go out of scope at end of block, returning a dangling pointer. should
// opt for dynamic memory allocation or use std::vector.

// e. pointer is declared an a pointer to an int but is being assigned to a reference
// to a value of type double.