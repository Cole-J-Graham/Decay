#pragma once
#include "Asset.h"

class Rectangle
{
public:
	//Constructors and Destructors
	Rectangle(float x, float y, float width, float height, sf::Color color,
		sf::Color border_color, float border_thickness, bool hidden);
	Rectangle(std::string text, sf::Color textColor, unsigned int textSize,
		float x, float y, float width, float height, sf::Color color, sf::Color border_color,
		float border_thickness, bool hidden);
	~Rectangle();

	//Core Functions
	void render(sf::RenderTarget* target = nullptr);
	void update(const sf::Vector2f mousePos);

	//Detection Functions
	void detectClick(const sf::Vector2f mousePos);

	//Modifiers
	void show() { this->hidden = false; };
	void hide() { this->hidden = true; };

	//Getters
	bool& isClicked() { return this->clicked; }

private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;
	bool clicked;
	bool hidden;
};

