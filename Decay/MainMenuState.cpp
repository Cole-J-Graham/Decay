#include "MainMenuState.h"
//Constructors and Destructors
MainMenuState::MainMenuState(sf::RenderWindow* window)
    : State(window)
{
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->setAssets();
    this->setAssetsPos();

    //Initialize Main Menu Buttons
    this->gamestate_btn = new Button(100, 100, 150, 50, this->font, "Start", 
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70));
}

MainMenuState::~MainMenuState()
{
    delete this->gamestate_btn;
}

//State Functions
void MainMenuState::updateKeybinds(const float& dt)
{
    
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateKeybinds(dt);

    this->gamestate_btn->update(getMousePosView());
}

void MainMenuState::render(sf::RenderTarget* target)
{
    this->gamestate_btn->render(target);
}

//Asset Functions
void MainMenuState::setAssets()
{
    
}

void MainMenuState::setAssetsPos()
{
    
}
