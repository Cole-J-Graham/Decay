#pragma once

#include "State.h"
#include "CombatComponent.h"
#include "CombatConsole.h"
#include "RewardSystem.h"

class CombatState : public State, public CombatComponent
{
public:
    CombatState(sf::RenderWindow* window, std::stack<State*>* states);
    ~CombatState() = default;

    // Core
    void combatLoop(const sf::Vector2f mousePos);
    bool detectEnemyDeath();
    bool detectPartyWipe();
    void resetCombat();

    bool startCombat(const std::string& areaId);
    bool startBossCombat(const std::string& enemyId,
        const std::string& areaId,
        const std::string& defeatedFlag,
        const std::string& musicContext = "");

    // State interface
    void updateKeybinds();
    void update();
    void render(sf::RenderTarget* target = nullptr);

    void resetAllCharacterTurns();

private:
    void handleCharacterTurn(int partyIndex, const sf::Vector2f mousePos);
    void handleEnemyTurn(const sf::Vector2f mousePos);
    void resetAllCharactersForNewCombat();

    void beginCombatEnd();
    void finishCombatEnd();

    void beginDefeat();
    void handleReturnToBonfire();
    void handleLoadLastSave();

    void applyCombatMusic(const std::string& areaId,
        const std::string& overrideContext = "");

    CombatConsole console;

    bool stateEnd = false;
    bool defeatState = false;
    int  combatFrame = 0;

    std::string pendingDefeatedFlag;
    std::string currentAreaIdForBonfire;
};