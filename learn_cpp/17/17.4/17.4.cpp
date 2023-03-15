#include <string>

class Fruit
{
private:
  std::string m_name;
  std::string m_color;

public:
  Fruit(const std::string& name, const std::string& color)
    : m_name{ name }, m_color{ color }
  {
  }

	const std::string& getName() const { return m_name; }
	const std::string& getColor() const { return m_color; }
};

class Apple : public Fruit
{
private:
  double m_fiber;

public:
  Apple(const std::string& name, const std::string& color, double fiber):
    Fruit{ name, color }, m_fiber{ fiber }
  {
  }

  double getFiber() const { return m_fiber; }
};

class Banana : public Fruit
{
public:
  Banana(const std::string& name, const std::string& color):
    Fruit{ name, color }
  {
  }
};