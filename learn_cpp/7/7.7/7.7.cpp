#include <iostream>


void printAlphabet()
{
  char c{'a'};
  while (c <= 'z')
  {
    std::cout << c << ' ' << static_cast<int>(c) << '\n';
    c++;
  }
}

void numPyramid()
{
  // outer loops between 1 and 5
  int outer{ 1 };
  while (outer <= 5)
  {

    int inner{ 5 };
		while (inner >= 1)
		{
			// The first number in any row is the same as the row number
			// So number should be printed only if it is <= the row number, space otherwise
			if (inner <= outer)
				std::cout << inner << ' '; // print the number and a single space
			else
				std::cout << "  "; // don't print a number, but print two spaces

			--inner;
		}

		// A row has been printed, move to the next row
		std::cout << '\n';

		++outer;
  }
}

void invertedNumPyramid()
{
  // outer loops between 1 and 5
  int outer{ 5 };
  while (outer >= 1)
  {
      // For each iteration of the outer loop, the code in the body of the loop executes once

      // inner loops between 1 and outer
      int inner{ outer };
      while (inner >= 1)
      {
        std::cout << inner-- << ' ';
      }

      // print a newline at the end of each row
      std::cout << '\n';
      --outer;
  }
}


int main()
{
  printAlphabet();
  return 0;
}