#pragma once

#include "Button.h"
#include "Rectangle.h"
#include "Text.h"
#include "UiSprite.h"
#include "AnimationPlayer.h"

#include <map>
#include <memory>
#include <string>

class UiPanel
{
public:
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget& target);

    void addButton(const std::string& id, std::unique_ptr<Button> button);
    void addRectangle(const std::string& id, std::unique_ptr<Rectangle> rectangle);
    void addText(const std::string& id, std::unique_ptr<Text> text);
    void addSprite(const std::string& id, std::unique_ptr<UiSprite> sprite);
    void addAnimation(const std::string& id, std::unique_ptr<AnimationPlayer> animation);

    Button& button(const std::string& id);
    Rectangle& rectangle(const std::string& id);
    Text& text(const std::string& id);
    UiSprite& sprite(const std::string& id);
    AnimationPlayer& animation(const std::string& id);

private:
    std::map<std::string, std::unique_ptr<Button>> buttons;
    std::map<std::string, std::unique_ptr<Rectangle>> rectangles;
    std::map<std::string, std::unique_ptr<Text>> texts;
    std::map<std::string, std::unique_ptr<UiSprite>> sprites;
    std::map<std::string, std::unique_ptr<AnimationPlayer>> animations;
};