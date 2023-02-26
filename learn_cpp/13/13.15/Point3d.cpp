#include <Point3d.h>
#include <Vector3d.h>

#include <iostream>

Point3d::Point3d(double x = 0.0, double y = 0.0, double z = 0.0)
  : m_x{x}, m_y{y}, m_z{z}
{
}

void Point3d::print() const
{
  std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n";
}

void Point3d::moveByVector(const Vector3d& v)
{
  m_x += v.m_x;
  m_y += v.m_y;
  m_z += v.m_z;
}