#include "EnemyMoveDatabase.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace
{
    std::vector<std::string> split(const std::string& text, char delimiter)
    {
        std::vector<std::string> parts;
        std::stringstream ss(text);
        std::string part;

        while (std::getline(ss, part, delimiter)) {
            parts.push_back(part);
        }

        return parts;
    }
}

EnemyMoveDatabase& EnemyMoveDatabase::getInstance()
{
    static EnemyMoveDatabase instance;
    return instance;
}

bool EnemyMoveDatabase::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open enemy move database: " << filePath << "\n";
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

        // Allows a header row.
        if (line.rfind("id|", 0) == 0) {
            continue;
        }

        std::vector<std::string> fields = split(line, '|');

        if (fields.size() < 6) {
            std::cerr << "Invalid enemy move line: " << line << "\n";
            continue;
        }

        EnemyMoveDefinition move;
        move.id = fields[0];
        move.type = fields[1];
        move.target = fields[2];
        move.message = fields[3];
        move.sfxId = fields[4];
        move.power = std::stof(fields[5]);

        if (move.id.empty()) {
            std::cerr << "Enemy move has empty id: " << line << "\n";
            continue;
        }

        this->moves[move.id] = move;
    }

    std::cout << "Loaded enemy moves: " << this->moves.size() << "\n";
    return true;
}

const EnemyMoveDefinition* EnemyMoveDatabase::getMove(const std::string& id) const
{
    auto it = this->moves.find(id);

    if (it == this->moves.end()) {
        return nullptr;
    }

    return &it->second;
}

const std::vector<EnemyMoveDefinition> EnemyMoveDatabase::getAllMoves() const
{
    std::vector<EnemyMoveDefinition> allMoves;

    for (const auto& pair : this->moves) {
        allMoves.push_back(pair.second);
    }

    return allMoves;
}