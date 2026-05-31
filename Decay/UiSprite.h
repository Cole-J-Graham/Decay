#pragma once

#include "AssetDatabase.h"

#include <SFML/Graphics.hpp>
#include <string>

class UiSprite
{
public:
    UiSprite(const std::string& textureId, float x, float y, float scaleX, float scaleY, bool hidden);
    UiSprite(const std::string& textureId, sf::Vector2f position, sf::Vector2f scale, bool hidden);

    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

    void setPosition(float x, float y);
    void setScale(float scaleX, float scaleY);

    void show();
    void hide();

    bool isHidden() const;

    void fitInside(float boxX, float boxY, float boxWidth, float boxHeight, float padding = 0.f);

private:
    sf::Sprite sprite;
    bool hidden;
};