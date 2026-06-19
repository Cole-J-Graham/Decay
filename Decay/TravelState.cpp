#include "TravelState.h"
#include "MusicManager.h"
#include "MusicPlayer.h"
#include "PauseMenuState.h"
#include "SaveManager.h"

// ── Constructors ──────────────────────────────────────────────────────────

TravelState::TravelState(sf::RenderWindow* window, std::stack<State*>* states,
    MusicPlayer* musicPlayer)
    : State(window, states)
    , music(musicPlayer)
{
    this->initRects();
    this->map = new MapComponent();

    if (SaveManager::getInstance().hasPendingMapState())
        SaveManager::getInstance().applyPendingMapState(this->map);

    this->lastMapId = this->map->getCurrentMapId();
    this->combat = new CombatState(window, states);

    // MusicPlayer is owned by Game and wired into MusicManager once at boot —
    // just start this area's playlist on the singleton.
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

// ── Core ──────────────────────────────────────────────────────────────────

void TravelState::checkForQuit()
{
    const bool escDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    if (!this->escWasDown && escDown)
        this->states->push(new PauseMenuState(this->window, this->states, this->music, this->map));

    this->escWasDown = escDown;
}

void TravelState::update()
{
    this->checkForQuit();
    MusicManager::getInstance().update();
    this->updateMousePositions();

    // Feed current area name to the HUD every frame (cheap string compare inside)
    this->travelHud->setAreaName(this->map->getCurrentMapId());

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

// ── Travel ────────────────────────────────────────────────────────────────

void TravelState::updateEventsFromMovement()
{
    const EncounterResult result = this->determineEncounterResult();
    this->handleEncounterResult(result);
}

void TravelState::updateTravelActions()
{
    if (this->travelInput->returnBonfireClicked())
    {
        this->states->push(new BonfireState(this->window, this->states,
            this->map->getCurrentMapId(), this->music));
        return;
    }

    this->updateEventsFromMovement();
}

void TravelState::updateTravelInputVisibility()
{
    const bool eventActive = this->map->eventIsActive() || bossPreFightEventActive();

    const bool canMove =
        this->map->mapIsSelected() &&
        !eventActive;

    // Arrow visibility — independent per side
    if (!canMove)
    {
        this->travelInput->hideMoveArrows();
    }
    else
    {
        if (this->map->isAtFrameEnd())
            this->travelInput->hideRightArrow();
        else
            this->travelInput->showRightArrow();

        if (this->map->isAtFrameStart())
            this->travelInput->hideLeftArrow();
        else
            this->travelInput->showLeftArrow();
    }
}

// ── Rectangles ────────────────────────────────────────────────────────────

void TravelState::initRects()
{
    // Map panel border — centre column
    this->rectangles["BORDER"] = new Rectangle(
        560, 5, 800, 800,
        sf::Color::Transparent, sf::Color(255, 255, 255, 50), 1.f, false);

    // Left column — map viewer lives here, height matches center panel
    this->rectangles["LEFTBOX"] = new Rectangle(
        5, 5, 550, 800,
        sf::Color::Transparent, sf::Color(255, 255, 255, 50), 1.f, false);

    // Left column header divider
    this->rectangles["LEFT_HEADER_DIV"] = new Rectangle(
        5, 36, 550, 1,
        sf::Color(255, 255, 255, 25), sf::Color::Transparent, 0.f, false);

    // Right column — panels open here, same height
    this->rectangles["RIGHTBOX"] = new Rectangle(
        1365, 5, 550, 800,
        sf::Color::Transparent, sf::Color(255, 255, 255, 50), 1.f, false);

    // Right column header divider
    this->rectangles["RIGHT_HEADER_DIV"] = new Rectangle(
        1365, 36, 550, 1,
        sf::Color(255, 255, 255, 25), sf::Color::Transparent, 0.f, false);

    // Bottom bar — spans full width, docked inside the bottom of the
    // three columns (ends flush with their bottom edge at y=805) so it
    // no longer collides with the dialogue box starting at y=806.
    this->rectangles["BOTTOM_BAR"] = new Rectangle(
        0, 770, 1920, 35,
        sf::Color(10, 10, 10, 160), sf::Color(255, 255, 255, 30), 1.f, false);
}

void TravelState::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles)
        it.second->render(target);
}

// ── Encounters ────────────────────────────────────────────────────────────

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

    const std::string currentMapId = this->map->getCurrentMapId();
    const BossEncounterDefinition* boss =
        BossEncounterDatabase::getInstance().getBoss(currentMapId);

    if (boss != nullptr && !GameFlags::getInstance().has(boss->defeatedFlag))
        return EncounterResult::Boss;

    if (this->map->rollEvent())
        return EncounterResult::Event;

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

        pendingBoss = std::make_unique<PendingBoss>();
        pendingBoss->enemyId = boss->enemyId;
        pendingBoss->areaId = this->map->getCurrentAreaId();
        pendingBoss->defeatedFlag = boss->defeatedFlag;
        pendingBoss->musicContext = boss->musicContext;

        if (!boss->preFightEventPath.empty())
        {
            bossPreFightEvent = std::make_unique<EventManager>(
                "", boss->preFightEventPath, true);
            std::cout << "TravelState: boss pre-fight event started: "
                << boss->preFightEventPath << "\n";
        }
        else
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
        break;
    }

    case EncounterResult::Treasure:
        break;

    case EncounterResult::Cutscene:
        break;
    }
}