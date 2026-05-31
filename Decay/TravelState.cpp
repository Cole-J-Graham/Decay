#include "TravelState.h"
//Constructors and Destructors
TravelState::TravelState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    //Initialization
    this->initRects();
    this->map = new MapComponent();
    this->combat = new CombatState(window, states);
    this->music = std::make_unique<MusicPlayer>("Assets/Music/music_list.txt");
    this->travelInput = std::make_unique<TravelInputComponent>();

    this->combatChanceMin = 1;
    this->combatChanceMax = 11;
    this->combatOdds = 1;

    srand(time(NULL));
}

TravelState::~TravelState()
{
    delete this->combat;
    delete this->map;
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
}

//Core Functions
void TravelState::update()
{
    this->music->update(this->getMousePosView());
    this->updateMousePositions();

    this->updateTravelInputVisibility();
    this->travelInput->update(this->getMousePosView());

    this->map->update(
        this->getMousePosView(),
        this->travelInput->rightArrowClicked(),
        this->travelInput->leftArrowClicked()
    );

    this->updateTravelInputVisibility();
    this->updateTravelActions();

    CharacterManager::getInstance().updateAll(this->getMousePosView());
}

void TravelState::render(sf::RenderTarget* target)
{
    CharacterManager::getInstance().renderAllStats(target);
    this->map->render(target);
    this->renderRects(target);
    this->music->render(target);
    this->travelInput->render(target);
}

//Travel Functions
void TravelState::updateEventsFromMovement()
{
    const EncounterResult result = this->determineEncounterResult();
    this->handleEncounterResult(result);
}

void TravelState::updateTravelActions()
{
    if (this->travelInput->returnBonfireClicked()) {
        this->states->push(new BonfireState(this->window, this->states));
        return;
    }

    this->updateEventsFromMovement();
}

void TravelState::updateTravelInputVisibility()
{
    const bool eventActive = this->map->eventIsActive();

    const bool canMove =
        this->map->mapIsOpen() &&
        this->map->mapIsSelected() &&
        !eventActive;

    if (canMove) {
        this->travelInput->showMoveArrows();
    }
    else {
        this->travelInput->hideMoveArrows();
    }

    if (eventActive) {
        this->map->hideMapButton();
    }
    else {
        this->map->showMapButton();
    }
}

//Rectangle Functions
void TravelState::initRects()
{
    this->rectangles["BORDER"] = new Rectangle(560, 5, 800, 800, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
    this->rectangles["LEFTBOX"] = new Rectangle(0, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
    this->rectangles["RIGHTBOX"] = new Rectangle(1365, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
}

void TravelState::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}

bool TravelState::didPlayerMove() const
{
    return this->travelInput->rightArrowClicked() || this->travelInput->leftArrowClicked();
}

EncounterResult TravelState::determineEncounterResult()
{
    if (!this->didPlayerMove()) {
        return EncounterResult::None;
    }

    // If an event is already active, do not trigger anything else.
    if (this->map->eventIsActive()) {
        return EncounterResult::None;
    }

    // Events get priority.
    if (this->map->rollEvent()) {
        return EncounterResult::Event;
    }

    // Future expansion point:
    // if (treasure roll succeeds) return EncounterResult::Treasure;
    // if (boss condition succeeds) return EncounterResult::Boss;
    // if (cutscene condition succeeds) return EncounterResult::Cutscene;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> combatRange(
        this->combatChanceMin,
        this->combatChanceMax
    );

    if (this->combatOdds == combatRange(rng)) {
        return EncounterResult::Combat;
    }

    return EncounterResult::None;
}

void TravelState::handleEncounterResult(EncounterResult result)
{
    switch (result) {
    case EncounterResult::None:
        break;

    case EncounterResult::Event:
        // Nothing else needed here.
        // rollEvent() already activated the event.
        break;

    case EncounterResult::Combat:
        if (this->combat->startCombat(this->map->getCurrentAreaId())) {
            this->states->push(this->combat);
        }
        break;

    case EncounterResult::Treasure:
        // Future
        break;

    case EncounterResult::Boss:
        // Future
        break;

    case EncounterResult::Cutscene:
        // Future
        break;
    }
}