#include <iostream>

namespace animals
{
  enum Animal
  {
    chicken,
    dog,
    cat,
    elephant,
    duck,
    snake,
    max_animals,
  };
};

int main()
{
  int legs[animals::max_animals]{ 2, 4, 4, 4, 2, 0 };

  std::cout << "An elephant has " << legs[animals::elephant] << " legs.";

  double temps[365] { };
  return 0;
}