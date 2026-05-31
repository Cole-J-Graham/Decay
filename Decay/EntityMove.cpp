#include "EntityMove.h"

#include <iostream>

// Constructors and Destructors
EntityMove::EntityMove(const std::string& moveMessage, Operation op,
    std::string sfxId)
    : operation(op), sfxId(sfxId)
{
    this->hidden = true;
    this->moveMessage = moveMessage;
    this->message = std::make_unique<Text>(355, 835, 16, moveMessage, sf::Color::White, true);
}

// Core Functions
void EntityMove::render(sf::RenderTarget* target)
{
    if (!this->hidden) {
        this->message->render(target);
    }
}

void EntityMove::update(const sf::Vector2f mousePos)
{}

void EntityMove::useMove()
{
    if (this->operation) {
        this->operation();
    }

    if (!this->sfxId.empty()) {
        SfxManager::getInstance().play(this->sfxId);
    }

    this->show();

    std::cout << "Entity move used: " << this->moveMessage << std::endl;
}

void EntityMove::renderMoveMessage(sf::RenderTarget* target)
{
    if (!this->hidden) {
        this->message->render(target);
    }
}

// Setters
void EntityMove::show()
{
    this->hidden = false;
    this->message->setShown();
}

void EntityMove::hide()
{
    this->hidden = true;
    this->message->setHidden();
}