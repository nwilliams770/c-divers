#include <algorithm>
#include <array>
#include <iostream>
#include <string>

// 1
struct Student {
  std::string name {};
  int points {};
};

// 2
struct Season
{
  std::string_view name{};
  double averageTemperature{};
};

int main()
{
  // 1
  const std::array<Student, 8> students{
  { { "Albert", 3 },
    { "Ben", 5 },
    { "Christine", 2 },
    { "Dan", 8 }, // Dan has the most points (8).
    { "Enchilada", 4 },
    { "Francis", 1 },
    { "Greg", 3 },
    { "Hagrid", 5 } }
  };

  const Student* bestScore{
    std::max_element(students.begin(), students.end(),
      [](const auto& a, const auto&b) {
        return (a.points < b.points);
      }
    )
  };

  std::cout << bestScore->name << "is the best student\n";

  // 2
  std::array<Season, 4> seasons{
    { { "Spring", 285.0 },
      { "Summer", 296.0 },
      { "Fall", 288.0 },
      { "Winter", 263.0 } }
  };

  std::sort(seasons.begin(), seasons.end(), [](const auto& a, const auto &b) {
    return a.averageTemperature < b.averageTemperature;
  });

  for (const auto& season : seasons)
  {
    std::cout << season.name << '\n';
  }

  return 0;
}