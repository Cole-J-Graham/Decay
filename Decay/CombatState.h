#pragma once

// States
#include "State.h"

// Modules
#include "CombatComponent.h"
#include "UiPanel.h"

class CombatState : public State, public CombatComponent
{
public:
    // Constructors and Destructors
    CombatState(sf::RenderWindow* window, std::stack<State*>* states);
    ~CombatState() = default;

    // Core Functions
    void combatLoop(const sf::Vector2f mousePos);
    bool detectEnemyDeath();
    void resetCombat();
    bool startCombat(const std::string& areaId);

    // State Functions
    void updateKeybinds();
    void update();
    void render(sf::RenderTarget* target = nullptr);

    // Character Functions
    void resetAllCharacterTurns();

private:
    // UI Functions
    void initUi();

    // Combat Turn Helpers
    void handleCharacterTurn(int partyIndex, const sf::Vector2f mousePos);
    void handleEnemyTurn(const sf::Vector2f mousePos);

    // Combat Ending Helpers
    void beginCombatEnd();
    void finishCombatEnd();

    // Combat Console Helpers
    void enableCombatConsoleContinue();
    void disableCombatConsoleContinue();
    bool combatConsoleClicked();

private:
    bool stateEnd = false;
    bool combatConsoleActive = false;

    int combatFrame = 0;

    UiPanel ui;
};