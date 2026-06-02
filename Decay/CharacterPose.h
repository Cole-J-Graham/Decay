#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class CharacterPose
{
public:
    bool loadIdleTexture(const std::string& texturePath, sf::Sprite& sprite);

    void playTemporaryPose(
        sf::Sprite& sprite,
        const std::string& texturePath,
        int durationTurns
    );

    void resetPose(sf::Sprite& sprite);
    bool hasTemporaryPose() const;
    void consumePoseTurn(sf::Sprite& sprite);

private:
    sf::Texture idleTexture;
    sf::Texture poseTexture;

    bool temporaryPoseActive = false;
    int temporaryPoseTurns = 0;
};