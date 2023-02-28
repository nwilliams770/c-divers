#include <cassert>
#include <iostream>
#include <numeric>

class Fraction
{
  private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

  public:
    Fraction(int n, int d)
    {
      assert(d != 0 && "denominator cannot be zero");

      m_numerator = n;
      m_denominator = d;

      reduce();
    }

    void print()
    {
      std::cout << m_numerator << "/" << m_denominator << '\n';
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

    friend Fraction operator*(const Fraction& frac, int x);
    friend Fraction operator*(int x, const Fraction& frac);
    friend Fraction operator*(const Fraction& frac1, const Fraction& frac2);

};

Fraction operator*(const Fraction& frac, int x)
{
  return { (frac.m_numerator * x), frac.m_denominator };
}

Fraction operator*(int x, const Fraction& frac)
{
  return frac * x;
}

Fraction operator*(const Fraction& frac1, const Fraction& frac2)
{
  return { (frac1.m_numerator * frac2.m_numerator), (frac1.m_denominator, frac2.m_denominator)};
}
