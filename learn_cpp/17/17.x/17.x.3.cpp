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

class Potion
{
public:
  enum PotionType
  {
    health,
    strength,
    poison,

    max_types,
  };

  enum PotionSize
  {
    small,
    medium,
    large,

    max_sizes
  };

private:
  PotionType m_type{};
  PotionSize m_size{};

public:
  Potion(PotionType type, PotionSize size): m_type{ type }, m_size{ size }
  {
  }

  PotionType getType() const { return m_type; }
  PotionSize getSize() const { return m_size; }

  static std::string_view getPotionTypeName(PotionType type)
  {
    static constexpr std::array names{
      "Health",
      "Strength",
      "Poison",
    };

    return names.at(static_cast<std::size_t>(type));
  }

  static std::string_view getPotionSizeName(PotionSize size)
  {
    static constexpr std::array sizes{
      "Small",
      "Medium",
      "Large",
    };

    return sizes.at(static_cast<std::size_t>(size));
  }

    std::string getName() const
    {
      return std::string(getPotionSizeName(getSize())) + " potion of " + std::string(getPotionTypeName(getType()));
    }

  static Potion getRandomPotion()
  {
    int type{ getRandomNumber(0, static_cast<int>(PotionType::max_types) - 1) };
    int size{ getRandomNumber(0, static_cast<int>(PotionSize::max_sizes) - 1) };

  }
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

  void drinkPotion(Potion& potion)
  {
    switch (potion.getType())
    {
    case Potion::health:
      m_health += ((potion.getSize() == Potion::large ? 5 : 2));
      break;
    case Potion::strength:
      ++m_damage;
      break;
    case Potion::poison:
      reduceHealth(1);
      break;
    case Potion::max_types:
      break;
    }
  }
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

void fightMonster(Player& player)
{
  Monster monster{ Monster::getRandomMonster() };
  std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";

  while (!monster.isDead() && !player.isDead())
  {
    std::cout << "(R)un or (F)ight: ";
    char action{};
    std::cin >> action;
    if (action == 'R' || action == 'r')
    {
      if (getRandomNumber(1, 2) == 1)
      {
        std::cout << "You got away safely.\n";
        return;
      }
      else
      {
        std::cout << "You couldn't get away!\n";
        attackPlayer(monster, player);
        continue;
      }
    }

    if (action == 'F' || action == 'f')
    {
      attackMonster(player, monster);
      attackPlayer(monster, player);
    }
  }
};

void onMonsterKilled(Player& player, Monster& monster)
{
  std::cout << "You slayed the " << monster.getName() << ".\n";
  player.levelUp();
  std::cout << "You are now level " << player.getLevel() << ".\n";
  std::cout << "You looted " << monster.getGold() << " gold.\n";
  player.addGold(monster.getGold());

  constexpr int potionChance{ 33 };
  if (getRandomNumber(1, 100) <= potionChance)
  {
    auto potion{ Potion::getRandomPotion() };

    std::cout << "You found a mythical and mysterious potion! Do you want to drink it? [y/n]";
    char choice{};
    std::cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
      player.drinkPotion(potion);
      std::cout << "You drank a " << potion.getName() << ".\n";
    }
  }
}

void attackMonster(Player& player, Monster& monster)
{
  if (player.isDead())
  {
    return;
  }

  std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << "damage.\n";
  monster.reduceHealth(player.getDamage());

  if (monster.isDead())
  {
    onMonsterKilled(player, monster);
  }
};

void attackPlayer(Monster& monster, Player& player)
{
  if (monster.isDead())
  {
    return;
  }

  player.reduceHealth(monster.getDamage());
  std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
};

int main()
{
  std::cout << "Enter your name: ";
  std::string playerName;
  std::cin >> playerName;

  Player player{ playerName };

  std::cout << "Welcome " << player.getName() << ".\n";
  std::cout << "You have " << player.getHealth() << " health and are carrying " <<
    player.getGold() << " gold.\n";

  while (!player.isDead() && !player.hasWon())
  {
    fightMonster(player);
  }

  if (player.isDead())
  {
    std::cout << "You died at level " << player.getLevel() << " with " << player.getGold() << "gold.\n";
  }
  else
  {
    std::cout << "You won the game with " << player.getGold() << " gold!\n";
  }

  return 0;
}