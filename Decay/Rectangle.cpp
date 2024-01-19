#include "Rectangle.h"
//Constructors and Destructors
Rectangle::Rectangle(float x, float y, float width, float height, sf::Color color,
	sf::Color border_color, float border_thickness)
{
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(color);
	this->shape.setPosition(x, y);
	this->shape.setOutlineColor(border_color);
	this->shape.setOutlineThickness(border_thickness);
}

Rectangle::~Rectangle()
{

}

//Core Functions
void Rectangle::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}