#include "Move.h"
Move::Move(std::string key, std::string tipMessage, float width, float height,
	float clicktime, sf::Font font, std::string text, sf::Color idleColor, sf::Color hoverColor,
	sf::Color activeColor, bool hidden)
{
	this->button = std::make_unique<Button>(350, 800, width, height, clicktime, font, text, idleColor,
		hoverColor, activeColor, hidden);
    this->tipMessage = tipMessage;
    this->hidden = hidden;
    this->initRects();
}

Move::~Move()
{
    
}

//Core Functions
void Move::render(sf::RenderTarget* target)
{
    if (!this->hidden) {
        this->button->render(target);
        this->renderRects(target);
    }
}

void Move::update(const sf::Vector2f mousePos)
{
	this->button->update(mousePos);
    if (this->button->isHovered()) {
        this->rectangles["TIPBOX"]->show();
    }
    else {
        this->rectangles["TIPBOX"]->hide();
    }
}

const bool Move::isPressed() 
{ 
	return this->button->isPressed();
}

//Rectangle Functions
void Move::initRects()
{
    this->rectangles["TIPBOX"] = std::make_unique<Rectangle>(this->tipMessage, sf::Color::White, 16, 1700, 100, 200, 
        200, sf::Color::Transparent, sf::Color::White, 1.f, true);
}

void Move::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}