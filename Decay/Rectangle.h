#pragma once
#include "Asset.h"

class Rectangle
{
public:
	//Constructors and Destructors
	Rectangle(float x, float y, float width, float height, sf::Color color,
		sf::Color border_color, float z);
	~Rectangle();

	//Core Functions
	void render(sf::RenderTarget* target = nullptr);

private:
	sf::RectangleShape shape;
};

