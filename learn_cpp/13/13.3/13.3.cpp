#include <array>
#include <cassert>
#include <iostream>

// 1
// a. A public member is a member of a class that can be accessed by anyone (e.g. the public)
// b. A private member is a member of a class that can only be accessed by other members of the class
// c. An access specifier determines who has access to members defined after the specifier
// d. 3 (public, private, protected)

// 2a
class Point3d
{
private:
  int m_x {};
  int m_y {};
  int m_z {};

public:
  void setValues(int x, int y, int z)
  {
    m_x = x;
    m_y = y;
    m_z = z;
  }

  void print()
  {
    std::cout << "<" << m_x << "," << m_y << "," << m_z << ">";
  }

  // 2b
  bool isEqual(const Point3d& p)
  {
    return (p.m_x == m_x) && (p.m_y == m_y) && (p.m_z == m_z);
  }

};

// 3
class Stack
{
private:

  using Array = std::array<int, 10>;
  using Index = Array::size_type;

  Array m_stack {};
  Index m_next {};

public:
  void reset()
  {
    m_next = 0;
  }

  bool push(int value)
  {
    if (m_next == m_stack.size())
    {
      return false;
    }

    m_stack[m_next++] = value;
  }

  int pop()
  {
    assert(m_next > 0 && "Cannot pop from empty stack");

    return m_stack[--m_next];
  }

  void print()
  {
    std::cout << "(";
    for (Index i{ 0 }; i < m_next; ++i)
    {
      std::cout << m_stack[i] << " ";
    }
    std::cout << ")\n";
  }
};

int main()
{
    Point3d point;
    point.setValues(1, 2, 3);

    point.print();
    std::cout << '\n';

    return 0;
}