#include "Move.h"

Move::Move(std::string key, std::string moveMessage, std::string tipMessage,
    std::string text, Operation op, int& a, int& b, int& coolDown)
    : operation(op), a(a), b(b), coolDown(coolDown)
{
    this->button = std::make_unique<Button>(350, 800, 100, 25, 0.1, text,
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->message = new Text(355, 835, 16, moveMessage, sf::Color::White, true);
    this->moveMessage = moveMessage;
    this->tipMessage = tipMessage;
    this->hidden = hidden;
    this->moveMessage = moveMessage;
    this->initRects();
}

Move::~Move() 
{
    delete this->message;
}

// Core Functions
void Move::render(sf::RenderTarget* target) {
    if (!this->hidden) {
        this->button->render(target);
        this->renderRects(target);
    }
    this->message->render(target);
}

void Move::update(const sf::Vector2f mousePos) {
    this->button->update(mousePos);
    if (this->button->isHovered()) {
        this->rectangles["TIPBOX"]->show();
    }
    else {
        this->rectangles["TIPBOX"]->hide();
    }

    if (this->button->isPressed()) {
        this->useMove();
    }

    if (this->coolDown > 0) {
        this->message->setString("Too tired to move this turn!");
        this->message->setShown();
        //this->coolDown--;
    }
}

void Move::useMove() 
{
    this->operation(a, b, this->coolDown);
    this->message->setShown();
    std::cout << "Operation applied: a = " << a << ", b = " << b << std::endl;
}

// Rectangle Functions
void Move::initRects() {
    this->rectangles["TIPBOX"] = std::make_unique<Rectangle>(this->tipMessage, sf::Color::White, 16, 1700, 100, 200,
        200, sf::Color::Transparent, sf::Color::White, 1.f, true);
}

void Move::renderRects(sf::RenderTarget* target) {
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}