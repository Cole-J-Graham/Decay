#pragma once

#include <string>
#include <vector>

struct MoveEffectDefinition
{
    std::string type;
    std::string target;
    std::string targetId;

    float value = 0.f;
    int durationTurns = 0;
};

struct CharacterMoveDefinition
{
    std::string id;
    std::string ownerId;

    std::string buttonText;
    std::string message;
    std::string tip;

    std::string sfxId;
    int cooldown = 0;

    std::string poseTexturePath;
    int poseDurationTurns = 0;

    // -1 = infinite; any other value = max uses per combat
    int mpMax = -1;

    std::vector<MoveEffectDefinition> effects;
};