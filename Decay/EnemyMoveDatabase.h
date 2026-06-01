#pragma once

#include "EnemyTypes.h"

#include <string>
#include <unordered_map>
#include <vector>

class EnemyMoveDatabase
{
public:
    static EnemyMoveDatabase& getInstance();

    EnemyMoveDatabase(const EnemyMoveDatabase&) = delete;
    EnemyMoveDatabase& operator=(const EnemyMoveDatabase&) = delete;

    bool loadFromFile(const std::string& filePath);

    const EnemyMoveDefinition* getMove(const std::string& id) const;
    const std::vector<EnemyMoveDefinition> getAllMoves() const;

private:
    EnemyMoveDatabase() = default;

private:
    std::unordered_map<std::string, EnemyMoveDefinition> moves;
};