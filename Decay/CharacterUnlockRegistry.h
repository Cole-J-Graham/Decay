#pragma once

// ---------------------------------------------------------------------------
// CharacterUnlockRegistry
// Holds fully-constructed Character objects that have not yet been added to
// CharacterManager.  GameTriggers registers unlock handlers that call
// unlockCharacter(), which moves the character into CharacterManager and
// fires an optional notification.
//
// Usage:
//   // At startup (InitializeCharacters):
//   CharacterUnlockRegistry::getInstance().registerCharacter("SIWARD", siward);
//
//   // In GameTriggers::registerAll():
//   TriggerManager::getInstance().on("unlock_siward", []() {
//       CharacterUnlockRegistry::getInstance().unlockCharacter("SIWARD");
//   });
//
//   // At the moment of unlock (end of intro event, boss defeat, etc.):
//   TriggerManager::getInstance().fire("unlock_siward");
// ---------------------------------------------------------------------------

#include "Character.h"
#include <memory>
#include <string>
#include <unordered_map>

class CharacterUnlockRegistry
{
public:
    static CharacterUnlockRegistry& getInstance()
    {
        static CharacterUnlockRegistry instance;
        return instance;
    }

    CharacterUnlockRegistry(const CharacterUnlockRegistry&) = delete;
    CharacterUnlockRegistry& operator=(const CharacterUnlockRegistry&) = delete;

    // Store a character here before it is unlocked.
    void registerCharacter(const std::string& id, std::shared_ptr<Character> character)
    {
        pending[id] = std::move(character);
    }

    // Move a pending character into CharacterManager.
    // Safe to call multiple times — guards via GameFlags internally.
    // Returns false if the id was never registered or already unlocked.
    bool unlockCharacter(const std::string& id);

    // Returns the pending (not-yet-unlocked) character, or nullptr.
    std::shared_ptr<Character> getPending(const std::string& id) const
    {
        auto it = pending.find(id);
        return it != pending.end() ? it->second : nullptr;
    }

private:
    CharacterUnlockRegistry() = default;

    std::unordered_map<std::string, std::shared_ptr<Character>> pending;
};