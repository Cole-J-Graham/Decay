#include "Rectangle.h"
//Constructors and Destructors
Rectangle::Rectangle(float x, float y, float width, float height, sf::Color color,
	sf::Color border_color, float border_thickness, bool hidden)
{
	//Rectangle
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(color);
	this->shape.setPosition(x, y);
	this->shape.setOutlineColor(border_color);
	this->shape.setOutlineThickness(border_thickness);
	this->hidden = hidden;
	this->clicked = false;
}

Rectangle::Rectangle(std::string text, sf::Color textColor, unsigned int textSize, 
	float x, float y, float width, float height, sf::Color color, sf::Color border_color, 
	float border_thickness, bool hidden)
{
	//Rectangle
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(color);
	this->shape.setPosition(x, y);
	this->shape.setOutlineColor(border_color);
	this->shape.setOutlineThickness(border_thickness);

	//Text
	font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
	this->text.setString(text);
	this->text.setFillColor(textColor);
	this->text.setFont(font);
	this->text.setCharacterSize(textSize);
	this->text.setPosition(x, y);
	this->hidden = hidden;
}

Rectangle::~Rectangle()
{

}

//Core Functions
void Rectangle::render(sf::RenderTarget* target)
{
	if (!this->hidden) {
		target->draw(this->shape);
		target->draw(this->text);
	}
}

void Rectangle::update(const sf::Vector2f mousePos)
{
	this->detectClick(mousePos);
}

//Detection Functions
void Rectangle::detectClick(const sf::Vector2f mousePos)
{
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->clicked = true;
		}
		else {
			this->clicked = false;
		}
	}
}