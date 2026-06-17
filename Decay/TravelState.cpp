#include "TravelState.h"
#include "MusicManager.h"
#include "PauseMenuState.h"
#include "SaveManager.h"

// Constructors and Destructors
TravelState::TravelState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->initRects();
    this->map = new MapComponent();

    if (SaveManager::getInstance().hasPendingMapState()) {
        SaveManager::getInstance().applyPendingMapState(this->map);
    }

    this->lastMapId = this->map->getCurrentMapId();
    this->combat = new CombatState(window, states);
    this->music = std::make_unique<MusicPlayer>();
    MusicManager_setPlayer(this->music.get());
    MusicManager::getInstance().preloadAll();
    MusicManager::getInstance().play(lastMapId);

    this->travelInput = std::make_unique<TravelInputComponent>();
    this->travelHud = std::make_unique<TravelHudComponent>();
    this->inventoryPanel = std::make_unique<InventoryPanel>();

    this->combatChanceMin = 1;
    this->combatChanceMax = 11;
    this->combatOdds = 1;

    srand(time(NULL));
}

TravelState::~TravelState()
{
    delete this->combat;
    delete this->map;

    for (auto& it : this->rectangles)
        delete it.second;
}

// Core Functions
void TravelState::checkForQuit()
{
    const bool escDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    if (!this->escWasDown && escDown)
        this->states->push(new PauseMenuState(this->window, this->states, this->music.get(), this->map));

    this->escWasDown = escDown;
}

void TravelState::update()
{
    this->checkForQuit();
    MusicManager::getInstance().update();
    this->updateMousePositions();

    // If a boss pre-fight event is playing, lock travel and wait for it to finish
    if (bossPreFightEventActive())
    {
        updateBossPreFightEvent(this->getMousePosView());
        return;
    }

    this->updateTravelInputVisibility();
    this->travelInput->update(this->getMousePosView());
    this->travelHud->update(this->getMousePosView());

    this->map->update(
        this->getMousePosView(),
        this->travelInput->rightArrowClicked(),
        this->travelInput->leftArrowClicked()
    );

    const std::string currentMap = this->map->getCurrentMapId();

    if (currentMap != this->lastMapId)
    {
        std::cout << "MAP CHANGED: " << this->lastMapId << " -> " << currentMap << "\n";
        MusicManager::getInstance().transition(currentMap);
        this->lastMapId = currentMap;
    }

    this->updateTravelInputVisibility();
    this->updateTravelActions();

    if (this->travelHud->partyPanelVisible())
        CharacterManager::getInstance().updatePartyPanel(this->getMousePosView());

    if (this->travelHud->statsPanelVisible())
        CharacterManager::getInstance().updateStatsPanel(this->getMousePosView());

    if (this->travelHud->inventoryPanelVisible())
        this->inventoryPanel->update();
}

void TravelState::render(sf::RenderTarget* target)
{
    this->map->render(target);
    this->renderRects(target);

    if (this->travelHud->partyPanelVisible())
        CharacterManager::getInstance().renderPartyPanel(target);

    if (this->travelHud->statsPanelVisible())
        CharacterManager::getInstance().renderStatsPanel(target);

    if (this->travelHud->inventoryPanelVisible())
        this->inventoryPanel->render(target);

    this->travelInput->render(target);
    this->travelHud->render(target);
    GameTriggers::renderNotification(target);

    // Render boss pre-fight event on top if active
    if (bossPreFightEventActive())
        renderBossPreFightEvent(target);
}

// ── Boss pre-fight event ──────────────────────────────────────────────────

bool TravelState::bossPreFightEventActive() const
{
    return bossPreFightEvent != nullptr;
}

void TravelState::updateBossPreFightEvent(const sf::Vector2f& mousePos)
{
    if (!bossPreFightEvent) return;

    bossPreFightEvent->update(mousePos);

    if (bossPreFightEvent->hasFinished())
    {
        bossPreFightEvent.reset();

        // Now start the actual boss combat
        if (pendingBoss)
        {
            if (this->combat->startBossCombat(
                pendingBoss->enemyId,
                pendingBoss->areaId,
                pendingBoss->defeatedFlag,
                pendingBoss->musicContext))
            {
                this->states->push(this->combat);
            }
            pendingBoss.reset();
        }
    }
}

void TravelState::renderBossPreFightEvent(sf::RenderTarget* target)
{
    if (bossPreFightEvent)
        bossPreFightEvent->render(target);
}

// Travel Functions
void TravelState::updateEventsFromMovement()
{
    const EncounterResult result = this->determineEncounterResult();
    this->handleEncounterResult(result);
}

