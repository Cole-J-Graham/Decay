#include "CharacterPose.h"

#include <iostream>

bool CharacterPose::loadIdleTexture(const std::string& texturePath, sf::Sprite& sprite)
{
    if (!this->idleTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load character idle texture: " << texturePath << "\n";
        return false;
    }

    sprite.setTexture(this->idleTexture, true);
    return true;
}

void CharacterPose::playTemporaryPose(
    sf::Sprite& sprite,
    const std::string& texturePath,
    int durationTurns
)
{
    if (texturePath.empty() || durationTurns <= 0) {
        return;
    }

    if (!this->poseTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load temporary pose texture: " << texturePath << "\n";
        return;
    }

    sprite.setTexture(this->poseTexture, true);
    this->temporaryPoseActive = true;
    this->temporaryPoseTurns = durationTurns;
}

void CharacterPose::resetPose(sf::Sprite& sprite)
{
    sprite.setTexture(this->idleTexture, true);
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