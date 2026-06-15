#include "SaveManager.h"
#include "GameFlags.h"
#include "Inventory.h"
#include "CharacterManager.h"
#include "MapComponent.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <ctime>
#include <iostream>

namespace
{
    std::vector<std::string> splitOnPipe(const std::string& line)
    {
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, '|')) {
            fields.push_back(field);
        }
        return fields;
    }

    std::string stripCarriageReturn(std::string line)
    {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        return line;
    }
}

// ---------------------------------------------------------------------------
// Paths
// ---------------------------------------------------------------------------

std::string SaveManager::slotPath(int slot) const
{
    return "Assets/Saves/slot" + std::to_string(slot) + ".sav";
}

// ---------------------------------------------------------------------------
// Save
// ---------------------------------------------------------------------------

bool SaveManager::saveToSlot(int slot, MapComponent* map)
{
    if (slot < 0 || slot >= maxSlots) return false;

    std::filesystem::create_directories("Assets/Saves");

    std::ofstream file(this->slotPath(slot));
    if (!file.is_open()) {
        std::cerr << "SaveManager: failed to open slot " << slot << " for writing\n";
        return false;
    }

    // [META]
    file << "[META]\n";
    file << "location|" << (map ? map->getCurrentMapId() : "") << "\n";

    {
        std::time_t now = std::time(nullptr);
        std::tm tmNow{};
#if defined(_MSC_VER)
        localtime_s(&tmNow, &now);
#else
        tmNow = *std::localtime(&now);
#endif
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tmNow);
        file << "timestamp|" << buf << "\n";
    }
    file << "\n";

    // [UNLOCKED_MAPS]
    file << "[UNLOCKED_MAPS]\n";
    if (map) {
        for (const auto& id : map->getUnlockedMapIds()) {
            file << id << "\n";
        }
    }
    file << "\n";

    // [FLAGS]
    file << "[FLAGS]\n";
    for (const auto& flag : GameFlags::getInstance().getAllFlags()) {
        file << flag << "\n";
    }
    file << "\n";

    // [INVENTORY]
    file << "[INVENTORY]\n";
    file << "GOLD|" << Inventory::getInstance().getGold() << "\n";
    for (const auto& stack : Inventory::getInstance().getAllStacks()) {
        file << stack.itemId << "|" << stack.quantity << "\n";
    }
    file << "\n";

    // [PARTY] — slot index | character id, so empty slots don't break ordering
    file << "[PARTY]\n";
    {
        const auto& members = CharacterManager::getInstance().getParty().getAllCharacters();
        for (int i = 0; i < static_cast<int>(members.size()); ++i) {
            if (members[i]) {
                file << i << "|" << members[i]->getId() << "\n";
            }
        }
    }
    file << "\n";

    // [CHARACTER:ID] — one block per registered character, generic over
    // however many exist and however many stats each has.
    for (const auto& pair : CharacterManager::getInstance().getAllCharacters()) {
        const auto& character = pair.second;
        if (!character) continue;

        file << "[CHARACTER:" << pair.first << "]\n";
        file << "hp|" << character->getHp() << "|" << character->getHpMax() << "\n";
        file << "damage|" << character->getDamage() << "\n";
        file << "defense|" << character->getDefense() << "\n";
        file << "healing|" << character->getHealing() << "\n";

        auto& stats = character->getStats();
        if (stats) {
            file << "level|" << stats->getLevel() << "\n";
            file << "exp|" << stats->getExp() << "\n";
            file << "sp|" << stats->getSp() << "\n";

            for (const auto& key : stats->getStatKeys()) {
                file << "stat|" << key << "|" << stats->getStatCount(key) << "\n";
            }
        }

        // ASSUMPTION: Character::getMoveMp() returns an iterable
        // map<string,int> of moveId -> mp cost. If the real signature
        // differs, this loop (and the moveMp restore case below) is the
        // only thing that needs adjusting.
        for (const auto& mp : character->getAllMoveMp()) {
            file << "moveMp|" << mp.first << "|" << mp.second << "\n";
        }

        file << "\n";
    }

    return true;
}

// ---------------------------------------------------------------------------
// Load
// ---------------------------------------------------------------------------

