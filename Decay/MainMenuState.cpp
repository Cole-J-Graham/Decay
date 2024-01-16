#include "MainMenuState.h"
//Constructors and Destructors
MainMenuState::MainMenuState(sf::RenderWindow* window)
    : State(window)
{
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->setAssets();
    this->setAssetsPos();
}

MainMenuState::~MainMenuState()
{

}

//State Functions
void MainMenuState::updateKeybinds(const float& dt)
{
    
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateKeybinds(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
    for (int i = 0; i < buttons.size(); i++) {
        target->draw(buttons[i]);
        target->draw(buttonsText[i]);
    }
}

//Asset Functions
void MainMenuState::setAssets()
{
    //Load All Buttons
    for (int i = 0; i < buttons.size(); i++) {
        buttonsText[i].setFont(font);
        buttonsText[i].setCharacterSize(18);
        buttonsText[i].setFillColor(sf::Color::Black);
        buttons[i].setSize(sf::Vector2f(150.0f, 25.0f));
        buttons[i].setOutlineColor(sf::Color::White);
        buttons[i].setOutlineThickness(1.0f);
    }
    //Set Button Text Strings
    buttonsText[0].setString("Start");
    buttonsText[1].setString("Load");
    buttonsText[2].setString("Quit");
}

void MainMenuState::setAssetsPos()
{
    //Set buttons and button text positions
    buttons[0].setPosition(10.f, 100.f);
    buttons[1].setPosition(10.f, 125.f);
    buttons[2].setPosition(10.f, 150.f);
    buttonsText[0].setPosition(10.f, 100.f);
    buttonsText[1].setPosition(10.f, 125.f);
    buttonsText[2].setPosition(10.f, 150.f);
}
