#include <iostream>

namespace constants
{
    inline constexpr double pi { 3.14159 };
}

using Degrees = double;
using Radians = double;

Radians convertToRadians(Degrees degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    std::cout << "Enter a number of degrees: ";
    Degrees degrees{};
    std::cin >> degrees;

    Radians radians { convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";
    // radians = degrees
    // This will compile
    // Degrees and Radians are just aliases both representing double
    // So they can be re-assigned to one another but it should be
    // avoided as it doesn't make sense semantically

    return 0;
}
