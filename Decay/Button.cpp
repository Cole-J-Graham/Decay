#include "Button.h"
//Constructors and Destructors
Button::Button(float x, float y, float width, float height, float clicktime, sf::Font font,
    std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, 
    bool hidden)
{
    this->buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(sf::Color::White);

    this->font = font;
    this->text.setFont(this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(16);
    this->text.setPosition(x, y);

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
    this->hidden = hidden;
    this->clicktime = clicktime;
    this->enabled = true;


    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
}

Button::~Button()
{
    
}

//Core Functions
void Button::update(const sf::Vector2f mousePos)
{
    /*Update the booleans for hover and pressed*/
    this->elapsed = this->clock.getElapsedTime();

    //Idle
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(mousePos)) {
        //Hover
        this->buttonState = BTN_HOVER;
        if (this->elapsed.asSeconds() >= this->clicktime) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //Pressed
                this->buttonState = BTN_ACTIVE;
                this->clock.restart();
            }
        }
    }

    switch (this->buttonState) {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}

void Button::render(sf::RenderTarget* target)
{
    if (!this->hidden) {
        target->draw(this->shape);
        target->draw(this->text);
    }
}

//Accessors
const bool Button::isPressed() const
{
    if (this->buttonState == BTN_ACTIVE)
        return true;

    return false;
}

const bool Button::isHovered() const
{
    if (this->buttonState == BTN_HOVER)
        return true;

    return false;
}
