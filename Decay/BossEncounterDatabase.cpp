#include "BossEncounterDatabase.h"

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

bool BossEncounterDatabase::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "BossEncounterDatabase: failed to open: " << filePath << "\n";
        return false;
    }

    this->bosses.clear();

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        if (line.rfind("mapId|", 0) == 0) continue; // header row

        // Strip trailing \r
        if (!line.empty() && line.back() == '\r') line.pop_back();

        std::vector<std::string> fields = split(line, '|');
        if (fields.size() < 5)
        {
            std::cerr << "BossEncounterDatabase: invalid line: " << line << "\n";
            continue;
        }

        BossEncounterDefinition def;
        def.mapId = fields[0];
        def.enemyId = fields[1];
        def.preFightEventPath = fields[2];
        def.defeatedFlag = fields[3];
        def.musicContext = fields[4];

        if (def.mapId.empty() || def.enemyId.empty())
        {
            std::cerr << "BossEncounterDatabase: missing mapId or enemyId: " << line << "\n";
            continue;
        }

        this->bosses[def.mapId] = def;
    }

    std::cout << "BossEncounterDatabase: loaded " << this->bosses.size() << " boss encounters.\n";
    return true;
}

const BossEncounterDefinition* BossEncounterDatabase::getBoss(const std::string& mapId) const
{
    auto it = this->bosses.find(mapId);
    return it != this->bosses.end() ? &it->second : nullptr;
}

bool BossEncounterDatabase::hasBoss(const std::string& mapId) const
{
    return this->bosses.count(mapId) > 0;
}