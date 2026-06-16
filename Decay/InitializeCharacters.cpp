#include "InitializeCharacters.h"
#include "CharacterUnlockRegistry.h"
#include "GameFlags.h"
#include "TriggerManager.h"
#include "NPCManager.h"

// Private constructor
InitializeCharacters::InitializeCharacters()
{}

// Private destructor
InitializeCharacters::~InitializeCharacters()
{}

// Static method to get the singleton instance
InitializeCharacters& InitializeCharacters::getInstance()
{
    static InitializeCharacters instance;
    return instance;
}

// Core Functions
void InitializeCharacters::initialize()
{
    this->initCharacters();
    this->initStats();
    this->initLore();
    this->initNPCs();
    this->restoreUnlockedCharacters();
}

// Character Functions
void InitializeCharacters::initCharacters()
{
    // ── Unlocked from the start ───────────────────────────────────────────
    CharacterManager::getInstance().addCharacter("PLAYER", std::make_shared<Character>("PLAYER", "Player", 40, 40, 10, 10, 0, 25.f, 150.f, 0.319f, "Assets/Sprites/Player.png", true));
    CharacterManager::getInstance().addCharacter("ZIN", std::make_shared<Character>("ZIN", "Zin", 30, 30, 10, 10, 5, 25.f, 420.f, 0.066f, "Assets/Sprites/zinSprite.png", false));

    // ── Must be unlocked ──────────────────────────────────────────────────
    // These are constructed and held in CharacterUnlockRegistry until their
    // unlock trigger fires (event completion, boss defeat, or shop purchase).
    // They will not appear in CharacterManager until then.
    CharacterUnlockRegistry::getInstance().registerCharacter("OVI", std::make_shared<Character>("OVI", "Ovi", 40, 40, 10, 10, 0, 25.f, 690.f, 0.625f, "Assets/Sprites/thomNormal.png", false));
    CharacterUnlockRegistry::getInstance().registerCharacter("JUNE", std::make_shared<Character>("JUNE", "June", 50, 50, 10, 10, 0, 25.f, 960.f, 0.625f, "Assets/Sprites/june.png", false));
    CharacterUnlockRegistry::getInstance().registerCharacter("SULIMAN", std::make_shared<Character>("SULIMAN", "Suliman", 10, 10, 20, 10, 0, 25.f, 960.f, 0.590f, "Assets/Sprites/suliman.png", false));
    CharacterUnlockRegistry::getInstance().registerCharacter("LYRA", std::make_shared<Character>("LYRA", "Lyra", 35, 35, 14, 10, 3, 25.f, 960.f, 1.f, "Assets/Sprites/Lyra.png", false));
}

// Initialize NPCs for game
void InitializeCharacters::initNPCs()
{
    // NPCs are now loaded from Assets/Data/emotions.db via EmotionDatabase
}

