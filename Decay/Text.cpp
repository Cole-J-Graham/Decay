#include "Text.h"

// Constructors and Destructors
Text::Text() : x(0), y(0), text_size(0), hidden(true), duration(0.f)
{
}

Text::Text(int text_size, std::string textString, sf::Color text_color, bool hidden, float duration)
    : text_size(text_size), hidden(hidden), duration(duration)
{
    // Load font
    if (!font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    // Main Text
    this->text.setString(textString);
    this->text.setFillColor(text_color);
    this->text.setFont(font);
    this->text.setCharacterSize(text_size);
    this->text.setPosition(menuText_x, menuText_y);
    this->textString = textString;

    // Countdown Text
    this->countdownText.setFont(font);
    this->countdownText.setCharacterSize(18);
    this->countdownText.setFillColor(sf::Color::White);
    this->countdownText.setPosition(5.f, 782.f);

    if (!hidden)
    {
        timer.restart(); // Start the timer if the text is initially shown
    }
}

Text::Text(float x, float y, int text_size, std::string textString, sf::Color text_color,
    bool hidden, float duration)
    : x(x), y(y), text_size(text_size), hidden(hidden), duration(duration)
{
    // Load font
    if (!font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    // Main Text
    this->text.setString(textString);
    this->text.setFillColor(text_color);
    this->text.setFont(font);
    this->text.setCharacterSize(text_size);
    this->text.setPosition(x, y);
    this->textString = textString;

    // Countdown Text
    this->countdownText.setFont(font);
    this->countdownText.setCharacterSize(18);
    this->countdownText.setFillColor(sf::Color::White);
    this->countdownText.setPosition(5.f, 782.f);

    if (!hidden)
    {
        timer.restart(); // Start the timer if the text is initially shown
    }
}

Text::~Text()
{
}

// Text Functions
void Text::render(sf::RenderTarget* target)
{
    // Check if the duration has elapsed
    if (!hidden && duration > 0.f && timer.getElapsedTime().asSeconds() > duration)
    {
        this->hidden = true;
    }

    // Render main text
    if (!this->hidden)
    {
        target->draw(this->text);

        // Update and render countdown as a number
        float remainingTime = duration - timer.getElapsedTime().asSeconds();
        if (remainingTime < 0.f) remainingTime = 0.f;
        countdownText.setString(std::to_string(static_cast<int>(remainingTime)));
        target->draw(this->countdownText);
    }
}

void Text::setString(std::string text)
{
    this->text.setString(text);
}

void Text::update()
{
    // Hide the text if duration is exceeded
    if (!hidden && duration > 0.f && timer.getElapsedTime().asSeconds() > duration)
    {
        this->hidden = true;
    }
}
