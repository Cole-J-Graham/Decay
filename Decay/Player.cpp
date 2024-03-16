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
    this->statsMod = new StatsModule();
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->initStats();
    this->initButtons();

}

Player::~Player()
{
    delete this->statsMod;
    //Delete Combat Buttons
    auto it = this->combatButtons.begin();
    for (it = this->combatButtons.begin(); it != this->combatButtons.end(); ++it) {
        delete it->second;
    }
}

//Core Functions
void Player::updatePlayer(const sf::Vector2f mousePos)
{
    this->updateButtons(mousePos);
}

void Player::renderPlayer(sf::RenderTarget* target)
{
    this->renderButtons(target);
    this->statsMod->render(target);
}

//Combat Functions
void Player::playerTurn()
{
    switch (this->player_frame) {
    case 0:
        for (auto& it : this->combatButtons) { it.second->show(); }
        break;
    case 1:
        for (auto& it : this->combatButtons) { it.second->hide(); }
        break;
    }
}

//Stat Functions
void Player::initStats()
{
    this->statsMod->createStat("STRENGTH", "STR");
    this->statsMod->createStat("AGILITY", "AGI");
}

//Button Functions
void Player::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->combatButtons) { it.second->update(mousePos); }
    this->statsMod->update(mousePos);
}

void Player::initButtons()
{
    this->combatButtons["STRIKE"] = new Button(350, 750, 100, 25, 0.5f, this->font, "STRIKE",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->combatButtons["CLOAK"] = new Button(350, 775, 100, 25, 0.5f, this->font, "CLOAK",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->combatButtons["GUARD"] = new Button(350, 800, 100, 25, 0.5f, this->font, "GUARD",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void Player::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->combatButtons) {
        it.second->render(target);
    }
}