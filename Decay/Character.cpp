#include "Character.h"

// Constructors and Deconstructors
Character::Character(std::string characterName, float hp, float hpMax, float damage, float defense,
    float x, float y, float scale, std::string characterTexture, bool turnActive)
{
    // Player Variables
    this->hp = hp;
    this->hpMax = hpMax;
    this->damage = damage;
    this->defense = defense;
    this->characterFrame = 0;
    this->coolDown = 1;
    this->x = x;
    this->y = y;

    // Asset Variables
    this->characterTexture.loadFromFile(characterTexture);
    this->character.setTexture(this->characterTexture);
    this->character.setPosition(x, y);
    this->character.setScale(scale, scale);
    this->characterName = characterName;
    this->border = std::make_unique<Rectangle>(this->x, this->y, 200, 200, sf::Color::Transparent, sf::Color::White, 1.f, false);

    this->turnActive = turnActive;

    // Initialization
    this->initText();
    this->initButtons();
}

Character::~Character() 
{
    //Delete Move Buttons
    auto ib = this->moveButtons.begin();
    for (ib = this->moveButtons.begin(); ib != this->moveButtons.end(); ++ib) {
        delete ib->second;
    }
}

// Core Functions
void Character::update(const sf::Vector2f mousePos) {
    this->updateText();
    this->updateButtons(mousePos);
}

void Character::render(sf::RenderTarget* target) {
    // In combat
    target->draw(this->character);
    this->border->render(target);
    this->renderButtons(target);
    this->renderText(target);
    // Active Turn
    if (this->turnActive && this->coolDown <= 0) {
        this->renderMoveButtons(target);
    }
}

void Character::characterTurn(int& combatFrame, const sf::Vector2f mousePos) {
    this->update(mousePos);
    switch (this->characterFrame) {
    case 0:
        if (this->coolDown <= 0) {
            this->turnActive = true;
            for (auto& it : this->moveButtons) { it.second->show(); }
        }
        else if (this->coolDown > 0) {
            this->characterFrame = 1;
        }
        break;
    case 1:
        for (auto& it : this->moveButtons) { it.second->hide(); }
        this->endTurn(combatFrame);
        break;
    }
}

void Character::resetTurn() {
    this->characterFrame = 0;
}

void Character::endTurn(int& combatFrame) {
    this->buttons["ENDTURN"]->show();
    if (this->buttons["ENDTURN"]->isPressed()) {
        this->resetTurn();
        combatFrame++;
        this->buttons["ENDTURN"]->hide();
        this->coolDown--;
        for (auto& it : this->moveButtons) { it.second->hideAttackMessage(); }
    }
}

// Button Functions
void Character::updateButtons(const sf::Vector2f mousePos) {
    for (auto& it : this->moveButtons) {
        if(!it.second->isHidden()) { it.second->update(mousePos); }
    }
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }

    for (auto& it : this->moveButtons) {
        if (it.second->isPressed()) {
            this->characterFrame++;
        }
    }
}

void Character::initButtons() {
    this->buttons["ENDTURN"] = std::make_unique<Button>(450, 800, 150, 25, 0.5f, "End " + this->characterName + "'s Turn",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), true);
}

void Character::renderButtons(sf::RenderTarget* target) {
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

// Move Functions
void Character::createMove(std::string key, std::string moveMessage, std::string tipMessage, 
    std::string text, Move::Operation op, float& a, float& b) {
    this->moveButtons[key] = new Move(key, moveMessage, tipMessage, text, op, a, b, this->coolDown);
}

void Character::renderMoveButtons(sf::RenderTarget* target) {
    int y = 825;
    for (auto& it : this->moveButtons) {
        it.second->render(target);
        it.second->setPosition(350, y -= 25);
    }
}

// Text Functions
void Character::initText() {
    this->text["HP"] = std::make_unique<Text>(this->x, this->y + 200, 16, "HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax),
        sf::Color::White, false);
}

void Character::renderText(sf::RenderTarget* target) {
    for (auto& it : this->text) {
        it.second->render(target);
    }
}

void Character::updateText() {
    this->text["HP"]->setString("HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax));
}