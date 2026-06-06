#pragma once
#include "AssetDatabase.h"
#include <SFML/Graphics.hpp>
#include <string>

class NPC
{
public:
    NPC(const std::string& id, const std::string& displayName, const std::string& assetId, float scale = 1.0f);

    void renderPreview(sf::RenderTarget* target, float x, float y);

    const std::string& getId() const { return id; }
    const std::string& getDisplayName() const { return displayName; }

private:
    std::string id;
    std::string displayName;
    std::string assetId;
    sf::Sprite sprite;
};