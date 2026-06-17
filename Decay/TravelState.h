#pragma once

// States
#include "State.h"
#include "EncounterResult.h"
#include "MapComponent.h"
#include "MusicPlayer.h"
#include "CombatState.h"
#include "BonfireState.h"
#include "TravelInputComponent.h"
#include "TravelHudComponent.h"
#include "InventoryPanel.h"
#include "EventManager.h"

// Events
#include "TriggerManager.h"
#include "GameFlags.h"
#include "GameTriggers.h"
#include "BossEncounterDatabase.h"

// Managers
#include "CharacterManager.h"

class TravelState : public State
{
public:
    // Constructors and Destructors
    TravelState(sf::RenderWindow* window, std::stack<State*>* states);
    ~TravelState();

    // Core Functions
    void update();
    void render(sf::RenderTarget* target = nullptr);

    // Overrides base checkForQuit to push PauseMenuState with the music pointer
    void checkForQuit();

    // Travel Functions
    void updateEventsFromMovement();
    void updateTravelActions();
    void updateTravelInputVisibility();

    // Rectangle Functions
    void initRects();
    void renderRects(sf::RenderTarget* target);

    void checkFPS(sf::Clock& clock, sf::Clock& fpsClock, int& frameCount)
    {
        sf::Time elapsed = clock.restart();
        frameCount++;

        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            float fps = frameCount / fpsClock.restart().asSeconds();
            std::cout << "FPS: " << fps << std::endl;
            frameCount = 0;
        }
    }

    sf::Clock clock;
    sf::Clock fpsClock;
    int frameCount = 0;

private:
    bool didPlayerMove() const;
    EncounterResult determineEncounterResult();
    void handleEncounterResult(EncounterResult result);

    // Boss pre-fight event — active while a pre-fight cutscene plays
    void updateBossPreFightEvent(const sf::Vector2f& mousePos);
    void renderBossPreFightEvent(sf::RenderTarget* target);
    bool bossPreFightEventActive() const;

    bool escWasDown = false;

private:
    int combatChanceMin;
    int combatChanceMax;
    float combatOdds;
    std::string lastMapId;

    // Pending boss encounter — held while the pre-fight event plays,
    // then consumed to start combat when the event finishes.
    struct PendingBoss
    {
        std::string enemyId;
        std::string areaId;
        std::string defeatedFlag;
        std::string musicContext;
    };
    std::unique_ptr<PendingBoss>  pendingBoss;
    std::unique_ptr<EventManager> bossPreFightEvent;

    std::unique_ptr<TravelHudComponent>   travelHud;
    std::unique_ptr<TravelInputComponent> travelInput;
    std::unique_ptr<InventoryPanel>       inventoryPanel;
    std::vector<sf::Texture>              mapData;
    std::map<std::string, Rectangle*>     rectangles;

    CombatState* combat;
    MapComponent* map;

    std::unique_ptr<MusicPlayer> music;
};