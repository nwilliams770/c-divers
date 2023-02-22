#include <iostream>

// A
class IntPair
{
public:
  int m_first {};
  int m_second {};

  void set(int first, int second)
  {
    m_first = first;
    m_second = second;
  }

  void print()
  {
    std::cout << "Pair(" << m_first << "," << m_second << ")\n";
  }
};

// B. Opt for class over struct here because we are adding member functions.

int main()
{
	IntPair p1;
	p1.set(1, 1); // set p1 values to (1, 1)

	IntPair p2 { 2, 2 }; // initialize p2 values to (2, 2)

	p1.print();
	p2.print();

	return 0;
}