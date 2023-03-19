#include <array>
#include <cstdlib> // for rand() and srand()
#include <iostream>
#include <string>


// Generate a random number between min and max (inclusive)
// Assumes std::srand() has already been called
// Assumes max - min <= RAND_MAX
int getRandomNumber(int min, int max)
{
  static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) }; // static used for efficiency, so we only calculate this value once
  // evenly distribute the random number across our range
  return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

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

  void levelUp()
  {
    ++m_level;
    ++m_damage;
  }

  int getLevel() const { return m_level; }
  bool hasWon() const { return m_level >= 20; }
};

class Monster: public Creature
{
public:
	enum class Type
	{
		dragon,
		orc,
		slime,
		max_types
	};

private:
  static const Creature& getDefaultCreature(Type type)
  {
    static const std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData{
      { { "dragon", 'D', 20, 4, 100 },
        { "orc", 'o', 4, 2, 25 },
        { "slime", 's', 1, 1, 10 } }
    };

    return monsterData.at(static_cast<std::size_t>(type));
  }

public:
  Monster(Type type)
    : Creature{ getDefaultCreature(type) }
  {
  }

  static Monster getRandomMonster()
  {
    int num{ getRandomNumber(0, static_cast<int>(Type::max_types) - 1) };
    return Monster{ static_cast<Type>(num) };
  }
};

void fightMonster()
{

};

void attackMonster()
{

};

void attackPlayer()
{

};

int main()
{
  std::cout << "Enter your name: ";
  std::string playerName;
  std::cin >> playerName;

  Player p{ playerName };

  std::cout << "Welcome " << p.getName() << ".\n";
  std::cout << "You have " << p.getHealth() << " health and are carrying " <<
    p.getGold() << " gold.\n";

  while (!p.isDead() && !p.hasWon())
  {

  }

  return 0;
}