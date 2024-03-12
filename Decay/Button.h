#pragma once
#include "Asset.h"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
public:
	//Constructors and Destructors
	Button(float x, float y, float width, float height, sf::Font font,
	std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
		bool hidden);
	~Button();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Accessors
	const bool isPressed() const;
	
	//Modifiers
	void show() { this->hidden = false; };
	void hide() { this->hidden = true; };

private:
	//Core Booleans
	short unsigned buttonState;
	bool hidden;

	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
};