bool SaveManager::loadFromSlot(int slot, MapComponent* map)
{
    if (slot < 0 || slot >= maxSlots) return false;

    std::ifstream file(this->slotPath(slot));
    if (!file.is_open()) {
        std::cerr << "SaveManager: slot " << slot << " not found\n";
        return false;
    }

    // Reset destination state before applying the save. Characters
    // themselves are mutated in place below (not replaced), so existing
    // shared_ptrs held by Party/CombatState/etc. remain valid.
    GameFlags::getInstance().clearAll();
    Inventory::getInstance().clear();
    Inventory::getInstance().setGold(0);
    CharacterManager::getInstance().getParty().clear();

    this->pendingMapStateValid = false;
    this->pendingMapId.clear();
    this->pendingUnlockedMapIds.clear();

    enum class Section { None, Meta, UnlockedMaps, Flags, Inventory, Party, Character };
    Section section = Section::None;
    std::shared_ptr<Character> currentCharacter;

    std::string rawLine;
    while (std::getline(file, rawLine))
    {
        const std::string line = stripCarriageReturn(rawLine);
        if (line.empty()) continue;

        if (line[0] == '[')
        {
            if (line.rfind("[CHARACTER:", 0) == 0)
            {
                section = Section::Character;
                const std::string charId = line.substr(11, line.size() - 12); // strip "[CHARACTER:" and "]"
                currentCharacter = CharacterManager::getInstance().getCharacter(charId);

                if (!currentCharacter) {
                    std::cerr << "SaveManager: unknown character id in save: " << charId << "\n";
                }
            }
            else if (line == "[META]")          section = Section::Meta;
            else if (line == "[UNLOCKED_MAPS]")  section = Section::UnlockedMaps;
            else if (line == "[FLAGS]")          section = Section::Flags;
            else if (line == "[INVENTORY]")      section = Section::Inventory;
            else if (line == "[PARTY]")          section = Section::Party;
            else                                  section = Section::None;

            continue;
        }

        const std::vector<std::string> fields = splitOnPipe(line);

        switch (section)
        {
        case Section::Meta:
            if (fields.size() >= 2 && fields[0] == "location") {
                this->pendingMapId = fields[1];
            }
            break;

        case Section::UnlockedMaps:
            this->pendingUnlockedMapIds.push_back(line);
            break;

        case Section::Flags:
            GameFlags::getInstance().set(line);
            break;

        case Section::Inventory:
            if (fields.size() >= 2) {
                if (fields[0] == "GOLD") {
                    Inventory::getInstance().setGold(std::stoi(fields[1]));
                }
                else {
                    Inventory::getInstance().addItem(fields[0], std::stoi(fields[1]));
                }
            }
            break;

        case Section::Party:
            if (fields.size() >= 2) {
                const int slotIndex = std::stoi(fields[0]);
                auto member = CharacterManager::getInstance().getCharacter(fields[1]);
                if (member) {
                    CharacterManager::getInstance().getParty().addToSlot(slotIndex, member);
                }
            }
            break;

        case Section::Character:
            if (!currentCharacter || fields.empty()) break;

            if (fields[0] == "hp" && fields.size() >= 3) {
                currentCharacter->getHp() = std::stof(fields[1]);
                currentCharacter->getHpMax() = std::stof(fields[2]);
            }
            else if (fields[0] == "damage" && fields.size() >= 2) {
                currentCharacter->getDamage() = std::stof(fields[1]);
            }
            else if (fields[0] == "defense" && fields.size() >= 2) {
                currentCharacter->getDefense() = std::stof(fields[1]);
            }
            else if (fields[0] == "healing" && fields.size() >= 2) {
                currentCharacter->getHealing() = std::stof(fields[1]);
            }
            else if (fields[0] == "level" && fields.size() >= 2) {
                if (currentCharacter->getStats())
                    currentCharacter->getStats()->setLevel(std::stoi(fields[1]));
            }
            else if (fields[0] == "exp" && fields.size() >= 2) {
                if (currentCharacter->getStats())
                    currentCharacter->getStats()->setExp(std::stof(fields[1]));
            }
            else if (fields[0] == "sp" && fields.size() >= 2) {
                if (currentCharacter->getStats())
                    currentCharacter->getStats()->setSp(std::stoi(fields[1]));
            }
            else if (fields[0] == "stat" && fields.size() >= 3) {
                if (currentCharacter->getStats())
                    currentCharacter->getStats()->setStatCount(fields[1], std::stoi(fields[2]));
            }
            else if (fields[0] == "moveMp" && fields.size() >= 3) {
                // ASSUMPTION: see saveToSlot's moveMp comment.
                currentCharacter->setMoveMp(fields[1], std::stoi(fields[2]));
            }
            break;

        default:
            break;
        }
    }

    // Refresh HP labels (in-world + stats panel) now that hp/hpMax have
    // been restored for whichever characters were in the save.
    for (auto& pair : CharacterManager::getInstance().getAllCharacters()) {
        if (pair.second) pair.second->updateText();
    }

    // Apply map/unlock state immediately if we have a live MapComponent
    // (in-game load from the pause menu). Otherwise stash it — TravelState
    // applies it once its MapComponent exists (main-menu load).
    if (map) {
        this->applyPendingMapState(map);
    }
    else {
        this->pendingMapStateValid = !this->pendingMapId.empty();
    }

    return true;
}

// ---------------------------------------------------------------------------
// Pending map state
// ---------------------------------------------------------------------------

void SaveManager::applyPendingMapState(MapComponent* map)
{
    if (!map) return;

    if (!this->pendingUnlockedMapIds.empty()) {
        map->setUnlockedMapIds(this->pendingUnlockedMapIds);
    }
    if (!this->pendingMapId.empty()) {
        map->setCurrentMapById(this->pendingMapId);
    }

    this->pendingMapStateValid = false;
    this->pendingMapId.clear();
    this->pendingUnlockedMapIds.clear();
}

// ---------------------------------------------------------------------------
// Slot summary (for the slot picker UI)
// ---------------------------------------------------------------------------

SaveManager::SlotSummary SaveManager::getSlotSummary(int slot) const
{
    SlotSummary summary;
    if (slot < 0 || slot >= maxSlots) return summary;

    std::ifstream file(this->slotPath(slot));
    if (!file.is_open()) return summary;

    summary.exists = true;

    enum class Section { None, Meta, Character };
    Section section = Section::None;

    std::string rawLine;
    while (std::getline(file, rawLine))
    {
        const std::string line = stripCarriageReturn(rawLine);
        if (line.empty()) continue;

        if (line[0] == '[')
        {
            if (line.rfind("[CHARACTER:", 0) == 0) section = Section::Character;
            else if (line == "[META]")             section = Section::Meta;
            else                                    section = Section::None;
            continue;
        }

        const std::vector<std::string> fields = splitOnPipe(line);
        if (fields.size() < 2) continue;

        if (section == Section::Meta) {
            if (fields[0] == "location")  summary.location = fields[1];
            else if (fields[0] == "timestamp") summary.timestamp = fields[1];
        }
        else if (section == Section::Character && fields[0] == "level") {
            summary.partyLevel = std::max(summary.partyLevel, std::stoi(fields[1]));
        }
    }

    return summary;
}