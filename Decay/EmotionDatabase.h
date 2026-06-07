#pragma once
#include <string>

// ============================================================
//  EmotionDatabase
//  Loads emotion portrait definitions for both NPCs and
//  Characters from a flat data file, registering them via
//  NPCManager and CharacterManager respectively.
//  Must load after InitializeCharacters has run.
// ============================================================

class EmotionDatabase
{
public:
    static EmotionDatabase& getInstance();
    bool loadFromFile(const std::string& filePath);

private:
    EmotionDatabase() = default;
    ~EmotionDatabase() = default;
    EmotionDatabase(const EmotionDatabase&) = delete;
    EmotionDatabase& operator=(const EmotionDatabase&) = delete;
};