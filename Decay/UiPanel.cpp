#include "UiPanel.h"

void UiPanel::update(sf::Vector2f mousePos)
{
    for (auto& [id, button] : buttons) {
        button->update(mousePos);
    }

    for (auto& [id, rectangle] : rectangles) {
        rectangle->update(mousePos);
    }

    for (auto& [id, sprite] : sprites) {
        sprite->update(mousePos);
    }

    for (auto& [id, animation] : animations) {
        animation->update();
    }
}

void UiPanel::render(sf::RenderTarget& target)
{
    for (auto& [id, rectangle] : rectangles) {
        rectangle->render(&target);
    }

    for (auto& [id, sprite] : sprites) {
        sprite->render(&target);
    }

    for (auto& [id, animation] : animations) {
        animation->render(&target);
    }

    for (auto& [id, button] : buttons) {
        button->render(&target);
    }

    for (auto& [id, text] : texts) {
        text->render(&target);
    }
}

void UiPanel::addButton(const std::string& id, std::unique_ptr<Button> button)
{
    buttons[id] = std::move(button);
}

void UiPanel::addRectangle(const std::string& id, std::unique_ptr<Rectangle> rectangle)
{
    rectangles[id] = std::move(rectangle);
}

void UiPanel::addText(const std::string& id, std::unique_ptr<Text> text)
{
    texts[id] = std::move(text);
}

void UiPanel::addSprite(const std::string& id, std::unique_ptr<UiSprite> sprite)
{
    sprites[id] = std::move(sprite);
}

void UiPanel::addAnimation(const std::string& id, std::unique_ptr<AnimationPlayer> animation)
{
    animations[id] = std::move(animation);
}

Button& UiPanel::button(const std::string& id)
{
    return *buttons.at(id);
}

Rectangle& UiPanel::rectangle(const std::string& id)
{
    return *rectangles.at(id);
}

Text& UiPanel::text(const std::string& id)
{
    return *texts.at(id);
}

UiSprite& UiPanel::sprite(const std::string& id)
{
    return *sprites.at(id);
}

AnimationPlayer& UiPanel::animation(const std::string& id)
{
    return *animations.at(id);
}