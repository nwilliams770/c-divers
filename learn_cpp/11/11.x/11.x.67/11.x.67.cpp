#include <algorithm> // for std::shuffle
#include <array>
#include <ctime> // for std::time
#include <iostream>
#include <random> // for std::mt19937

enum class CardSuit
{
  club,
  heart,
  spade,
  diamond,
  max_suits,
};

enum class CardRank
{
  rank_2,
  rank_3,
  rank_4,
  rank_5,
  rank_6,
  rank_7,
  rank_8,
  rank_9,
  rank_10,
  rank_jack,
  rank_queen,
  rank_king,
  rank_ace,

  max_ranks,
};

struct Card {
  CardSuit suit;
  CardRank rank;
};

struct Player {
  int score {};
};

using Deck = std::array<Card, 52>;
using Index = Deck::size_type;

constexpr int g_maxScore{ 21 };
constexpr int g_dealerMinScore{ 17 };

void printCard(const Card& card) {
    switch (card.rank)
    {
    case CardRank::rank_2:      std::cout << '2';   break;
    case CardRank::rank_3:      std::cout << '3';   break;
    case CardRank::rank_4:      std::cout << '4';   break;
    case CardRank::rank_5:      std::cout << '5';   break;
    case CardRank::rank_6:      std::cout << '6';   break;
    case CardRank::rank_7:      std::cout << '7';   break;
    case CardRank::rank_8:      std::cout << '8';   break;
    case CardRank::rank_9:      std::cout << '9';   break;
    case CardRank::rank_10:     std::cout << 'T';   break;
    case CardRank::rank_jack:   std::cout << 'J';   break;
    case CardRank::rank_queen:  std::cout << 'Q';   break;
    case CardRank::rank_king:   std::cout << 'K';   break;
    case CardRank::rank_ace:    std::cout << 'A';   break;
    default:
        std::cout << '?';
        break;
    }

    switch (card.suit)
    {
    case CardSuit::club:       std::cout << 'C';   break;
    case CardSuit::diamond:    std::cout << 'D';   break;
    case CardSuit::heart:      std::cout << 'H';   break;
    case CardSuit::spade:      std::cout << 'S';   break;
    default:
        std::cout << '?';
        break;
    }
}

void printDeck(const Deck& deck)
{
  for (const auto& card : deck)
  {
    printCard(card);
    std::cout << ' ';
  }

  std::cout << '\n';
}

Deck createDeck()
{
  Deck deck{};
  Index index{ 0 };

  for (int suit{ 0 }; suit < static_cast<int>(CardSuit::max_suits); ++suit)
  {
    for (int rank{ 0 }; rank < static_cast<int>(CardRank::max_ranks); ++rank)
    {
      deck[index].suit = static_cast<CardSuit>(suit);
      deck[index].rank = static_cast<CardRank>(rank);
      ++index;
    }
  }

  return deck;
}

void shuffleDeck(Deck& deck)
{
// mt is static so it only gets seeded once.
  static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

  std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(const Card& card)
{
  switch (card.rank)
  {
  case CardRank::rank_2:        return 2;
  case CardRank::rank_3:        return 3;
  case CardRank::rank_4:        return 4;
  case CardRank::rank_5:        return 5;
  case CardRank::rank_6:        return 6;
  case CardRank::rank_7:        return 7;
  case CardRank::rank_8:        return 8;
  case CardRank::rank_9:        return 9;
  case CardRank::rank_10:       return 10;
  case CardRank::rank_jack:     return 10;
  case CardRank::rank_queen:    return 10;
  case CardRank::rank_king:     return 10;
  case CardRank::rank_ace:      return 11;
  default:
    assert(false && "should never happen");
    return 0;
  }
}

bool playerWantsToHit()
{
  while (true)
  {
    std::cout << "(h)it or (s)tand?: ";

    char input{};

    std::cin >> input;

    switch (input)
    {
      case 'h':
        return true;
      case 's':
        return false;
    }
  }
}

// Return true on bust
bool playerTurn(const Deck& deck, Index& nextCardIndex, Player& player)
{
  while (true)
  {
    if (player.score > g_maxScore)
    {
      std::cout << "You busted!\n";
      return true;
    } else {
      if (playerWantsToHit())
      {
        int cardValue{ getCardValue(deck.at(nextCardIndex++)) };
        player.score += cardValue;
        std::cout << "You were dealt a " << cardValue << " and now have " << player.score << '\n';
      } else {
        return false;
      }
    }
  }
}

// Return true on bust
bool dealerTurn(const Deck& deck, Index& nextCardIndex, Player& dealer)
{
  while (dealer.score <= g_dealerMinScore)
  {
    int cardValue{ getCardValue(deck.at(nextCardIndex++)) };
    dealer.score += cardValue;
    std::cout << "The dealer turned up a " << cardValue << " and now has " << dealer.score << '\n';
  }

  if (dealer.score > g_maxScore)
  {
    std::cout << "The dealer busted!\n";
    return true;
  }

  return false;
}

bool playRound(const Deck& deck)
{
  Index nextCardIndex{ 0 };

  Player dealer{ getCardValue(deck.at(nextCardIndex))};
  nextCardIndex++;

  std::cout << "The dealer is showing: " << dealer.score << '\n';

  Player player{ getCardValue(deck.at(nextCardIndex)) + getCardValue(deck.at(nextCardIndex + 1)) };
  nextCardIndex += 2;

  std::cout << "You have: " << player.score << '\n';

  if (playerTurn(deck, nextCardIndex, player))
  {
    return false;
  }

  if (dealerTurn(deck, nextCardIndex, dealer))
  {
    return true;
  }

  return (player.score > dealer.score);
}


int main()
{
  auto deck{ createDeck() };

  shuffleDeck(deck);

  if (playRound(deck))
  {
    std::cout << "You win!\n";
  } else {
    std::cout << "You lose!\n";
  }

  return 0;
}