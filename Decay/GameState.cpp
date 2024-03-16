#include "GameState.h"

//Constructors and Destructors
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");

    //Initialize Bonfire Assets
    this->initButtons();
    this->initRects();
}

GameState::~GameState()
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

void GameState::endState()
{
	std::cout << "Ending game state~" << "\n";
}

//Functions
void GameState::updateKeybinds()
{
	this->checkForQuit();
}

void GameState::update()
{
	this->updateMousePositions();
	this->updateKeybinds();
    this->updateButtons();
}

void GameState::render(sf::RenderTarget* target)
{
    this->renderButtons(target);
    this->renderRectangles(target);
}

//Asset Functions
void GameState::initButtons()
{
	this->buttons["EXPLORE"] = new Button(455, 755, 100, 25, 0.5f, this->font, "Explore",
		sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["EXIT"] = new Button(455, 780, 100, 25, 0.5f, this->font, "Exit",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void GameState::updateButtons()
{
    /*Updates all buttons in the State and handles their functionality*/
    for (auto& it : this->buttons) {
        it.second->update(getMousePosView());
    }

    //Start the game
    if (this->buttons["EXPLORE"]->isPressed()) {
        this->states->push(new CombatState(this->window, this->states));
        std::cout << "Starting Travel State!";
    }

    //Quit the game
    if (this->buttons["EXIT"]->isPressed()) {
        this->quit = true;
    }
}

void GameState::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

void GameState::initRects()
{
    this->rectangles["BORDER"] = new Rectangle(560, 5, 800, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
    this->rectangles["LEFTBOX"] = new Rectangle(0, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
    this->rectangles["RIGHTBOX"] = new Rectangle(1365, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
}

void GameState::renderRectangles(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}