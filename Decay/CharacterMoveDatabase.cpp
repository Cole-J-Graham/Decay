#include "CharacterMoveDatabase.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace
{
    std::vector<std::string> splitKeepEmpty(const std::string& text, char delimiter)
    {
        std::vector<std::string> parts;
        std::stringstream ss(text);
        std::string part;

        while (std::getline(ss, part, delimiter)) {
            parts.push_back(part);
        }

        return parts;
    }

    std::vector<std::string> splitSkipEmpty(const std::string& text, char delimiter)
    {
        std::vector<std::string> parts;
        std::stringstream ss(text);
        std::string part;

        while (std::getline(ss, part, delimiter)) {
            if (!part.empty()) {
                parts.push_back(part);
            }
        }

        return parts;
    }

    MoveEffectDefinition parseEffect(const std::string& token)
    {
        MoveEffectDefinition effect;

        std::vector<std::string> parts = splitKeepEmpty(token, ':');

        // Supported:
        // TYPE:TARGET:VALUE:DURATION
        // TYPE:TARGET:TARGET_ID:VALUE:DURATION
        if (parts.size() == 4) {
            effect.type = parts[0];
            effect.target = parts[1];
            effect.value = std::stof(parts[2]);
            effect.durationTurns = std::stoi(parts[3]);
        }
        else if (parts.size() == 5) {
            effect.type = parts[0];
            effect.target = parts[1];
            effect.targetId = parts[2];
            effect.value = std::stof(parts[3]);
            effect.durationTurns = std::stoi(parts[4]);
        }
        else {
            std::cerr << "Invalid character move effect token: " << token << "\n";
        }

        return effect;
    }

    std::vector<MoveEffectDefinition> parseEffects(const std::string& text)
    {
        std::vector<MoveEffectDefinition> effects;

        if (text.empty() || text == "NONE") {
            return effects;
        }

        std::vector<std::string> tokens = splitSkipEmpty(text, ';');

        for (const auto& token : tokens) {
            effects.push_back(parseEffect(token));
        }

        return effects;
    }
}

CharacterMoveDatabase& CharacterMoveDatabase::getInstance()
{
    static CharacterMoveDatabase instance;
    return instance;
}

bool CharacterMoveDatabase::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open character move database: " << filePath << "\n";
        return false;
    }

    this->moves.clear();

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        if (line[0] == '#') {
            continue;
        }

        if (line.rfind("id|", 0) == 0) {
            continue;
        }

        std::vector<std::string> fields = splitKeepEmpty(line, '|');

        if (fields.size() < 10) {
            std::cerr << "Invalid character move line: " << line << "\n";
            continue;
        }

        CharacterMoveDefinition move;
        move.id = fields[0];
        move.ownerId = fields[1];
        move.buttonText = fields[2];
        move.message = fields[3];
        move.tip = fields[4];
        move.sfxId = fields[5];
        move.cooldown = std::stoi(fields[6]);
        move.poseTexturePath = fields[7];
        move.poseDurationTurns = std::stoi(fields[8]);
        move.effects = parseEffects(fields[9]);

        // field 10 — mpMax. "infinite" or missing = -1
        if (fields.size() > 10 && fields[10] != "infinite" && !fields[10].empty()) {
            move.mpMax = std::stoi(fields[10]);
        }
        else {
            move.mpMax = -1;
        }

        if (move.id.empty() || move.ownerId.empty()) {
            std::cerr << "Character move missing id or owner: " << line << "\n";
            continue;
        }

        this->moves[move.id] = move;
    }

    std::cout << "Loaded character moves: " << this->moves.size() << "\n";
    return true;
}

const CharacterMoveDefinition* CharacterMoveDatabase::getMove(const std::string& moveId) const
{
    auto it = this->moves.find(moveId);

    if (it == this->moves.end()) {
        return nullptr;
    }

    return &it->second;
}

std::vector<const CharacterMoveDefinition*> CharacterMoveDatabase::getMovesForOwner(const std::string& ownerId) const
{
    std::vector<const CharacterMoveDefinition*> ownerMoves;

    for (const auto& pair : this->moves) {
        if (pair.second.ownerId == ownerId) {
            ownerMoves.push_back(&pair.second);
        }
    }

    return ownerMoves;
}