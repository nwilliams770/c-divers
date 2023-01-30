#include <iostream>

int main()
{
  constexpr std::string_view names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};

  std::cout << "Enter a name: ";
  std::string username{};
  std::cin >> username;

  bool found { false };

  for (auto name : names )
  {
    if (username == name)
    {
      found = true;
      break;
    }
  }

  if (found)
  {
    std::cout << username << "was found.";
  } else {
    std::cout << username << "was not found";
  }

  return 0;
}