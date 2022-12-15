#include <iostream>

int getInt()
{
  int input{};
  std::cout << "Enter a value from 0 to 255: ";
  std::cin >> input;

  return input;
}

int printAndDecrementOne(int x, int pow)
{
    std::cout << '1';
    return (x - pow);
}

// x is our number to test
// pow is a power of 2 (e.g. 128, 64, 32, etc...)
int printAndDecrementBit(int x, int pow)
{
    // Test whether our x is greater than some power of 2 and print the bit
    if (x >= pow)
        return printAndDecrementOne(x, pow); // If x is greater than our power of 2, subtract the power of 2

    // x is less than pow
    std::cout << '0';
    return x;
}

int main()
{
  int input{ getInt() };

    input = printAndDecrementBit(input, 128);
    input = printAndDecrementBit(input, 64);
    input = printAndDecrementBit(input, 32);
    input = printAndDecrementBit(input, 16);

    std::cout << ' ';

    input = printAndDecrementBit(input, 8);
    input = printAndDecrementBit(input, 4);
    input = printAndDecrementBit(input, 2);
    input = printAndDecrementBit(input, 1);

    std::cout << '\n';

    return 0;

}