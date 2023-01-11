#include <iostream>
#include <random>

namespace constants
{
  constexpr int targetLowerBound { 1 };
  constexpr int targetUpperBound { 100 };
  constexpr int guesses { 8 };
}

int main()
{
  return 0;
}

void run()
{
  std::random_device rd;
  std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_device for our seed
	std::mt19937 mt{ ss }; // initialize our Mersenne Twister with the std::seed_seq

	// Create a reusable random number generator that generates uniform numbers
	std::uniform_int_distribution die6{ constants::targetLowerBound, constants::targetLowerBound }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

  do
  {
    std::cout << "Let's play a game. I'm thinking of a number between "
    << constants::targetLowerBound << " and " << constants::targetUpperBound <<
    ". You have" << constants::guesses << "tries to guess what it is.";

    int target{ die6(mt) };

    bool won{ newGame(target, constants::guesses) };
    if (won)
    {
      std::cout << "Correct! You win!";
    }
    else
    {
      std::cout << "Sorry, you lose. The correct number was " << target << ".";
    }
  } while (playAgain());
}


bool newGame(int target, int guesses)
{
  for (int count { 1 }; count < guesses; ++count)
  {
    std::cout << "Guess #" << count << ": ";

    int guess { getGuess() };

    if (guess > target)
    {
      std::cout << "Your guess is too high.";
    }
    else if (guess < target)
    {
      std::cout << "Your guess is too low.";
    }
    else
    {
      return true;
    }
  }

  return false;
}

bool playAgain()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Would you like to play again (y/n)?";
        char operation{};
        std::cin >> operation;
        ignoreLine(); // // remove any extraneous input

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case 'y':
        case 'Y':
          return true;
        case 'n':
        case 'N':
            return false;
        default: // otherwise tell the user what went wrong
            std::cerr << "Oops, that input is invalid. Please try again.\n";
        }
    } // and try again
}

int getGuess()
{
  while (true)
  {
    int guess{};
    std::cin >> guess;

    // Check for failed extraction
    if (!std::cin) // has a previous extraction failed?
    {
      // yep, so let's handle the failure
      std::cin.clear(); // put us back in 'normal' operation mode
      ignoreLine(); // and remove the bad input
      std::cerr << "Oops, that input is invalid.  Please try again.\n";
    }
    else if (guess < constants::targetLowerBound || guess > constants::targetUpperBound)
    {
      ignoreLine();
      std::cerr << "Oops, that input is out of bounds.  Please guess a number from"
      << constants::targetLowerBound << " to " << constants::targetUpperBound << ".\n";
    }
    else
    {
      ignoreLine(); // remove any extraneous input
      return guess;
    }
  }
}

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}