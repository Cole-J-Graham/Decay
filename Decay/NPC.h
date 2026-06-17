#pragma once
#include "AssetDatabase.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class NPC
{
public:
    NPC(const std::string& id, const std::string& displayName, const std::string& assetId, float scale = 1.0f);

    void renderPreview(sf::RenderTarget* target, float x, float y);
    void setEmotion(const std::string& emotion);
    void addEmotion(const std::string& emotion, const std::string& assetId);

    const std::string& getId() const { return id; }
    const std::string& getDisplayName() const { return displayName; }

private:
    std::string id;
    std::string displayName;
    std::string assetId;        // default/neutral asset
    std::string currentEmotion;
    float       scale = 1.f;    // stored so setEmotion can reapply after texture swap
    sf::Sprite sprite;

    std::unordered_map<std::string, std::string> emotionAssets;
};