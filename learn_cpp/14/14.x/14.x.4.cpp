#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>

class FixedPoint2
{
private:
  std::int16_t m_base{};
  std::int8_t m_decimal{};

public:
  FixedPoint2(std::int16_t base = 0, std::int8_t decimal = 0 ):
    m_base{ base }, m_decimal { decimal }
  {
    assert(m_decimal > -99 && m_decimal < 99);

    if (m_base < 0 || m_decimal < 0)
    {
      if (m_base > 0)
      {
        m_base = -m_base;
      }
      if (m_decimal > 0)
      {
        m_decimal = -m_decimal;
      }
    }
  }

  FixedPoint2(double d):
    m_base{ static_cast<std::int16_t>(std::trunc(d)) },
    m_decimal{ static_cast<std::int8_t>(std::round(d * 100) - m_base * 100) }
  {
  }

  operator double() const;
  FixedPoint2 operator-() const;
  friend bool operator==(const FixedPoint2& fp1, const FixedPoint2& fp2);

};

FixedPoint2::operator double() const
{
  return m_base + (static_cast<double>(m_decimal) / 100);
}

FixedPoint2 FixedPoint2::operator-() const
{
  return {
    static_cast<std::int16_t>(-m_base),
    static_cast<std::int8_t>(-m_decimal)
 };
}

FixedPoint2 operator+(const FixedPoint2& fp1, const FixedPoint2& fp2)
{
	return { static_cast<double>(fp1) + static_cast<double>(fp2) };
}


bool operator==(const FixedPoint2& fp1, const FixedPoint2& fp2)
{
  return (fp1.m_base == fp2.m_base && fp1.m_decimal == fp2.m_decimal);
}

std::ostream& operator<<(std::ostream& out, const FixedPoint2& fp)
{
  out << static_cast<double>(fp);
  return out;
}

std::istream& operator>>(std::istream& in, FixedPoint2& fp)
{
	double d{};
	in >> d;
	fp = FixedPoint2{ d };

	return in;
}

int main()
{
	FixedPoint2 a{ 34, 56 };
	std::cout << a << '\n';

	FixedPoint2 b{ -2, 8 };
	std::cout << b << '\n';

	FixedPoint2 c{ 2, -8 };
	std::cout << c << '\n';

	FixedPoint2 d{ -2, -8 };
	std::cout << d << '\n';

	FixedPoint2 e{ 0, -5 };
	std::cout << e << '\n';

	std::cout << static_cast<double>(e) << '\n';

	return 0;
}