#include "InitializeCharacters.h"

//Private constructor
InitializeCharacters::InitializeCharacters()
{

}

//Private destructor
InitializeCharacters::~InitializeCharacters()
{

}

//Static method to get the singleton instance
InitializeCharacters& InitializeCharacters::getInstance()
{
    static InitializeCharacters instance; // Singleton instance, created once and reused
    return instance;
}

//Core Functions
void InitializeCharacters::initialize()
{
    this->initCharacters();
    this->initStats();
}

//Character Functions
void InitializeCharacters::initCharacters()
{
    CharacterManager::getInstance().addCharacter("PLAYER", std::make_shared<Character>("PLAYER", "Player", 100, 100, 10, 10, 0, 25.f, 150.f, 0.319f, "Assets / Sprites / Player.png", true));
    CharacterManager::getInstance().addCharacter("ZIN", std::make_shared<Character>("ZIN", "Zin", 100, 100, 10, 10, 5, 25.f, 420.f, 0.066f, "Assets/Sprites/zinSprite.png", false));
    CharacterManager::getInstance().addCharacter("THOM", std::make_shared<Character>("THOM", "Thom", 100, 100, 10, 10, 0, 25.f, 690.f, 0.625f, "Assets/Sprites/thomNormal.png", false));
}

//Stat Functions
void InitializeCharacters::initStats()
{
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterManager::getInstance().getCharacter("PLAYER")->getDamage(), 1.4);
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterManager::getInstance().getCharacter("PLAYER")->getHpMax(), 1.5);
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->createStat("DEFENSE", "DEF", "Defense", CharacterManager::getInstance().getCharacter("PLAYER")->getDefense(), 1.5);

    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterManager::getInstance().getCharacter("ZIN")->getDamage(), 1.4);
    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterManager::getInstance().getCharacter("ZIN")->getHpMax(), 1.5);
    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->createStat("HEALING", "HEA", "Healing", CharacterManager::getInstance().getCharacter("ZIN")->getHealing(), 1.5);
}