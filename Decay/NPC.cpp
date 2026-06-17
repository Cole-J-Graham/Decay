#include "NPC.h"
#include <iostream>

NPC::NPC(const std::string& id, const std::string& displayName, const std::string& assetId, float scale)
    : id(id), displayName(displayName), assetId(assetId), scale(scale)
{
    if (AssetDatabase::getInstance().has(assetId))
    {
        sprite.setTexture(AssetDatabase::getInstance().getTexture(assetId));
        sprite.setScale(scale, scale);
    }
    else
        std::cerr << "NPC: asset ID not found in database: " << assetId << "\n";
}

void NPC::renderPreview(sf::RenderTarget* target, float x, float y)
{
    sprite.setPosition(x, y);

    const float padding = 1.f; // adjust border thickness here

    sf::FloatRect bounds = sprite.getGlobalBounds();

    sf::RectangleShape border(sf::Vector2f(
        bounds.width + padding * 2.f,
        bounds.height + padding * 2.f));

    border.setPosition(x - padding, y - padding);
    border.setFillColor(sf::Color::White);
    border.setOutlineThickness(0.f);

    target->draw(border);
    target->draw(sprite);
}

void NPC::addEmotion(const std::string& emotion, const std::string& assetId)
{
    emotionAssets[emotion] = assetId;
}

void NPC::setEmotion(const std::string& emotion)
{
    if (emotion.empty() || emotion == currentEmotion) return;

    currentEmotion = emotion;

    auto it = emotionAssets.find(emotion);
    if (it != emotionAssets.end() && AssetDatabase::getInstance().has(it->second)) {
        sprite.setTexture(AssetDatabase::getInstance().getTexture(it->second));
    }
    else {
        // Fall back to default neutral texture
        if (AssetDatabase::getInstance().has(assetId))
            sprite.setTexture(AssetDatabase::getInstance().getTexture(assetId));
    }

    // Reapply scale — texture swap resets it to 1.0
    sprite.setScale(scale, scale);
}