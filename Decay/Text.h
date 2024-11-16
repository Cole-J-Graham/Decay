#pragma once
#include "Asset.h"
#include <SFML/System.hpp> // For sf::Clock

class Text
{
public:
    // Constructors and Destructors
    Text();
    Text(float x, float y, int text_size, std::string textString, sf::Color text_color,
        bool hidden, float duration = 0.f);
    ~Text();

    // Text Functions
    void render(sf::RenderTarget* target);
    void setString(std::string text);
    void update();

    // Modifiers
    void setPosition(float x, float y) { this->text.setPosition(x, y); };

    // Getters
    bool& getHidden() { return this->hidden; };
    const std::string& getString() const { return this->textString; }

    // Setters
    bool& setHidden() { return this->hidden = true; };
    bool& setShown() {
        this->hidden = false;
        this->timer.restart(); // Restart the timer if duration is set
        return this->hidden;
    };

private:
    // Text Variables
    std::string textString;
    sf::Text text;
    sf::Font font;
    sf::Color text_color;

    float x;
    float y;
    int text_size;
    bool hidden;

    // Timer Variables
    float duration;         // Duration in seconds
    sf::Clock timer;        // Timer to track visibility
};