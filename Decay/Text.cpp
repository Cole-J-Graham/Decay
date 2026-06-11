#include "Text.h"

#include <stdexcept>

// Constructors and Destructors
Text::Text()
    : x(0.f), y(0.f), text_size(0), hidden(true), duration(0.f)
{}

Text::Text(int text_size, std::string textString, sf::Color text_color, bool hidden, float duration)
{
    this->initText(
        this->menuText_x,
        this->menuText_y,
        text_size,
        textString,
        text_color,
        hidden,
        duration
    );
}

Text::Text(float x, float y, int text_size, std::string textString, sf::Color text_color,
    bool hidden, float duration)
{
    this->initText(
        x,
        y,
        text_size,
        textString,
        text_color,
        hidden,
        duration
    );
}

void Text::initText(float x, float y, int text_size, const std::string& textString,
    sf::Color text_color, bool hidden, float duration)
{
    this->x = x;
    this->y = y;
    this->text_size = text_size;
    this->hidden = hidden;
    this->duration = duration;
    this->textString = textString;
    this->text_color = text_color;

    this->text.setString(textString);
    this->text.setFillColor(text_color);
    this->text.setFont(AssetDatabase::getInstance().getFont("ticker_font"));
    this->text.setCharacterSize(text_size);
    this->text.setPosition(x, y);

    this->countdownText.setFont(AssetDatabase::getInstance().getFont("ticker_font"));
    this->countdownText.setCharacterSize(18);
    this->countdownText.setFillColor(sf::Color::White);
    this->countdownText.setPosition(5.f, 782.f);

    if (!hidden) {
        this->timer.restart();
    }
}

// Core Functions
void Text::update()
{
    if (this->hidden) {
        return;
    }

    if (this->duration > 0.f &&
        this->timer.getElapsedTime().asSeconds() >= this->duration) {
        this->setHidden();
    }
}

void Text::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    this->update();

    if (this->hidden) {
        return;
    }

    target->draw(this->text);

    if (this->countdownVisible && this->duration > 0.f) {
        float remainingTime = this->duration - this->timer.getElapsedTime().asSeconds();

        if (remainingTime < 0.f) {
            remainingTime = 0.f;
        }

        this->countdownText.setString(std::to_string(static_cast<int>(remainingTime)));
        target->draw(this->countdownText);
    }
}

// Text Functions
void Text::setString(const std::string& text)
{
    this->textString = text;
    this->text.setString(text);
}

void Text::showFor(const std::string& text, float durationSeconds)
{
    this->setString(text);
    this->duration = durationSeconds;
    this->setShown();
}

void Text::clearDuration()
{
    this->duration = 0.f;
}

// Setters
bool& Text::setHidden()
{
    this->hidden = true;
    return this->hidden;
}

bool& Text::setShown()
{
    this->hidden = false;
    this->timer.restart();
    return this->hidden;
}

std::string Text::wrapText(const std::string& text, float maxWidth, unsigned int charSize)
{
    const sf::Font& font = AssetDatabase::getInstance().getFont("ticker_font");

    std::string result;
    std::string word;
    float       lineWidth = 0.f;

    auto measureWord = [&](const std::string& w) -> float
        {
            float width = 0.f;
            for (char c : w)
                width += font.getGlyph(c, charSize, false).advance;
            return width;
        };

    const float spaceAdvance = font.getGlyph(' ', charSize, false).advance;

    for (size_t i = 0; i <= text.size(); ++i)
    {
        char c = (i < text.size()) ? text[i] : '\0';

        if (c == ' ' || c == '\n' || c == '\0')
        {
            if (!word.empty())
            {
                float wordWidth = measureWord(word);

                if (lineWidth > 0.f && lineWidth + spaceAdvance + wordWidth > maxWidth)
                {
                    result += '\n';
                    lineWidth = 0.f;
                }
                else if (lineWidth > 0.f)
                {
                    result += ' ';
                    lineWidth += spaceAdvance;
                }

                result += word;
                lineWidth += wordWidth;
                word.clear();
            }

            if (c == '\n')
            {
                result += '\n';
                lineWidth = 0.f;
            }
        }
        else
        {
            word += c;
        }
    }

    return result;
}