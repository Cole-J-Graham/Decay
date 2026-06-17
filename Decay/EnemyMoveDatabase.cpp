#include "EnemyMoveDatabase.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace
{
    std::vector<std::string> split(const std::string& text, char delimiter)
    {
        std::vector<std::string> parts;
        std::stringstream ss(text);
        std::string part;
        while (std::getline(ss, part, delimiter))
            parts.push_back(part);
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
    if (!file.is_open())
    {
        std::cerr << "Failed to open enemy move database: " << filePath << "\n";
        return false;
    }

    this->moves.clear();

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        if (line.rfind("id|", 0) == 0)      continue; // header row

        if (!line.empty() && line.back() == '\r') line.pop_back();

        std::vector<std::string> fields = split(line, '|');

        // Minimum required: id|type|target|message|sfxId|power
        if (fields.size() < 6)
        {
            std::cerr << "Invalid enemy move line: " << line << "\n";
            continue;
        }

        EnemyMoveDefinition move;
        move.id = fields[0];
        move.type = fields[1];
        move.target = fields[2];
        move.message = fields[3];
        move.sfxId = fields[4];

        try { move.power = std::stof(fields[5]); }
        catch (...) { move.power = 1.f; }

        // Optional durationTurns column
        if (fields.size() >= 7 && !fields[6].empty())
        {
            try { move.durationTurns = std::stoi(fields[6]); }
            catch (...) { move.durationTurns = 0; }
        }

        if (move.id.empty()) continue;

        this->moves[move.id] = move;
    }

    std::cout << "Loaded enemy moves: " << this->moves.size() << "\n";
    return true;
}

const EnemyMoveDefinition* EnemyMoveDatabase::getMove(const std::string& id) const
{
    auto it = this->moves.find(id);
    return it != this->moves.end() ? &it->second : nullptr;
}

const std::vector<EnemyMoveDefinition> EnemyMoveDatabase::getAllMoves() const
{
    std::vector<EnemyMoveDefinition> result;
    result.reserve(this->moves.size());
    for (const auto& pair : this->moves)
        result.push_back(pair.second);
    return result;
}