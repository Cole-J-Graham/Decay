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
    CharacterManager::getInstance().addCharacter("PLAYER", std::make_shared<Character>("PLAYER", "Player", 1, 1, 10, 10, 0, 25.f, 150.f, 0.319f, "player_sprite", true));
    CharacterManager::getInstance().addCharacter("ZIN", std::make_shared<Character>("ZIN", "Zin", 1, 1, 10, 10, 5, 25.f, 420.f, 0.066f, "zin_sprite", false));
    // ── Must be unlocked ──────────────────────────────────────────────────
    CharacterUnlockRegistry::getInstance().registerCharacter("OVI", std::make_shared<Character>("OVI", "Ovi", 40, 40, 10, 10, 0, 25.f, 690.f, 0.625f, "ovi_sprite", false));
    CharacterUnlockRegistry::getInstance().registerCharacter("JUNE", std::make_shared<Character>("JUNE", "June", 50, 50, 10, 10, 0, 25.f, 960.f, 0.625f, "june_sprite", false));
    CharacterUnlockRegistry::getInstance().registerCharacter("SULIMAN", std::make_shared<Character>("SULIMAN", "Suliman", 10, 10, 20, 10, 0, 25.f, 960.f, 0.590f, "sulliman_sprite", false));
    CharacterUnlockRegistry::getInstance().registerCharacter("LYRA", std::make_shared<Character>("LYRA", "Lyra", 35, 35, 14, 10, 3, 25.f, 960.f, 1.f, "lyra_sprite", false));
}

// Initialize NPCs for game
void InitializeCharacters::initNPCs()
{
    // NPCs are now loaded from Assets/Data/emotions.db via EmotionDatabase
}

// Stat Functions
void InitializeCharacters::initStats()
{
    auto& cm = CharacterManager::getInstance();
    auto& reg = CharacterUnlockRegistry::getInstance();

    // ── PLAYER ────────────────────────────────────────────────────────────
    cm.getCharacter("PLAYER")->getStats()->createStat("STRENGTH", "STR", "Damage",
        cm.getCharacter("PLAYER")->getDamage(), 2.0f);

    cm.getCharacter("PLAYER")->getStats()->createStat("VITALITY", "VIT", "Health",
        cm.getCharacter("PLAYER")->getHpMax(), 1.0f,
        [](float mod) {
            auto c = CharacterManager::getInstance().getCharacter("PLAYER");
            if (c) {
                c->getHp() += mod;
                c->updateText();
                if (c->getStats()) c->getStats()->setHp(c->getHp(), c->getHpMax());
            }
        });

    cm.getCharacter("PLAYER")->getStats()->createStat("DEFENSE", "DEF", "Defense",
        cm.getCharacter("PLAYER")->getDefense(), 1.0f);

    // ── ZIN ───────────────────────────────────────────────────────────────
    cm.getCharacter("ZIN")->getStats()->createStat("STRENGTH", "STR", "Damage",
        cm.getCharacter("ZIN")->getDamage(), 1.0f);

    cm.getCharacter("ZIN")->getStats()->createStat("VITALITY", "VIT", "Health",
        cm.getCharacter("ZIN")->getHpMax(), 1.2f,
        [](float mod) {
            auto c = CharacterManager::getInstance().getCharacter("ZIN");
            if (c) {
                c->getHp() += mod;
                c->updateText();
                if (c->getStats()) c->getStats()->setHp(c->getHp(), c->getHpMax());
            }
        });

    cm.getCharacter("ZIN")->getStats()->createStat("HEALING", "HEA", "Healing",
        cm.getCharacter("ZIN")->getHealing(), 2.0f);

    // ── OVI ───────────────────────────────────────────────────────────────
    reg.getPending("OVI")->getStats()->createStat("ENVIGORATE", "ENV", "Buff",
        reg.getPending("OVI")->getDamage(), 2.0f);

    reg.getPending("OVI")->getStats()->createStat("VITALITY", "VIT", "Health",
        reg.getPending("OVI")->getHpMax(), 1.2f,
        [](float mod) {
            auto c = CharacterManager::getInstance().getCharacter("OVI");
            if (c) {
                c->getHp() += mod;
                c->updateText();
                if (c->getStats()) c->getStats()->setHp(c->getHp(), c->getHpMax());
            }
        });

    reg.getPending("OVI")->getStats()->createStat("HEALING", "HEA", "Healing",
        reg.getPending("OVI")->getHealing(), 1.0f);

    // ── JUNE ──────────────────────────────────────────────────────────────
    reg.getPending("JUNE")->getStats()->createStat("STRENGTH", "STR", "Damage",
        reg.getPending("JUNE")->getDamage(), 0.7f);

    reg.getPending("JUNE")->getStats()->createStat("VITALITY", "VIT", "Health",
        reg.getPending("JUNE")->getHpMax(), 1.7f,
        [](float mod) {
            auto c = CharacterManager::getInstance().getCharacter("JUNE");
            if (c) {
                c->getHp() += mod;
                c->updateText();
                if (c->getStats()) c->getStats()->setHp(c->getHp(), c->getHpMax());
            }
        });

    reg.getPending("JUNE")->getStats()->createStat("DEFENSE", "DEF", "Defense",
        reg.getPending("JUNE")->getDefense(), 2.3f);

    // ── SULIMAN ───────────────────────────────────────────────────────────
    reg.getPending("SULIMAN")->getStats()->createStat("STRENGTH", "STR", "Damage",
        reg.getPending("SULIMAN")->getDamage(), 3.0f);

    reg.getPending("SULIMAN")->getStats()->createStat("VITALITY", "VIT", "Health",
        reg.getPending("SULIMAN")->getHpMax(), 0.2f,
        [](float mod) {
            auto c = CharacterManager::getInstance().getCharacter("SULIMAN");
            if (c) {
                c->getHp() += mod;
                c->updateText();
                if (c->getStats()) c->getStats()->setHp(c->getHp(), c->getHpMax());
            }
        });

    reg.getPending("SULIMAN")->getStats()->createStat("HEALING", "HEA", "Healing",
        reg.getPending("SULIMAN")->getHealing(), 2.0f);

    // ── LYRA ──────────────────────────────────────────────────────────────
    // LYRA has no VIT stat so no HP callback needed
    reg.getPending("LYRA")->getStats()->createStat("STRENGTH", "STR", "Damage",
        reg.getPending("LYRA")->getDamage(), 1.0f);

    reg.getPending("LYRA")->getStats()->createStat("DEBUFF", "DEB", "Debuff",
        reg.getPending("LYRA")->getHpMax(), 2.0f);

    reg.getPending("LYRA")->getStats()->createStat("HEALING", "HEA", "Healing",
        reg.getPending("LYRA")->getHealing(), 2.0f);
}

