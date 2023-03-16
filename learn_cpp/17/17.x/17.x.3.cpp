#include <iostream>
#include <string>

class Creature
{
protected:
  std::string m_name{};
  char m_symbol{};
  int m_health{};
  int m_damage{};
  int m_gold{};

public:
  Creature(std::string_view name, char symbol, int health, int damage, int gold)
    : m_name{ name }
    , m_symbol{ symbol }
    , m_health{ health }
    , m_damage{ damage }
    , m_gold{ gold }
  {
  }

  const std::string& getName() const { return m_name; }
  char getSymbol() const { return m_symbol; }
  int getHealth() const { return m_health; }
  int getDamage() const { return m_damage; }
  int getGold() const { return m_gold; }

  void reduceHealth(int damage) { m_health -= damage; }
  bool isDead() const { return m_health <= 0; }
  void addGold(int gold) { m_gold += gold; }
};

namespace NewPlayer {
  char constexpr symbol = '@';
  int constexpr health = 10;
  int constexpr damage = 1;
  int constexpr gold = 0;
  int constexpr level = 1;
}

class Player: public Creature
{
private:
  int m_level{};

public:
  Player(std::string_view name)
    : m_level{ NewPlayer::level }
    , Creature{ name, NewPlayer::symbol, NewPlayer::health, NewPlayer::damage, NewPlayer::gold }
  {
  }

  int getLevel() const { return m_level; }
};

int main()
{
  std::cout << "Enter your name: "
  std::string playerName;
  std::cin >> playerName;

  Player p{ playerName };

  std::cout << "Welcome " << p.getName() << ".\n";
  std::cout << "You have " << p.getHealth() << " health and are carrying " <<
    p.getGold() << " gold.\n"



  return 0;
}