void TravelState::updateTravelActions()
{
    if (this->travelInput->returnBonfireClicked()) {
        this->states->push(new BonfireState(this->window, this->states,
            this->map->getCurrentMapId()));
        return;
    }

    this->updateEventsFromMovement();
}

void TravelState::updateTravelInputVisibility()
{
    const bool eventActive = this->map->eventIsActive() || bossPreFightEventActive();

    const bool canMove =
        this->map->mapIsOpen() &&
        this->map->mapIsSelected() &&
        !eventActive;

    if (!canMove)
    {
        this->travelInput->hideMoveArrows();
    }
    else
    {
        // Show/hide each arrow independently based on frame position
        if (this->map->isAtFrameEnd())
            this->travelInput->hideRightArrow();
        else
            this->travelInput->showRightArrow();

        if (this->map->isAtFrameStart())
            this->travelInput->hideLeftArrow();
        else
            this->travelInput->showLeftArrow();
    }

    if (eventActive)
        this->map->hideMapButton();
    else
        this->map->showMapButton();
}

// Rectangle Functions
void TravelState::initRects()
{
    this->rectangles["BORDER"] = new Rectangle(560, 5, 800, 800,
        sf::Color::Transparent, sf::Color::White, 1.f, false);
    this->rectangles["LEFTBOX"] = new Rectangle(0, 5, 555, 800,
        sf::Color::Transparent, sf::Color::White, 1.f, false);
    this->rectangles["RIGHTBOX"] = new Rectangle(1365, 5, 555, 800,
        sf::Color::Transparent, sf::Color::White, 1.f, false);
}

void TravelState::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles)
        it.second->render(target);
}

bool TravelState::didPlayerMove() const
{
    return this->travelInput->rightArrowClicked() ||
        this->travelInput->leftArrowClicked();
}

EncounterResult TravelState::determineEncounterResult()
{
    if (!this->didPlayerMove())
        return EncounterResult::None;

    if (this->map->eventIsActive())
        return EncounterResult::None;

    // ── Boss check — highest priority after events ────────────────────
    const std::string currentMapId = this->map->getCurrentMapId();
    const BossEncounterDefinition* boss =
        BossEncounterDatabase::getInstance().getBoss(currentMapId);

    if (boss != nullptr && !GameFlags::getInstance().has(boss->defeatedFlag))
        return EncounterResult::Boss;

    // ── Normal event roll ─────────────────────────────────────────────
    if (this->map->rollEvent())
        return EncounterResult::Event;

    // ── Random combat roll ────────────────────────────────────────────
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> combatRange(
        this->combatChanceMin, this->combatChanceMax);

    if (this->combatOdds == combatRange(rng))
        return EncounterResult::Combat;

    return EncounterResult::None;
}

void TravelState::handleEncounterResult(EncounterResult result)
{
    switch (result)
    {
    case EncounterResult::None:
        break;

    case EncounterResult::Event:
        // rollEvent() already activated the event inside MapComponent.
        break;

    case EncounterResult::Combat:
        if (this->combat->startCombat(this->map->getCurrentAreaId()))
            this->states->push(this->combat);
        break;

    case EncounterResult::Boss:
    {
        const std::string currentMapId = this->map->getCurrentMapId();
        const BossEncounterDefinition* boss =
            BossEncounterDatabase::getInstance().getBoss(currentMapId);

        if (!boss) break;

        // Store the boss details for after the pre-fight event finishes
        pendingBoss = std::make_unique<PendingBoss>();
        pendingBoss->enemyId = boss->enemyId;
        pendingBoss->areaId = this->map->getCurrentAreaId();
        pendingBoss->defeatedFlag = boss->defeatedFlag;
        pendingBoss->musicContext = boss->musicContext;

        if (!boss->preFightEventPath.empty())
        {
            // Play the pre-fight cutscene — combat starts when it finishes
            bossPreFightEvent = std::make_unique<EventManager>(
                "",                          // areaName unused for direct file
                boss->preFightEventPath,
                true                         // directFile
            );
            std::cout << "TravelState: boss pre-fight event started: "
                << boss->preFightEventPath << "\n";
        }
        else
        {
            // No cutscene — go straight to combat
            if (this->combat->startBossCombat(
                pendingBoss->enemyId,
                pendingBoss->areaId,
                pendingBoss->defeatedFlag,
                pendingBoss->musicContext))
            {
                this->states->push(this->combat);
            }
            pendingBoss.reset();
        }
        break;
    }

    case EncounterResult::Treasure:
        break;

    case EncounterResult::Cutscene:
        break;
    }
}