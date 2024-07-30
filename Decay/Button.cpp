#include "Button.h"

Button::Button(float x, float y, float width, float height, float clicktime,
    std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
    bool hidden)
{
    this->buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(sf::Color::White);

    if (this->font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf")) {
        this->text.setFont(this->font);
    }
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(16);
    this->text.setPosition(x, y);

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
    this->hidden = hidden;

    // Initialize click blocking mechanism
    this->clickBlocked = false;
    this->clickBlockDuration = 0.1; // Adjust as needed
}

Button::Button(sf::Vector2f pos, float width, float height, float clicktime,
    std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
    bool hidden)
{
    this->buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(pos));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(sf::Color::White);

    if (this->font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf")) {
        this->text.setFont(this->font);
    }
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(16);
    this->text.setPosition(pos);

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
    this->hidden = hidden;

    // Initialize click blocking mechanism
    this->clickBlocked = false;
    this->clickBlockDuration = 0.1; // Adjust as needed
}

void Button::update(const sf::Vector2f mousePos)
{
    if (!this->hidden) {
        /* Update the booleans for hover and pressed */
        if (!this->clickBlocked) {
            this->elapsed = this->clock.getElapsedTime();

            // Idle
            this->buttonState = BTN_IDLE;
            if (this->shape.getGlobalBounds().contains(mousePos)) {
                // Hover
                this->buttonState = BTN_HOVER;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // Pressed
                    this->buttonState = BTN_ACTIVE;
                    this->clock.restart();
                    //std::cout << "Clicked: " << this->text.getString().toAnsiString() << std::endl;
                    // Block further clicks temporarily
                    this->clickBlocked = true;
                    this->clickBlockTimer.restart();
                }
            }
        }

        // Check and reset click blocking
        if (this->clickBlocked && this->clickBlockTimer.getElapsedTime().asSeconds() >= this->clickBlockDuration) {
            this->clickBlocked = false;
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
}

void Button::render(sf::RenderTarget* target)
{
    if (!this->hidden) {
        target->draw(this->shape);
        target->draw(this->text);
    }
}

const bool Button::isPressed() const
{
    if (this->buttonState == BTN_ACTIVE && !this->clickBlocked && !this->hidden) {
        return true;
    }
    else {
        return false;
    }
}

const bool Button::isHovered() const
{
    if (this->buttonState == BTN_HOVER && !this->clickBlocked && !this->hidden)
        return true;

    return false;
}