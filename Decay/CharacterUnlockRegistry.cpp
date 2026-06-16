#include "CharacterUnlockRegistry.h"
#include "CharacterManager.h"
#include "GameFlags.h"
#include "GameTriggers.h"

#include <iostream>

bool CharacterUnlockRegistry::unlockCharacter(const std::string& id)
{
    const std::string flag = "character_unlocked_" + id;

    if (GameFlags::getInstance().has(flag))
    {
        // Already unlocked — make sure they're in CharacterManager
        // (handles the save-load re-add path).
        auto it = pending.find(id);
        if (it != pending.end() && it->second)
            CharacterManager::getInstance().addCharacter(id, it->second);
        return true;
    }

    auto it = pending.find(id);
    if (it == pending.end() || !it->second)
    {
        std::cerr << "CharacterUnlockRegistry: no pending character registered for id: " << id << "\n";
        return false;
    }

    CharacterManager::getInstance().addCharacter(id, it->second);
    GameFlags::getInstance().set(flag);

    GameTriggers::showNotification("New companion unlocked: " + id, 6.f);
    std::cout << "CharacterUnlockRegistry: unlocked character: " << id << "\n";
    return true;
}