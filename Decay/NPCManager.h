#pragma once
#include "NPC.h"
#include <unordered_map>
#include <memory>
#include <string>

class NPCManager
{
public:
    NPCManager(const NPCManager&) = delete;
    NPCManager& operator=(const NPCManager&) = delete;

    static NPCManager& getInstance()
    {
        static NPCManager instance;
        return instance;
    }

    void addNPC(const std::string& id, std::unique_ptr<NPC> npc)
    {
        npcs[id] = std::move(npc);
    }

    NPC* getNPC(const std::string& id)
    {
        auto it = npcs.find(id);
        if (it != npcs.end()) return it->second.get();
        return nullptr;
    }

private:
    NPCManager() = default;
    ~NPCManager() = default;
    std::unordered_map<std::string, std::unique_ptr<NPC>> npcs;
};