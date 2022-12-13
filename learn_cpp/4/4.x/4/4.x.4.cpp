#include <iostream>

constexpr float EarthGravity = 9.8; // meters/second

double getDouble()
{
  std::cout << "Enter the height of the tower in meters: ";
  double input{};
  std::cin >> input;
  return input;
}

void printResult(int seconds, double height)
{
  std::cout << "At " << seconds << " seconds, the ball is at height: " << height << " meters" << '\n';
}

int main()
{
  double height{ getDouble() };
  int seconds_elapsed = 0;
  int current_velocity = 0;
  while (height >= current_velocity) {
    printResult(seconds_elapsed, height);
    current_velocity += EarthGravity;
    seconds_elapsed++;
  }

  printResult(seconds_elapsed+1, 0);
  return 0;
}