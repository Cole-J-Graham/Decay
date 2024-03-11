#include "Player.h"
//Constructors and Deconstructors
Player::Player()
{
    //Player Variables
    this->hp = 100;
    this->hpMax = 100;
    this->damage = 10;
    this->defense = 10;

    //Initialization
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->initButtons();
}

Player::~Player()
{
    //Delete Combat Buttons
    auto it = this->combatButtons.begin();
    for (it = this->combatButtons.begin(); it != this->combatButtons.end(); ++it) {
        delete it->second;
    }
}

//Core Functions
void Player::update(const sf::Vector2f mousePos)
{
    this->updateButtons(mousePos);
}

void Player::render(sf::RenderTarget* target)
{
    this->renderButtons(target);
}

//Combat Functions
void Player::playerTurn()
{
    switch (this->playerFrame) {
    case 0:
        for (auto& it : this->combatButtons) { it.second->show(); }
        break;
    case 1:
        for (auto& it : this->combatButtons) { it.second->hide(); }
        break;
    }
}

void Player::strike(int* hostileHp)
{
    hostileHp -= this->damage * 2;
    this->combatMessage = "The player slashes at the opponent with all his might!";
}

void Player::cloak()
{
    this->combatMessage = "The player cloaks himself!";
}

void Player::guard()
{
    this->combatMessage = "The player prepares to protect Zin...";
}

//Button Functions
void Player::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->combatButtons) { it.second->update(mousePos); }

    if (this->combatButtons["STRIKE"]->isPressed()) {
        this->strike();
    }
    if (this->combatButtons["CLOAK"]->isPressed()) {
        this->cloak();
    }
    if (this->combatButtons["GUARD"]->isPressed()) {
        this->guard();
    }
}

void Player::initButtons()
{
    this->combatButtons["STRIKE"] = new Button(350, 750, 100, 25, this->font, "STRIKE",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->combatButtons["CLOAK"] = new Button(350, 775, 100, 25, this->font, "CLOAK",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->combatButtons["GUARD"] = new Button(350, 800, 100, 25, this->font, "GUARD",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void Player::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->combatButtons) {
        it.second->render(target);
    }
}