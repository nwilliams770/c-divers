#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 1
struct StudentGrade
{
  std::string name{};
  char grade;
};

class GradeMap
{
private:
  // 2 if we kept this sorted, we could use bin search (or another search algorithm)
  // in our override of operator[]. Much more efficient
  std::vector<StudentGrade> m_map{};

public:
  char& operator[](std::string_view name);
};

char& GradeMap::operator[](std::string_view name)
{
  auto found{ std::find_if(m_map.begin(), m_map.end(), [&](const auto& student) {
    return (student.name == name);
  } )};

  if (found != m_map.end())
  {
    return found->grade;
  }

  m_map.push_back({ std::string(name) });

  return m_map.back().grade;
}

int main()
{
	GradeMap grades{};

  // std::vector may have to resize after adding "Frank" and if it does, the ref
  // to Joe's grade becomes a dangling reference. Dangerous!
	char& gradeJoe{ grades["Joe"] }; // does a push_back
	gradeJoe = 'A';

	char& gradeFrank{ grades["Frank"] }; // does a push_back
	gradeFrank = 'B';

	std::cout << "Joe has a grade of " << gradeJoe << '\n';
	std::cout << "Frank has a grade of " << gradeFrank << '\n';

	return 0;
}
