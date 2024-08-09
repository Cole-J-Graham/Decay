#include "Text.h"
//Constructors and Destructors
Text::Text()
{

}

Text::Text(float x, float y, int text_size, std::string textString, sf::Color text_color, bool hidden)
{
	//Text Variables
	this->text.setString(textString);
	this->text.setFillColor(text_color);
	this->text.setFont(font);
	this->text.setCharacterSize(text_size);
	this->text.setPosition(x, y);
	this->textString = this->textString;
	this->hidden = hidden;

	font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
}

Text::~Text()
{

}

//Text Functions
void Text::render(sf::RenderTarget* target)
{
	if(!this->hidden)
	target->draw(this->text);
}

void Text::setString(std::string text)
{
	this->text.setString(text);
}