// Stat Functions
void InitializeCharacters::initStats()
{
    // ── Start unlocked — pull from CharacterManager ───────────────────────
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterManager::getInstance().getCharacter("PLAYER")->getDamage(), 2.0f);
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterManager::getInstance().getCharacter("PLAYER")->getHpMax(), 1.0f);
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->createStat("DEFENSE", "DEF", "Defense", CharacterManager::getInstance().getCharacter("PLAYER")->getDefense(), 1.0f);

    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterManager::getInstance().getCharacter("ZIN")->getDamage(), 1.0f);
    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterManager::getInstance().getCharacter("ZIN")->getHpMax(), 1.2f);
    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->createStat("HEALING", "HEA", "Healing", CharacterManager::getInstance().getCharacter("ZIN")->getHealing(), 2.0f);

    // ── Locked — pull from CharacterUnlockRegistry ────────────────────────
    CharacterUnlockRegistry::getInstance().getPending("OVI")->getStats()->createStat("ENVIGORATE", "ENV", "Buff", CharacterUnlockRegistry::getInstance().getPending("OVI")->getDamage(), 2.0f);
    CharacterUnlockRegistry::getInstance().getPending("OVI")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterUnlockRegistry::getInstance().getPending("OVI")->getHpMax(), 1.2f);
    CharacterUnlockRegistry::getInstance().getPending("OVI")->getStats()->createStat("HEALING", "HEA", "Healing", CharacterUnlockRegistry::getInstance().getPending("OVI")->getHealing(), 1.0f);

    CharacterUnlockRegistry::getInstance().getPending("JUNE")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterUnlockRegistry::getInstance().getPending("JUNE")->getDamage(), 0.7f);
    CharacterUnlockRegistry::getInstance().getPending("JUNE")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterUnlockRegistry::getInstance().getPending("JUNE")->getHpMax(), 1.7f);
    CharacterUnlockRegistry::getInstance().getPending("JUNE")->getStats()->createStat("DEFENSE", "DEF", "Defense", CharacterUnlockRegistry::getInstance().getPending("JUNE")->getDefense(), 2.3f);

    CharacterUnlockRegistry::getInstance().getPending("SULIMAN")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterUnlockRegistry::getInstance().getPending("SULIMAN")->getDamage(), 3.0f);
    CharacterUnlockRegistry::getInstance().getPending("SULIMAN")->getStats()->createStat("VITALITY", "VIT", "Health", CharacterUnlockRegistry::getInstance().getPending("SULIMAN")->getHpMax(), 0.2f);
    CharacterUnlockRegistry::getInstance().getPending("SULIMAN")->getStats()->createStat("HEALING", "HEA", "Healing", CharacterUnlockRegistry::getInstance().getPending("SULIMAN")->getHealing(), 2.0f);

    CharacterUnlockRegistry::getInstance().getPending("LYRA")->getStats()->createStat("STRENGTH", "STR", "Damage", CharacterUnlockRegistry::getInstance().getPending("LYRA")->getDamage(), 1.0f);
    CharacterUnlockRegistry::getInstance().getPending("LYRA")->getStats()->createStat("DEBUFF", "DEB", "Debuff", CharacterUnlockRegistry::getInstance().getPending("LYRA")->getHpMax(), 2.0f);
    CharacterUnlockRegistry::getInstance().getPending("LYRA")->getStats()->createStat("HEALING", "HEA", "Healing", CharacterUnlockRegistry::getInstance().getPending("LYRA")->getHealing(), 2.0f);
}

// Lore Functions
void InitializeCharacters::initLore()
{
    CharacterManager::getInstance().getCharacter("PLAYER")->getStats()->setTipText(
        "A reluctant adventurer, more years on the road than years of practice with that sword. Whatever's waiting out in the decay, it's not going to introduce itself first."
    );

    CharacterManager::getInstance().getCharacter("ZIN")->getStats()->setTipText(
        "Zin keeps the party standing more than anyone cares to admit. Quick with a poultice, quicker with a kind word -- though anyone who's seen her in a real fight knows not to call her harmless."
    );

    CharacterUnlockRegistry::getInstance().getPending("OVI")->getStats()->setTipText(
        "Ovi has a way of making everyone fight just a little harder before the first blow even lands. Nobody's quite sure how it works. Ovi isn't telling."
    );

    CharacterUnlockRegistry::getInstance().getPending("JUNE")->getStats()->setTipText(
        "June plants herself between danger and everyone else without a second thought -- slow to strike, slower still to fall."
    );

    CharacterUnlockRegistry::getInstance().getPending("SULIMAN")->getStats()->setTipText(
        "Suliman hits like the decay itself wants him gone -- and breaks just as easily. Keep him standing, and let the rest take care of itself."
    );

    CharacterUnlockRegistry::getInstance().getPending("LYRA")->getStats()->setTipText(
        "Lyra moves with the grace of someone who's spent years learning to dance with death. Her presence is a reminder that even in the darkest moments, there's always a way to find your footing."
    );
}

// Save / load support
void InitializeCharacters::restoreUnlockedCharacters()
{
    // Re-fire unlock triggers for any characters already unlocked in a
    // previous session. CharacterUnlockRegistry::unlockCharacter() guards
    // against double-unlock and suppresses the notification on re-add.
    auto& flags = GameFlags::getInstance();
    auto& triggers = TriggerManager::getInstance();

    if (flags.has("character_unlocked_OVI"))     triggers.fire("unlock_ovi");
    if (flags.has("character_unlocked_JUNE"))    triggers.fire("unlock_june");
    if (flags.has("character_unlocked_SULIMAN")) triggers.fire("unlock_suliman");
    if (flags.has("character_unlocked_LYRA"))    triggers.fire("unlock_lyra");
}