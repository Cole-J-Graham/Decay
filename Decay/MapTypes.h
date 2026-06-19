#pragma once

#include <string>
#include <vector>

// Defines a single explorable area within a map (one button, one frame sequence)
struct AreaDefinition
{
    std::string id;           // e.g. "forest_entrance"
    std::string mapId;        // parent map id e.g. "forest"
    int         areaIndex;    // order within the map (0-based)
    std::string name;         // display name on button
    float       buttonX;
    float       buttonY;
    std::string framesFile;   // path to .txt file listing frame ASSET IDS (one per line),
    // each id must be registered in assets.db / AssetDatabase
};

// Defines a full map (one tab in the MapViewer)
struct MapDefinition
{
    std::string mapId;            // e.g. "forest"
    std::string name;             // display name e.g. "Forest"
    float       scale;
    std::string mapImageId;       // asset id for the background map image, registered in assets.db
    std::string unlockCondition;  // "none" = always unlocked, otherwise a mapId that must be fully explored first
};