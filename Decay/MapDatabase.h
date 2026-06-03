#pragma once

#include "MapTypes.h"

#include <string>
#include <unordered_map>
#include <vector>

class MapDatabase
{
public:
    static MapDatabase& getInstance();

    MapDatabase(const MapDatabase&) = delete;
    MapDatabase& operator=(const MapDatabase&) = delete;

    bool loadFromFile(const std::string& filePath);

    // Returns nullptr if not found
    const MapDefinition* getMap(const std::string& mapId) const;
    const AreaDefinition* getArea(const std::string& areaId) const;

    // Returns all areas belonging to a map, sorted by areaIndex
    std::vector<const AreaDefinition*> getAreasForMap(const std::string& mapId) const;

    // Returns all maps in insertion order (i.e. file order)
    const std::vector<std::string>& getMapOrder() const;

private:
    MapDatabase() = default;

private:
    std::unordered_map<std::string, MapDefinition>  maps;
    std::unordered_map<std::string, AreaDefinition> areas;

    // Preserves the order maps were defined in the .db file
    std::vector<std::string> mapOrder;
};