#include "CompanionConversationManager.h"
#include "CharacterManager.h"
#include "GameFlags.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <random>
#include <regex>

// ---------------------------------------------------------------------------
//  Public
// ---------------------------------------------------------------------------

void CompanionConversationManager::onBonfireEntered()
{
    const auto& partyMembers = CharacterManager::getInstance().getAllPartyMembers();

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> idleRoll(1, idleRollOdds);

    for (const auto& member : partyMembers)
    {
        if (!member) continue;

        const std::string& id = member->getId();
        const int level = member->getStats() ? member->getStats()->getLevel() : 0;

        scanForCharacter(id, level);

        // Idle roll — only if no level-gated conversations are already pending
        // and the character doesn't already have an idle queued
        const std::string idlePath = "Assets/Events/Companions/" + id + "/";
        const bool alreadyHasPending = hasPending(id);

        if (!alreadyHasPending && idleRoll(rng) == 1)
        {
            // Collect all non-level-gated, non-once files
            std::vector<std::string> idleFiles;

            try
            {
                for (const auto& entry : std::filesystem::directory_iterator(idlePath))
                {
                    if (!entry.is_regular_file()) continue;

                    const std::string filename = entry.path().filename().string();
                    if (parseLevelRequirement(filename) == -1 && !isOneTime(filename))
                        idleFiles.push_back(entry.path().string());
                }
            }
            catch (const std::filesystem::filesystem_error& e)
            {
                std::cerr << "CompanionConversationManager: " << e.what() << "\n";
            }

            if (!idleFiles.empty())
            {
                std::uniform_int_distribution<size_t> pick(0, idleFiles.size() - 1);
                const std::string chosen = idleFiles[pick(rng)];
                queues[id].push_back(chosen);
                std::cout << "CompanionConversationManager: idle queued for "
                    << id << ": " << chosen << "\n";
            }
        }
    }
}

bool CompanionConversationManager::hasPending(const std::string& characterId) const
{
    auto it = queues.find(characterId);
    return it != queues.end() && !it->second.empty();
}

std::string CompanionConversationManager::popNext(const std::string& characterId)
{
    auto it = queues.find(characterId);
    if (it == queues.end() || it->second.empty())
        return "";

    const std::string path = it->second.front();
    it->second.pop_front();

    // Extract filename for flag management
    const std::string filename = std::filesystem::path(path).filename().string();

    // Clear the queued flag now that it's been consumed
    GameFlags::getInstance().clear(queuedFlagKey(characterId, filename));

    // Mark one-time conversations as played so they never re-queue
    if (isOneTime(filename))
        GameFlags::getInstance().set(playedFlagKey(characterId, filename));

    std::cout << "CompanionConversationManager: popped conversation for "
        << characterId << ": " << path << "\n";
    return path;
}

// ---------------------------------------------------------------------------
//  Private
// ---------------------------------------------------------------------------

void CompanionConversationManager::scanForCharacter(
    const std::string& characterId, int characterLevel)
{
    const std::string dirPath = "Assets/Events/Companions/" + characterId + "/";

    // Collect level-gated .once. files that are eligible and not yet played/queued
    std::vector<std::pair<int, std::string>> eligible; // (level, path)

    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(dirPath))
        {
            if (!entry.is_regular_file()) continue;

            const std::string filename = entry.path().filename().string();
            const int levelReq = parseLevelRequirement(filename);

            // Skip idle files here (handled separately in onBonfireEntered)
            if (levelReq == -1) continue;

            // Skip if not yet reached the required level
            if (characterLevel < levelReq) continue;

            // Skip if already played
            if (GameFlags::getInstance().has(playedFlagKey(characterId, filename)))
                continue;

            // Skip if already queued (survived a previous bonfire entry)
            if (GameFlags::getInstance().has(queuedFlagKey(characterId, filename)))
                continue;

            // Skip if already in the in-memory queue
            auto& q = queues[characterId];
            const std::string fullPath = entry.path().string();
            if (std::find(q.begin(), q.end(), fullPath) != q.end())
                continue;

            eligible.emplace_back(levelReq, fullPath);
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "CompanionConversationManager: " << e.what() << "\n";
        return;
    }

    // Sort by level requirement so lower levels queue first (FIFO by level)
    std::sort(eligible.begin(), eligible.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });

    for (const auto& [level, path] : eligible)
    {
        const std::string filename = std::filesystem::path(path).filename().string();
        queues[characterId].push_back(path);
        GameFlags::getInstance().set(queuedFlagKey(characterId, filename));
        std::cout << "CompanionConversationManager: queued level-gated conversation for "
            << characterId << " (level " << level << "): " << path << "\n";
    }
}

int CompanionConversationManager::parseLevelRequirement(const std::string& filename) const
{
    // Matches filenames like "zin_level2.once.txt" or "zin_level10.txt"
    std::regex levelRegex("level(\\d+)", std::regex::icase);
    std::smatch match;

    if (std::regex_search(filename, match, levelRegex))
        return std::stoi(match[1].str());

    return -1; // no level requirement
}

bool CompanionConversationManager::isOneTime(const std::string& filename) const
{
    return filename.find(".once.") != std::string::npos;
}

std::string CompanionConversationManager::queuedFlagKey(
    const std::string& characterId, const std::string& filename) const
{
    return "companion_queued:" + characterId + ":" + filename;
}

std::string CompanionConversationManager::playedFlagKey(
    const std::string& characterId, const std::string& filename) const
{
    return "companion_played:" + characterId + ":" + filename;
}