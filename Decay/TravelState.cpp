#include "TravelState.h"
//Constructors and Destructors
TravelState::TravelState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");

    //Asset Functions
    this->initRects();
    this->initButtons();
}

TravelState::~TravelState()
{
    //Deconstruct Buttons
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }

    //Deconstruct Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
}

//State Functions
void TravelState::updateKeybinds(const float& dt)
{

}

void TravelState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateButtons();
}

void TravelState::render(sf::RenderTarget* target)
{
    this->renderRects(target);
    this->renderButtons(target);
}

//Asset Functions
void TravelState::initButtons()
{
    this->buttons["RETURN_BONFIRE"] = new Button(415, 10, 135, 25, this->font, "Return->Bonfire",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70));
    this->buttons["BUTTON_RIGHT"] = new Button(1335, 780, 20, 20, this->font, "->",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70));
    this->buttons["BUTTON_LEFT"] = new Button(565, 780, 20, 20, this->font, "<-",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70));
}

void TravelState::updateButtons()
{
    /*Updates all buttons in the State and handles their functionality*/
    for (auto& it : this->buttons) {
        it.second->update(getMousePosView());
    }

    //Travel Right
    if (this->buttons["BUTTON_RIGHT"]->isPressed()) {
        std::cout << "Moved Right!";
    }
    //Travel Left
    if (this->buttons["BUTTON_LEFT"]->isPressed()) {
        std::cout << "Moved Left!";
    }
    //Return to bonfire
    if (this->buttons["RETURN_BONFIRE"]->isPressed()) {
        this->quit = true;
    }
}

void TravelState::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

void TravelState::initRects()
{
    this->rectangles["BORDER"] = new Rectangle(560, 5, 800, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
    this->rectangles["LEFTBOX"] = new Rectangle(0, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
    this->rectangles["RIGHTBOX"] = new Rectangle(1365, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
}

void TravelState::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}