#include <cstdint>
#include <cassert>
#include <iostream>
// 1a. point + point | normal/friend function
// 1b. -point | member function
// 1c. std::cout << point | normal/friend function
// 1d. point = 5 | member function


// 2
// We are not using an dynamically allocated memory so default copy and
// assignment operators are fine here -- no need to override.
class Average
{
private:
  std::int32_t m_total{};
  std::int8_t m_numbers{};

public:
  Average()
  {
  }

  Average& operator +=(int i);
  friend std::ostream& operator<<(std::ostream& out, const Average& avg);
};

Average& Average::operator+=(int i)
{
  m_total += i;
  m_numbers++;
  return *this;
}

std::ostream& operator<<(std::ostream& out, const Average& avg)
{
  double average{ static_cast<double>(avg.m_total) / avg.m_numbers };
  out << average;
  return out;
};

// 3
class IntArray
{
private:
  int m_length{};
  int* m_array{nullptr};

public:
  IntArray(int length): m_length{ length }
  {
    assert(length > 0);

    m_array = new int[m_length];
  }

  // Deep copy constructor
  IntArray(const IntArray& arr): m_length{ arr.m_length }
  {
    m_array = new int[m_length];

    int length{ arr.m_length };
    for (int i{ 0 }; i < length; ++i)
    {
      m_array[i] = arr.m_array[i];
    }
  }

  ~IntArray()
  {
    delete[] m_array;
  }

  IntArray& operator=(const IntArray& arr);
  int& operator[](int index);
  friend std::ostream& operator<<(std::ostream& out, const IntArray& arr);
};

IntArray& IntArray::operator=(const IntArray& arr)
{
  if (this == &arr)
  {
    return *this;
  }

  delete[] m_array;

  m_length = arr.m_length;
  m_array = new int[m_length];
  for (int i{ 0 }; i < m_length; ++i)
  {
    m_array[i] = arr.m_array[i];
  }

  return *this;
}


int& IntArray::operator[](int index)
{
  assert(index >= 0 && index < m_length);

  return m_array[index];
}

std::ostream& operator<<(std::ostream& out, const IntArray& arr)
{
  out << '[';
  int size { arr.m_length };
  for (int i{ 0 }; i < size; ++i)
  {
    out << arr.m_array[i];
  }

  out << ']';

  return out;
}

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };
	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	std::cout << b << '\n';

	return 0;
}