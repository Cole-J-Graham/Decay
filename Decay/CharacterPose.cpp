#include "CharacterPose.h"
#include "AssetDatabase.h"

#include <iostream>

bool CharacterPose::loadIdleTexture(const std::string& textureAssetId, sf::Sprite& sprite)
{
    try {
        sprite.setTexture(AssetDatabase::getInstance().getTexture(textureAssetId), true);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load character idle texture asset \"" << textureAssetId
            << "\": " << e.what() << "\n";
        return false;
    }

    this->idleAssetId = textureAssetId;
    return true;
}

void CharacterPose::playTemporaryPose(
    sf::Sprite& sprite,
    const std::string& textureAssetId,
    int durationTurns
)
{
    if (textureAssetId.empty() || durationTurns <= 0) {
        return;
    }

    try {
        sprite.setTexture(AssetDatabase::getInstance().getTexture(textureAssetId), true);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load temporary pose texture asset \"" << textureAssetId
            << "\": " << e.what() << "\n";
        return;
    }

    this->temporaryPoseActive = true;
    this->temporaryPoseTurns = durationTurns;
}

void CharacterPose::resetPose(sf::Sprite& sprite)
{
    if (!this->idleAssetId.empty()) {
        try {
            sprite.setTexture(AssetDatabase::getInstance().getTexture(this->idleAssetId), true);
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to restore character idle texture asset \"" << this->idleAssetId
                << "\": " << e.what() << "\n";
        }
    }

    this->temporaryPoseActive = false;
    this->temporaryPoseTurns = 0;
}

bool CharacterPose::hasTemporaryPose() const
{
    return this->temporaryPoseActive;
}

void CharacterPose::consumePoseTurn(sf::Sprite& sprite)
{
    if (!this->temporaryPoseActive) {
        return;
    }

    if (this->temporaryPoseTurns > 0) {
        this->temporaryPoseTurns--;
    }

    if (this->temporaryPoseTurns <= 0) {
        this->resetPose(sprite);
    }
}