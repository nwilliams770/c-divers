#include <iostream>

class Shape
{
public:
  virtual std::ostream& print(std::ostream& out) const = 0;

  friend std::ostream& operator<<(std::ostream& out, const Shape& s)
  {
    return s.print(out);
  }

  virtual ~Shape() = default;
};

int main()
{
  return 0;
}