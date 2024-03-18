#include "Player.h"
//Constructors and Deconstructors
Player::Player()
{
    //Player Variables
    this->hp = 100;
    this->hpMax = 100;
    this->damage = 10;
    this->defense = 10;

    this->playerFrame = 0;

    //Initialization
    this->statsMod = new StatsModule();
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->initStats();
    this->initButtons();
    this->initText();
    this->initSprite();
}

Player::~Player()
{
    delete this->statsMod;
    //Delete Combat Buttons
    auto ic = this->combatButtons.begin();
    for (ic = this->combatButtons.begin(); ic != this->combatButtons.end(); ++ic) {
        delete ic->second;
    }
    //Delete Text
    auto it = this->text.begin();
    for (it = this->text.begin(); it != this->text.end(); ++it) {
        delete it->second;
    }
}

//Core Functions
void Player::updatePlayer(const sf::Vector2f mousePos)
{
    this->updateButtons(mousePos);
    this->updateText();
    this->playerTurn();
}

void Player::renderPlayer(sf::RenderTarget* target)
{
    this->renderButtons(target);
    this->statsMod->render(target);
    this->renderText(target);
    this->renderSprite(target);
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
        this->resetTurn();
        break;
    }
}

void Player::resetTurn()
{
    this->playerFrame = 0;
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

    for (auto& it : this->combatButtons) {
        if (it.second->isPressed()) {
            this->playerFrame++;
        }
    }
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

//Text Functions
void Player::initText()
{
    this->text["HP"] = new Text(25, 351, 16, "HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax),
        sf::Color::White, false);
}

void Player::renderText(sf::RenderTarget* target)
{
    for (auto& it : this->text) {
        it.second->render(target);
    }
}

void Player::updateText()
{
    this->text["HP"]->setString("HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax));
}

//Sprite Functions
void Player::initSprite()
{
    this->playerTexture.loadFromFile("Assets/Sprites/player.png");
    this->player.setTexture(this->playerTexture);
    this->player.setPosition(25, 150);
    this->player.setScale(0.319, 0.319);
}

void Player::renderSprite(sf::RenderTarget* target)
{
    target->draw(player);
}
