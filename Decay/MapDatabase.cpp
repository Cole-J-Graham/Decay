#include "MapDatabase.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

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

    // Which section we're currently parsing
    enum class Section { None, Maps, Areas };

    Section parseSectionHeader(const std::string& line)
    {
        if (line == "[MAPS]")  return Section::Maps;
        if (line == "[AREAS]") return Section::Areas;
        return Section::None;
    }
}

MapDatabase& MapDatabase::getInstance()
{
    static MapDatabase instance;
    return instance;
}

bool MapDatabase::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open map database: " << filePath << "\n";
        return false;
    }

    this->maps.clear();
    this->areas.clear();
    this->mapOrder.clear();

    Section currentSection = Section::None;
    std::string line;

    while (std::getline(file, line)) {
        // Strip trailing \r for Windows line endings
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty())       continue;
        if (line[0] == '#')     continue;  // comment

        // Section header
        if (line[0] == '[') {
            currentSection = parseSectionHeader(line);
            continue;
        }

        // Column header rows
        if (line.rfind("id|", 0) == 0) continue;

        std::vector<std::string> fields = splitKeepEmpty(line, '|');

        // ------------------------------------------------------------------
        // MAPS:  id | name | scale | map_image_id | unlock_condition
        // map_image_id is an asset id registered in assets.db, not a path.
        // ------------------------------------------------------------------
        if (currentSection == Section::Maps) {
            if (fields.size() < 5) {
                std::cerr << "MapDatabase: invalid map line (need 5 fields): " << line << "\n";
                continue;
            }

            MapDefinition def;
            def.mapId = fields[0];
            def.name = fields[1];
            def.scale = std::stof(fields[2]);
            def.mapImageId = fields[3];
            def.unlockCondition = fields[4];

            if (def.mapId.empty()) {
                std::cerr << "MapDatabase: map missing id: " << line << "\n";
                continue;
            }

            this->maps[def.mapId] = def;
            this->mapOrder.push_back(def.mapId);
        }

        // ------------------------------------------------------------------
        // AREAS: id | map_id | area_index | name | button_x | button_y | frames_file
        // ------------------------------------------------------------------
        else if (currentSection == Section::Areas) {
            if (fields.size() < 7) {
                std::cerr << "MapDatabase: invalid area line (need 7 fields): " << line << "\n";
                continue;
            }

            AreaDefinition def;
            def.id = fields[0];
            def.mapId = fields[1];
            def.areaIndex = std::stoi(fields[2]);
            def.name = fields[3];
            def.buttonX = std::stof(fields[4]);
            def.buttonY = std::stof(fields[5]);
            def.framesFile = fields[6];

            if (def.id.empty() || def.mapId.empty()) {
                std::cerr << "MapDatabase: area missing id or map_id: " << line << "\n";
                continue;
            }

            this->areas[def.id] = def;
        }
    }

    std::cout << "MapDatabase: loaded " << this->maps.size() << " maps, "
        << this->areas.size() << " areas\n";
    return true;
}

const MapDefinition* MapDatabase::getMap(const std::string& mapId) const
{
    auto it = this->maps.find(mapId);
    if (it == this->maps.end()) return nullptr;
    return &it->second;
}

const AreaDefinition* MapDatabase::getArea(const std::string& areaId) const
{
    auto it = this->areas.find(areaId);
    if (it == this->areas.end()) return nullptr;
    return &it->second;
}

std::vector<const AreaDefinition*> MapDatabase::getAreasForMap(const std::string& mapId) const
{
    std::vector<const AreaDefinition*> result;

    for (const auto& pair : this->areas) {
        if (pair.second.mapId == mapId) {
            result.push_back(&pair.second);
        }
    }

    // Sort by areaIndex so buttons always appear in authored order
    std::sort(result.begin(), result.end(), [](const AreaDefinition* a, const AreaDefinition* b) {
        return a->areaIndex < b->areaIndex;
        });

    return result;
}

const std::vector<std::string>& MapDatabase::getMapOrder() const
{
    return this->mapOrder;
}