#include <iostream>
#include <string>

// 1a
class Ball
{
private:
  std::string m_color{ "black"};
  double m_radius{ 10.0 };

public:
  Ball() = default;

  Ball(std::string color, double radius)
  {
    m_color = color;
    m_radius = radius;
  }

  Ball(std::string color)
  {
    m_color = color;
  }

  Ball(double radius)
  {
    m_radius = radius;
  }

  void print()
  {
    std::cout << "color: " << m_color << ", " << "radius: " << m_radius << '\n';
  }
};

// 1b
class BallWithDefaultParams
{
private:
  std::string m_color{};
  double m_radius{};

public:
  BallWithDefaultParams(std::string color = "black", double radius = 10.0)
  {
    m_color = color;
    m_radius = radius;
  }

  BallWithDefaultParams(double radius)
  {
    m_color = "black";
    m_radius = radius;
  }

  void print()
  {
    std::cout << "color: " << m_color << ", " << "radius: " << m_radius << '\n';
  }
};

// 2
// If you do not define a default constructor, the compiler will create
// a public, empty default constructor for you