#pragma once

#include "CharacterMoveTypes.h"

#include <string>
#include <unordered_map>
#include <vector>

class CharacterMoveDatabase
{
public:
    static CharacterMoveDatabase& getInstance();

    CharacterMoveDatabase(const CharacterMoveDatabase&) = delete;
    CharacterMoveDatabase& operator=(const CharacterMoveDatabase&) = delete;

    bool loadFromFile(const std::string& filePath);

    const CharacterMoveDefinition* getMove(const std::string& moveId) const;
    std::vector<const CharacterMoveDefinition*> getMovesForOwner(const std::string& ownerId) const;

private:
    CharacterMoveDatabase() = default;

private:
    std::unordered_map<std::string, CharacterMoveDefinition> moves;
};