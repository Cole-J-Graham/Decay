#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class CharacterPose
{
public:
    // textureAssetId must be registered in assets.db / AssetDatabase
    bool loadIdleTexture(const std::string& textureAssetId, sf::Sprite& sprite);

    void playTemporaryPose(
        sf::Sprite& sprite,
        const std::string& textureAssetId,
        int durationTurns
    );

    void resetPose(sf::Sprite& sprite);
    bool hasTemporaryPose() const;
    void consumePoseTurn(sf::Sprite& sprite);

private:
    // Remembered so resetPose() can look the idle texture back up from
    // AssetDatabase's cache — CharacterPose no longer owns Texture objects.
    std::string idleAssetId;

    bool temporaryPoseActive = false;
    int temporaryPoseTurns = 0;
};