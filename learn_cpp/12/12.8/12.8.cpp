#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using Numbers = std::vector<int>;

namespace config
{
  constexpr int multiplierMin{ 2 };
  constexpr int multiplierMax{ 4 };
  constexpr int maxWrongAnswer{ 4 };
}

int getRandomInt(int min, int max)
{
  static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

  return std::uniform_int_distribution{ min, max }(mt);
}

Numbers generateNumbers(int start, int count, int multiplier)
{
  Numbers numbers(static_cast<Numbers::size_type>(count));

  int i{ start };

  for (auto& number : numbers)
  {
    number = ((i * i) * multiplier);
    ++i;
  }

  return numbers;
}

Numbers generateUserNumbers(int multiplier)
{
  std::cout << "Start where? ";
  int start{};
  std::cin >> start;

  std::cout << "How many? ";
  int count{};
  std::cin >> count;


}

int getUserGuess()
{
  std::cout << "> ";
  int guess{};
  std::cin >> guess;

  return guess;
}

bool findAndRemove(Numbers& numbers, int guess)
{
  auto found{ std::find(numbers.begin(), numbers.end(), guess)};

  // not found
  if (found == numbers.end())
  {
    return false;
  }
  else
  {
    numbers.erase(found);
    return true;
  }
}

int findClosestNumber(const Numbers& numbers, int guess)
{
  return *std::min_element(numbers.begin(), numbers.end(), [=](int a, int b) {
    return (std::abs(a - guess) < std::abs(b - guess));
  });
}

void printTask(Numbers::size_type count, int multiplier)
{
  std::cout << "Generated" << count
            << " square numbers. Do you know what each number is after multiplying it by "
            << multiplier << "?\n";
}

void printSuccess(Numbers::size_type numbersLeft)
{
  std::cout << "You got it! ";
  if (numbersLeft == 0)
  {
    std::cout << "You found all numbers, congrats!\n";
  }
  else
  {
    std::cout << numbersLeft << " number(s) left.\n";
  }
}

void printFailure(const Numbers& numbers, int guess)
{
  int closest{ findClosestNumber(numbers, guess) };

  std::cout << guess << " is wrong!";
  if (std::abs(closest - guess) <= config::maxWrongAnswer)
  {
    std::cout << "Try " << closest << " next time.\n";
  }
  else
  {
    std::cout << '\n';
  }
}

bool playRound(Numbers& numbers)
{
  int guess{ getUserGuess() };

  if (findAndRemove(numbers, guess))
  {
    printSuccess(numbers.size());

    return !numbers.empty();
  }
  else
  {
    printFailure(numbers, guess);
    return false;
  }
}

int main()
{
  int multiplier{ getRandomInt(config::multiplierMin, config::multiplierMax) };
  Numbers numbers{ generateUserNumbers(multiplier) };

  printTask(numbers.size(), multiplier);

  while (playRound(numbers))
    ;

  return 0;
}