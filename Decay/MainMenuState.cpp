#include "MainMenuState.h"
//Constructors and Destructors
MainMenuState::MainMenuState(sf::RenderWindow* window)
    : State(window)
{
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->setAssets();
    this->setAssetsPos();

    //Initialize Main Menu
    this->initButtons();
}

MainMenuState::~MainMenuState()
{

    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

//State Functions
void MainMenuState::updateKeybinds(const float& dt)
{
    this->checkForQuit();
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateKeybinds(dt);
    this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
    this->renderButtons(target);
}

//Asset Functions
void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE"] = new Button(100, 100, 100, 25, this->font, "Start",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70));
    this->buttons["EXIT_STATE"] = new Button(100, 125, 100, 25, this->font, "Quit",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70));
}

void MainMenuState::updateButtons()
{
    /*Updates all buttons in the State and handles their functionality*/
    for (auto &it : this->buttons) {
        it.second->update(getMousePosView());
    }

    //Quit the game
    if (this->buttons["EXIT_STATE"]->isPressed()) {
        this->quit = true;
    }
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

void MainMenuState::setAssets()
{
    
}

void MainMenuState::setAssetsPos()
{
    
}
