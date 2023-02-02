#include <array>
#include <iostream>
#include <numeric> // std::reduce

// #1
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

// #2
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
  using Stud
}

int main()
{
  // #1
  Inventory items{ 2, 5, 10 };

  std::cout << "The player has " << countTotalItems(items) << "item(s) in total.\n";

  std::cout << "The player has" << items[ItemType::item_torch] << "torch(es)\n";

  // #2



  return 0;

}