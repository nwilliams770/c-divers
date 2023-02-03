#include <array>
#include <iostream>

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

using Deck = std::array<Card, 52>;
using Index = Deck::size_type;

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



int main()
{
  return 0;
}