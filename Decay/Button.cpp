#include "Button.h"
//Constructors and Destructors
Button::Button(std::string text, float x, float y)
{
    this->buttonText.setString(text);
    this->button.setPosition(x, y);
    this->buttonText.setPosition(x, y);

    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->loadButton();
}

Button::~Button()
{
    
}

//Core Functions
void Button::render(sf::RenderTarget* target)
{
    target->draw(this->button);
    target->draw(this->buttonText);
}

void Button::setPos(float& x, float& y)
{
    this->button.setPosition(x, y);
    this->buttonText.setPosition(x, y);
}

//Asset Functions
void Button::loadButton()
{
    buttonText.setFont(font);
    buttonText.setCharacterSize(18);
    buttonText.setFillColor(sf::Color::Black);
    button.setSize(sf::Vector2f(150.0f, 25.0f));
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(1.0f);
}
