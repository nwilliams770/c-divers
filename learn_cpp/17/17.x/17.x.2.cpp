#include <string>

class Fruit
{
private:
  std::string m_name;
  std::string m_color;

public:
  Fruit(std::string_view name, std::string_view color)
    : m_name{ name }, m_color{ color }
  {
  }

  const std::string& getName() const { return m_name; }
  const std::string& getColor() const { return m_color; }
};

class Apple: public Fruit
{
public:
  Apple(std::string_view color="red")
    : Fruit{ "apple", color }
  {
  }
};

class Banana: public Fruit
{
public:
  Banana()
    : Fruit{ "banana", "yellow" }
  {
  }
};