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
void GameState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeybinds(dt);
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
	this->buttons["EXPLORE"] = new Button(100, 100, 100, 25, this->font, "Explore",
		sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70));
    this->buttons["EXIT"] = new Button(100, 125, 100, 25, this->font, "Exit",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70));
}

void GameState::updateButtons()
{
    /*Updates all buttons in the State and handles their functionality*/
    for (auto& it : this->buttons) {
        it.second->update(getMousePosView());
    }

    //Start the game
    if (this->buttons["EXPLORE"]->isPressed()) {
        //this->states->push(new GameState(this->window, this->states));
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
    this->rectangles["BORDER"] = new Rectangle(690, 0, 800, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
}

void GameState::renderRectangles(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}