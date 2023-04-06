#include <iostream>
#include <string>
#include <string_view>

// 1
template <typename T>
class Pair1
{
private:
  T m_x {};
  T m_y {};

public:
  Pair1(const T& x, const T& y): m_x{ x }, m_y{ y }
  {
  }

  T& first() { return m_x; }
  T& second() { return m_y; }
  const T& first() const { return m_x; }
	const T& second() const { return m_y; }
};

// 2
template <typename T, typename S>
class Pair
{
private:
  T m_x {};
  S m_y {};

public:
  Pair(const T& x, const S& y): m_x{ x }, m_y{ y }
  {
  }

  T& first() { return m_x; }
  S& second() { return m_y; }
  const T& first() const { return m_x; }
	const S& second() const { return m_y; }
};

template <typename T>
class StringValuePair: public Pair<std::string, T>
{
public:
	StringValuePair(std::string_view key, const T& value)
  // must cast std::string_view to std::string
		: Pair<std::string, T>{ static_cast<std::string>(key), value }
	{
	}
};

int main()
{
  // 1
	Pair1<int> p1 { 5, 8 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2 { 2.3, 4.5 };
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

  // 2
	Pair<int, double> p1 { 5, 6.7 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair<double, int> p2 { 2.3, 4 };
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';


  // 3
  StringValuePair<int> svp{ "Hello", 5 };
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

	return 0;
}