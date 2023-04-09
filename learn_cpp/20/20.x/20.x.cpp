#include <iostream>
#include <stdexcept>

class Fraction
{
private:
  int m_numerator = 0;
  int m_denominator = 1;

public:
  Fraction(int numerator = 0, int denominator = 1):
    m_numerator{ numerator }, m_denominator{ denominator }
  {
    if (denominator == 0)
    {
      throw std::runtime_error{"Invalid denominator"};
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
};

std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
  out << f.m_numerator << '/' << f.m_denominator;
  return out;
}

int main()
{
  std::cout << "Enter a numerator: ";
  int numerator{};
  std::cin >> numerator;

  std::cout << "Enter a denominator: ";
  int denominator{};
  std::cin >> denominator;

  try
  {
    Fraction f{ numerator, denominator };
    std::cout << "Fraction successfully created: " << f << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}