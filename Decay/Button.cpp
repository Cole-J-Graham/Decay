#include "Button.h"
#include "AssetDatabase.h"

Button::Button(float x, float y, float width, float height, float clicktime,
    std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
    bool hidden)
{
    this->buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(sf::Color::White);

    this->text.setFont(AssetDatabase::getInstance().getFont("ticker_font"));
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(16);
    this->text.setPosition(x, y);

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
    this->hidden = hidden;

    this->clickBlocked = false;
    this->clickBlockDuration = 0.1;
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

    this->text.setFont(AssetDatabase::getInstance().getFont("ticker_font"));
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(16);
    this->text.setPosition(pos);

    if (width <= 0.f)
    {
        sf::FloatRect bounds = this->text.getLocalBounds();
        width = bounds.width + 5.f;
    }

    this->shape.setSize(sf::Vector2f(width, height));

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
    this->hidden = hidden;

    this->clickBlocked = false;
    this->clickBlockDuration = 0.1;
}

void Button::update(const sf::Vector2f mousePos)
{
    if (this->hidden) {
        this->buttonState = BTN_IDLE;
        this->shape.setFillColor(this->idleColor);

        this->leftMouseWasDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        this->rightMouseWasDown = sf::Mouse::isButtonPressed(sf::Mouse::Right);
        return;
    }

    this->buttonState = BTN_IDLE;

    const bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    const bool rightMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Right);

    const bool leftClickedThisFrame = leftMouseDown && !this->leftMouseWasDown;
    const bool rightClickedThisFrame = rightMouseDown && !this->rightMouseWasDown;

    if (this->shape.getGlobalBounds().contains(mousePos)) {
        this->buttonState = BTN_HOVER;

        if (leftClickedThisFrame) {
            this->buttonState = BTN_ACTIVE_LEFT;
            std::cout << "Clicked LEFT: " << this->text.getString().toAnsiString() << std::endl;
            if (this->playClickSfx && !this->clickSfxId.empty()) {
                SfxManager::getInstance().play(this->clickSfxId);
            }
        }
        else if (rightClickedThisFrame) {
            this->buttonState = BTN_ACTIVE_RIGHT;
            std::cout << "Clicked RIGHT: " << this->text.getString().toAnsiString() << std::endl;
        }
    }

    this->leftMouseWasDown = leftMouseDown;
    this->rightMouseWasDown = rightMouseDown;

    switch (this->buttonState) {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;
    case BTN_ACTIVE_LEFT:
        this->shape.setFillColor(this->activeColor);
        break;
    case BTN_ACTIVE_RIGHT:
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

const bool Button::isPressed() const
{
    return this->buttonState == BTN_ACTIVE_LEFT && !this->hidden;
}

const bool Button::isPressedRight() const
{
    return this->buttonState == BTN_ACTIVE_RIGHT && !this->hidden;
}

const bool Button::isHovered() const
{
    return this->buttonState == BTN_HOVER && !this->hidden;
}

void Button::setIdle()
{
    this->buttonState = BTN_IDLE;
    this->shape.setFillColor(this->idleColor);
}