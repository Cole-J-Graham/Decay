#pragma once
#include "Asset.h"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
public:
	//Constructors and Destructors
	Button(float x, float y, float width, float height, float clicktime,
	std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
		bool hidden);
	Button(sf::Vector2f pos, float width, float height, float clicktime,
		std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
		bool hidden);

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Accessors
	const bool isPressed() const;
	const bool isHovered() const;
	//Modifiers
	void setPosition(float x, float y) { this->shape.setPosition(x, y); this->text.setPosition(x, y); };
	void setText(std::string& text) { this->text.setString(text); }
	void show() { this->hidden = false; };
	void hide() { this->hidden = true; };
	void deActivate() { this->clickBlocked = true; this->shape.setFillColor(this->activeColor); }
	void reActivate() { this->clickBlocked = false; this->shape.setFillColor(this->idleColor); }

private:
	//Core Booleans
	short unsigned buttonState;

	bool hidden;
	bool clickBlocked;

	sf::Clock clickBlockTimer;
	float clickBlockDuration;

	sf::Clock clock;
	sf::Time elapsed;

	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
};

