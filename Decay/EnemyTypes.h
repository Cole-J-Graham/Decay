#pragma once

#include "RewardTypes.h"

#include <string>
#include <vector>

struct EnemyMoveDefinition
{
    std::string id;
    std::string message;
    std::string sfxId;

    float damageMultiplier = 1.f;
};

struct EnemyDefinition
{
    std::string id;
    std::string name;

    float hp = 0.f;
    float hpMax = 0.f;
    float damage = 0.f;
    float defense = 0.f;
    float scale = 1.f;

    std::string spritePath;
    std::string viewerPath;

    RewardBundle rewards;

    std::vector<std::string> moveIds;
    std::vector<std::string> spawnAreas;
};