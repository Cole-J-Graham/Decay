#include "UiSprite.h"
#include <algorithm>

UiSprite::UiSprite(const std::string& textureId, float x, float y, float scaleX, float scaleY, bool hidden)
{
    this->sprite.setTexture(AssetDatabase::getInstance().getTexture(textureId));
    this->sprite.setPosition(x, y);
    this->sprite.setScale(scaleX, scaleY);
    this->hidden = hidden;
}

UiSprite::UiSprite(const std::string& textureId, sf::Vector2f position, sf::Vector2f scale, bool hidden)
{
    this->sprite.setTexture(AssetDatabase::getInstance().getTexture(textureId));
    this->sprite.setPosition(position);
    this->sprite.setScale(scale);
    this->hidden = hidden;
}

void UiSprite::update(sf::Vector2f mousePos)
{}

void UiSprite::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    if (!this->hidden) {
        target->draw(this->sprite);
    }
}

void UiSprite::setPosition(float x, float y)
{
    this->sprite.setPosition(x, y);
}

void UiSprite::setScale(float scaleX, float scaleY)
{
    this->sprite.setScale(scaleX, scaleY);
}

void UiSprite::show()
{
    this->hidden = false;
}

void UiSprite::hide()
{
    this->hidden = true;
}

bool UiSprite::isHidden() const
{
    return this->hidden;
}

void UiSprite::fitInside(float boxX, float boxY, float boxWidth, float boxHeight, float padding)
{
    const sf::FloatRect bounds = this->sprite.getLocalBounds();

    if (bounds.width <= 0.f || bounds.height <= 0.f) {
        return;
    }

    const float availableWidth = boxWidth - (padding * 2.f);
    const float availableHeight = boxHeight - (padding * 2.f);

    const float scaleX = availableWidth / bounds.width;
    const float scaleY = availableHeight / bounds.height;

    const float scale = std::min(scaleX, scaleY);

    this->sprite.setScale(scale, scale);

    const float scaledWidth = bounds.width * scale;
    const float scaledHeight = bounds.height * scale;

    const float centeredX = boxX + (boxWidth - scaledWidth) / 2.f;
    const float centeredY = boxY + (boxHeight - scaledHeight) / 2.f;

    this->sprite.setPosition(centeredX, centeredY);
}