#pragma once

// ---------------------------------------------------------------------------
// BossEncounterDatabase
//
// Maps a specific map node id to a boss encounter definition.
// Loaded from Assets/Data/boss_encounters.db.
//
// File format (pipe-delimited, # = comment):
//   mapId | enemyId | preFightEventPath | defeatedFlag | musicContext
//
// Example:
//   FOREST_8|forest_boss|Assets/Events/Bosses/forest_boss.txt|forest_boss_defeated|combat_boss
//
// Fields:
//   mapId           — the exact map node id returned by MapComponent::getCurrentMapId()
//   enemyId         — id matching an entry in enemies.db
//   preFightEventPath — path to an event file played before combat (empty = no cutscene)
//   defeatedFlag    — GameFlag set when this boss is defeated; prevents re-triggering
//   musicContext    — MusicManager context to play during this fight (empty = use default)
// ---------------------------------------------------------------------------

#include <string>
#include <unordered_map>

struct BossEncounterDefinition
{
    std::string mapId;
    std::string enemyId;
    std::string preFightEventPath;  // empty = no pre-fight event
    std::string defeatedFlag;
    std::string musicContext;       // empty = fall back to normal combat music
};

class BossEncounterDatabase
{
public:
    static BossEncounterDatabase& getInstance()
    {
        static BossEncounterDatabase instance;
        return instance;
    }

    BossEncounterDatabase(const BossEncounterDatabase&) = delete;
    BossEncounterDatabase& operator=(const BossEncounterDatabase&) = delete;

    bool loadFromFile(const std::string& filePath);

    // Returns nullptr if no boss is defined for this map node.
    const BossEncounterDefinition* getBoss(const std::string& mapId) const;

    bool hasBoss(const std::string& mapId) const;

private:
    BossEncounterDatabase() = default;

    std::unordered_map<std::string, BossEncounterDefinition> bosses;
};