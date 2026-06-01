#pragma once

#include "AssetDatabase.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>

class Text
{
public:
    // Constructors and Destructors
    Text();

    Text(int text_size, std::string textString, sf::Color text_color,
        bool hidden, float duration = 0.f);

    Text(float x = 5.f, float y = 810.f, int text_size = 0,
        std::string textString = "",
        sf::Color text_color = sf::Color::White,
        bool hidden = true,
        float duration = 0.f);

    ~Text() = default;

    // Core Functions
    void update();
    void render(sf::RenderTarget* target);

    // Text Functions
    void setString(const std::string& text);
    void showFor(const std::string& text, float durationSeconds);
    void clearDuration();

    // Modifiers
    void setPosition(float x, float y) { this->text.setPosition(x, y); }
    void setPositionDefault() { this->text.setPosition(menuText_x, menuText_y); }

    void setCountdownVisible(bool visible) { this->countdownVisible = visible; }
    void setCountdownPosition(float x, float y) { this->countdownText.setPosition(x, y); }

    // Getters
    bool& getHidden() { return this->hidden; }
    const std::string& getString() const { return this->textString; }

    // Setters
    bool& setHidden();
    bool& setShown();

private:
    void initText(float x, float y, int text_size, const std::string& textString,
        sf::Color text_color, bool hidden, float duration);

private:
    std::string textString;

    sf::Text text;
    sf::Text countdownText;

    sf::Color text_color;

    float x;
    float y;

    const float menuText_x = 5.f;
    const float menuText_y = 810.f;

    int text_size;
    bool hidden;

    // Optional timer behavior
    float duration;
    sf::Clock timer;

    // Debug/optional countdown display
    bool countdownVisible = false;
};