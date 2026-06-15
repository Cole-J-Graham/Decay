#include "InitializeCharacters.h"
#include "NPCManager.h"

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
    this->initLore();
    this->initNPCs();
}

//Character Functions
void InitializeCharacters::initCharacters()
{
    CharacterManager::getInstance().addCharacter("PLAYER", std::make_shared<Character>("PLAYER", "Player", 40, 40, 10, 10, 0, 25.f, 150.f, 0.319f, "Assets/Sprites/Player.png", true));
    CharacterManager::getInstance().addCharacter("ZIN", std::make_shared<Character>("ZIN", "Zin", 30, 30, 10, 10, 5, 25.f, 420.f, 0.066f, "Assets/Sprites/zinSprite.png", false));
    CharacterManager::getInstance().addCharacter("OVI", std::make_shared<Character>("OVI", "Ovi", 40, 40, 10, 10, 0, 25.f, 690.f, 0.625f, "Assets/Sprites/thomNormal.png", false));
    CharacterManager::getInstance().addCharacter("JUNE", std::make_shared<Character>("JUNE", "June", 50, 50, 10, 10, 0, 25.f, 960.f, 0.625f, "Assets/Sprites/june.png", false));
    CharacterManager::getInstance().addCharacter("SULIMAN", std::make_shared<Character>("SULIMAN", "Suliman", 10, 10, 20, 10, 0, 25.f, 960.f, 0.590f, "Assets/Sprites/suliman.png", false));
}

//Initialize NPCs for game. Currently piped through here for simplicity, but may want to move to a separate function or class if it gets more complex.
void InitializeCharacters::initNPCs()
{
    // NPCs are now loaded from Assets/Data/emotions.db via EmotionDatabas
}

//Stat Functions
void InitializeCharacters::initStats()
{
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterManager::getInstance().getCharacter("PLAYER")->getDamage(), 2.0f);
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterManager::getInstance().getCharacter("PLAYER")->getHpMax(), 1.0f);
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->createStat("DEFENSE", "DEF", "Defense", CharacterManager::getInstance().getCharacter("PLAYER")->getDefense(), 1.0f);

    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterManager::getInstance().getCharacter("ZIN")->getDamage(), 1.0f);
    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterManager::getInstance().getCharacter("ZIN")->getHpMax(), 1.2f);
    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->createStat("HEALING", "HEA", "Healing", CharacterManager::getInstance().getCharacter("ZIN")->getHealing(), 2.0f);

    CharacterManager::getInstance().getCharacter("OVI")->getStats()->createStat("ENVIGORATE", "ENV", "Buff", CharacterManager::getInstance().getCharacter("OVI")->getDamage(), 2.0f);
    CharacterManager::getInstance().getCharacter("OVI")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterManager::getInstance().getCharacter("OVI")->getHpMax(), 1.2f);
    CharacterManager::getInstance().getCharacter("OVI")->getStats()->createStat("HEALING", "HEA", "Healing", CharacterManager::getInstance().getCharacter("OVI")->getHealing(), 1.0f);

    CharacterManager::getInstance().getCharacter("JUNE")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterManager::getInstance().getCharacter("JUNE")->getDamage(), 0.7f);
    CharacterManager::getInstance().getCharacter("JUNE")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterManager::getInstance().getCharacter("JUNE")->getHpMax(), 1.7f);
    CharacterManager::getInstance().getCharacter("JUNE")->getStats()->createStat("DEFENSE", "DEF", "Defense", CharacterManager::getInstance().getCharacter("JUNE")->getDefense(), 2.3f);

    CharacterManager::getInstance().getCharacter("SULIMAN")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterManager::getInstance().getCharacter("SULIMAN")->getDamage(), 3.0f);
    CharacterManager::getInstance().getCharacter("SULIMAN")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterManager::getInstance().getCharacter("SULIMAN")->getHpMax(), 0.2f);
    CharacterManager::getInstance().getCharacter("SULIMAN")->getStats()->createStat("HEALING", "HEA", "Healing", CharacterManager::getInstance().getCharacter("SULIMAN")->getHealing(), 2.0f);
}

//Lore Functions
void InitializeCharacters::initLore()
{
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->setTipText(
        "A reluctant adventurer, more years on the road than years of practice with that sword. Whatever's waiting out in the decay, it's not going to introduce itself first."
    );

    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->setTipText(
        "Zin keeps the party standing more than anyone cares to admit. Quick with a poultice, quicker with a kind word -- though anyone who's seen her in a real fight knows not to call her harmless."
    );

    CharacterManager::getInstance().getCharacter("OVI")->getStats()->setTipText(
        "Ovi has a way of making everyone fight just a little harder before the first blow even lands. Nobody's quite sure how it works. Ovi isn't telling."
    );

    CharacterManager::getInstance().getCharacter("JUNE")->getStats()->setTipText(
        "June plants herself between danger and everyone else without a second thought -- slow to strike, slower still to fall."
    );

    CharacterManager::getInstance().getCharacter("SULIMAN")->getStats()->setTipText(
        "Suliman hits like the decay itself wants him gone -- and breaks just as easily. Keep him standing, and let the rest take care of itself."
    );
}