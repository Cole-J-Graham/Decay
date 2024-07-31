#include "TravelState.h"
//Constructors and Destructors
TravelState::TravelState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    //Initialization
    this->initRects();
    this->map = new MapComponent();
    this->combat = new CombatState(window, states);
    this->music = std::make_unique<MusicPlayer>();
    this->userInput = std::make_unique<UserInputComponent>();

    this->combatChanceMin = 1;
    this->combatChanceMax = 11;
    this->combatOdds = 1;

    srand(time(NULL));
}

TravelState::~TravelState()
{
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
    this->music->readFile("Assets/Music/music_list.txt");
    this->music->update(this->getMousePosView());
    this->updateMousePositions();
    this->updateEventsFromMovement();
    this->map->update(this->getMousePosView());
    this->userInput->update(this->getMousePosView());
    CharacterManager::getInstance().updateAll(this->getMousePosView());
    CharacterManager::getInstance().updateStats(this->getMousePosView());
}

void TravelState::render(sf::RenderTarget* target)
{
    this->map->render(target);
    this->renderRects(target);
    CharacterManager::getInstance().renderStats(target);
    this->music->render(target);
}

//Travel Functions
void TravelState::updateEventsFromMovement()
{
    //Push in combat based off random chance of each movement
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> combatRange(this->combatChanceMin, this->combatChanceMax);
    if (this->userInput->rightArrowClicked() || this->userInput->leftArrowClicked()) {
        if (this->combatOdds == combatRange(rng)) {
            this->states->push(this->combat);
        }
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