// Lore Functions
void InitializeCharacters::initLore()
{
    auto& cm = CharacterManager::getInstance();
    auto& reg = CharacterUnlockRegistry::getInstance();

    cm.getCharacter("PLAYER")->getStats()->setTipText(
        "A top tier knight reduced to a decaying reluctant adventurer. More years with a sword than years on the road."
    );

    cm.getCharacter("ZIN")->getStats()->setTipText(
        "A young mage from the capital that has practiced extensively. Zin keeps the party standing more than anyone cares to admit. Quick with a lightning bolt but she truly excels at mending those as they fall apart."
    );

    reg.getPending("OVI")->getStats()->setTipText(
        "Ovi has a way of making everyone fight just a little harder before the first blow even lands. Nobody's quite sure how it works, -- Ovi isn't telling."
    );

    reg.getPending("JUNE")->getStats()->setTipText(
        "A young warrior from the frontier who has seen too much of the world. June plants herself between danger and everyone else -- slow to strike, slower still to fall."
    );

    reg.getPending("SULIMAN")->getStats()->setTipText(
        "An old wizard from a land too far away. Suliman doesn't look like much, but he's got a way of making the most of every situation."
    );

    reg.getPending("LYRA")->getStats()->setTipText(
        "An ancient druid from the forest who can commune with nature itself. Lyra is a master of using the elements to force foes into submission."
    );
}

// Save / load support
void InitializeCharacters::restoreUnlockedCharacters()
{
    auto& flags = GameFlags::getInstance();
    auto& triggers = TriggerManager::getInstance();

    if (flags.has("character_unlocked_OVI"))     triggers.fire("unlock_ovi");
    if (flags.has("character_unlocked_JUNE"))    triggers.fire("unlock_june");
    if (flags.has("character_unlocked_SULIMAN")) triggers.fire("unlock_suliman");
    if (flags.has("character_unlocked_LYRA"))    triggers.fire("unlock_lyra");
}