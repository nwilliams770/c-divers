#include <iostream>


enum class MonsterType
{
  ogre,
  dragon,
  orc,
  giant_spider,
  slime,
};

struct Monster
{
  MonsterType type {};
  std::string name {};
  int health {};
};

constexpr std::string_view getMonsterType(MonsterType monsterType)
{
    switch (monsterType)
    {
    case MonsterType::ogre: return "Ogre";
    case MonsterType::dragon:   return "Dragon";
    case MonsterType::orc:  return "Orc";
    case MonsterType::giant_spider:  return "Giant Spider";
    case MonsterType::slime:  return "Slime";
    default:    return "Unknown";
    }
}

constexpr std::string_view printMonster(const Monster& monster)
{
  std::cout << "This " << getMonsterType(monster.type) << " is named " << monster.name
    << " and has " << monster.health << " health.\n";
};

int main()
{
	Monster ogre{ MonsterType::ogre, "Torg", 145 };
	Monster slime{ MonsterType::slime, "Blurp", 23 };

	printMonster(ogre);
	printMonster(slime);

  return 0;
}