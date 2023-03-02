#include <cassert>
#include <iostream>
#include <string>

class MyString
{
private:
  std::string m_string{};

public:
  MyString(const std::string& string = {}): m_string{ string }
  {
  }

  MyString operator()(int start, int len);
  friend std::ostream& operator<<(std::ostream& out, const MyString& s);

  std::string_view substr(int start, int len);
};

	std::string_view MyString::substr(int start, int length)
	{
		assert(start >= 0);
		assert(start + length <= static_cast<int>(m_string.length()) && "MyString::substr(int, int): Substring is out of range");

		return std::string_view{ m_string }.substr(start, length);
	}

MyString MyString::operator()(int start, int len)
{
  assert(start >= 0);
  assert(start + len <= static_cast<int>(m_string.length()));

  // 2
  // substr() copies part of the string then copies it again to instantiate
  // MyString. A third copy is made when MyString gets copied to be returned to
  // caller.
  return m_string.substr(start, len);
}

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
  out << s.m_string;

  return out;
}