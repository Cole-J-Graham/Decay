#pragma once
#include"Assets.h"
class Button
{
public:
	Button(std::string text, float x, float y);
	~Button();

	//Core Functions
	void draw(sf::RenderWindow& window);
	void setPos(float& x, float& y);
	void render(sf::RenderTarget* target);

private:
	sf::RectangleShape button;
	sf::Text buttonText;
	sf::Font font;

	//Asset Functions
	void loadButton();
};

