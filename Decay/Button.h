#pragma once
#include<iostream>

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
public:
	//Constructors and Destructors
	Button(float x, float y, float width, float height, sf::Font font,
	std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Accessors
	const bool isPressed() const;

private:
	//Core Booleans
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
};

