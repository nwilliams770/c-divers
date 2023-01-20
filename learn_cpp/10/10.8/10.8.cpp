#include <iostream>

struct AdvertisingMetrics
{
  int adsShown {};
  double engagementPercentage {};
  double earningsPerEngagement {};
};

AdvertisingMetrics getAdvertisingMetrics()
{
  AdvertisingMetrics temp;
  std::cout << "How many ads were shown today? ";
  std::cin >> temp.adsShown;
  std::cout << "What percentage of ads were clicked on by users? ";
  std::cin >> temp.engagementPercentage;
  std::cout << "What was the average earnings per click? ";
  std::cin >> temp.earningsPerEngagement;
  return temp;
}

void printAdvertisingMetrics(const AdvertisingMetrics& metrics)
{
    std::cout << "Number of ads shown: " << metrics.adsShown << '\n';
    std::cout << "Engagement percentage: " << metrics.engagementPercentage << '\n';
    std::cout << "Average earnings per engagement: $" << metrics.earningsPerEngagement << '\n';

  std::cout << "Total Earnings: $" <<
    (metrics.adsShown * metrics.engagementPercentage / 100 * metrics.earningsPerEngagement) << '\n';
}

struct Fraction
{
  int numerator { 0 };
  int denominator { 1 };
};

Fraction getFraction()
{
    Fraction temp{};
    std::cout << "Enter a value for numerator: ";
    std::cin >> temp.numerator;
    std::cout << "Enter a value for denominator: ";
    std::cin >> temp.denominator;
    std::cout << '\n';
    return temp;
}

Fraction multiply(const Fraction& f1, const Fraction& f2)
{
  return { (f1.numerator * f2.numerator), (f1.denominator * f2.denominator) };
}

void printFraction(const Fraction& f)
{
    std::cout << f.numerator << '/' << f.denominator;
}


int main()
{
  // #1
  AdvertisingMetrics metrics { getAdvertisingMetrics() };
  printAdvertisingMetrics(metrics);

  // #2
  Fraction f1{ getFraction() };
  Fraction f2{ getFraction() };

  std::cout << "Your fractions multiplied together: ";

  printFraction(multiply(f1, f2));
  return 0;
}

// #3
// We return Fraction by value from getFraction() because if we returned
// by reference we would be returning a DANGLING reference. The temp fraction
// instantiated in the scope of the function will be destroyed at the end
// of the function.

