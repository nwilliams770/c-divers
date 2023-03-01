#include <algorithm>
#include <iostream>
#include <numeric> // for std::gcd
#include <string>
#include <string_view>
#include <vector>

// 1
class Fraction
{
private:
	int m_numerator{};
	int m_denominator{};

public:
	Fraction(int numerator = 0, int denominator = 1) :
		m_numerator{ numerator }, m_denominator{ denominator }
	{
		// We put reduce() in the constructor to ensure any new fractions we make get reduced!
		// Any fractions that are overwritten will need to be re-reduced
		reduce();
	}

	void reduce()
	{
		int gcd{ std::gcd(m_numerator, m_denominator) };
		if (gcd)
		{
			m_numerator /= gcd;
			m_denominator /= gcd;
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);

  friend bool operator== (const Fraction& f1, const Fraction& f2);
  friend bool operator!= (const Fraction& f1, const Fraction& f2);

  friend bool operator< (const Fraction& f1, const Fraction& f2);
  friend bool operator> (const Fraction& f1, const Fraction& f2);

  friend bool operator<= (const Fraction& f1, const Fraction& f2);
  friend bool operator>= (const Fraction& f1, const Fraction& f2);
};

bool operator== (const Fraction& f1, const Fraction& f2)
{
  return (f1.m_numerator == f2.m_numerator) && (f1.m_denominator == f2.m_denominator);
}

bool operator!= (const Fraction& f1, const Fraction& f2)
{
  return !(operator==(f1, f2));
}

bool operator< (const Fraction& f1, const Fraction& f2)
{
  return (f1.m_numerator * f2.m_denominator < f2.m_numerator * f1.m_denominator);
}

bool operator> (const Fraction& f1, const Fraction& f2)
{
  return operator<(f2, f1);
}

bool operator<= (const Fraction& f1, const Fraction& f2)
{
  return !(operator<(f1, f2));
}

bool operator>= (const Fraction& f1, const Fraction& f2)
{
  return !(operator<(f2, f1));
}

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}

// 2
class Car
{
private:
    std::string m_make;
    std::string m_model;

public:
    Car(std::string_view make, std::string_view model)
        : m_make{ make }, m_model{ model }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Car& f1);

    friend bool operator== (const Car& c1, const Car& c2);
    friend bool operator!= (const Car& c1, const Car& c2);
    friend bool operator< (const Car& f1, const Car& f2);
};

bool operator== (const Car& c1, const Car& c2)
{
    return (c1.m_make == c2.m_make &&
            c1.m_model == c2.m_model);
}

bool operator!= (const Car& c1, const Car& c2)
{
    return (c1.m_make != c2.m_make ||
            c1.m_model != c2.m_model);
}

bool operator< (const Car& c1, const Car& c2)
{
  if (c1.m_make == c2.m_make)
  {
      return c1.m_model < c2.m_model;
  }
  else
  {
    return c1.m_make < c2.m_make;
  }
}

std::ostream& operator<< (std::ostream& out, const Car& c)
{
  out << "(" << c.m_make << ", " << c.m_model << ")";
  return out;
}

int main()
{
    Car corolla{ "Toyota", "Corolla" };
    Car camry{ "Toyota", "Camry" };

    if (corolla == camry)
        std::cout << "a Corolla and Camry are the same.\n";

    if (corolla != camry)
        std::cout << "a Corolla and Camry are not the same.\n";

    return 0;
}

int main()
{
  // 1
	Fraction f1{ 3, 2 };
	Fraction f2{ 5, 8 };

	std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << f2 << '\n';
	std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << f2 << '\n';
	std::cout << f1 << ((f1 < f2) ? " < " : " not < ") << f2 << '\n';
	std::cout << f1 << ((f1 > f2) ? " > " : " not > ") << f2 << '\n';
	std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << f2 << '\n';
	std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << f2 << '\n';

  // 2
  std::vector<Car> cars{
    { "Toyota", "Corolla" },
    { "Honda", "Accord" },
    { "Toyota", "Camry" },
    { "Honda", "Civic" }
  };

  std::sort(cars.begin(), cars.end()); // requires an overloaded operator<

  for (const auto& car : cars)
    std::cout << car << '\n'; // requires an overloaded operator<<

  return 0;

	return 0;
}