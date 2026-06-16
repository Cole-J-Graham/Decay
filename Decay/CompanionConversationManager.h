#pragma once

// ---------------------------------------------------------------------------
// CompanionConversationManager
//
// Manages per-character conversation queues for bonfire interactions.
//
// File conventions (under Assets/Events/Companions/<CHARACTER_ID>/):
//   zin_level2.once.txt   — queued when Zin reaches level >= 2, plays once ever
//   zin_level5.once.txt   — queued when Zin reaches level >= 5, plays once ever
//   zin_idle.txt          — no level gate, rare random chance to queue on bonfire entry
//
// Queue behaviour:
//   - FIFO per character. Level-gated .once. files are added in level order.
//   - Idle files have a 1-in-8 chance per character per bonfire entry, but
//     only one idle file queues at a time (no stacking).
//   - Consuming a conversation pops the front of the queue and sets a
//     GameFlag so it never re-queues (for .once. files).
//
// Usage (call once per bonfire entry):
//   CompanionConversationManager::getInstance().onBonfireEntered();
//
// Usage (on slot click):
//   std::string path = CompanionConversationManager::getInstance().popNext("ZIN");
//   // empty string = nothing queued
//
// Usage (for pending indicator):
//   bool pending = CompanionConversationManager::getInstance().hasPending("ZIN");
// ---------------------------------------------------------------------------

#include <deque>
#include <string>
#include <unordered_map>

class CompanionConversationManager
{
public:
    static CompanionConversationManager& getInstance()
    {
        static CompanionConversationManager instance;
        return instance;
    }

    CompanionConversationManager(const CompanionConversationManager&) = delete;
    CompanionConversationManager& operator=(const CompanionConversationManager&) = delete;

    // Call each time the player enters the bonfire.
    // Scans each active party member's conversation directory,
    // queues newly eligible level-gated files and rolls idle files.
    void onBonfireEntered();

    // Returns true if this character has at least one conversation queued.
    bool hasPending(const std::string& characterId) const;

    // Pops and returns the path of the next queued conversation for this
    // character. Returns empty string if nothing is queued.
    std::string popNext(const std::string& characterId);

private:
    CompanionConversationManager() = default;

    // Scans one character's directory and queues eligible files.
    void scanForCharacter(const std::string& characterId, int characterLevel);

    // Parses the level requirement out of a filename like "zin_level5.once.txt".
    // Returns -1 if no level requirement is found (idle file).
    int parseLevelRequirement(const std::string& filename) const;

    // Returns true if filename contains ".once."
    bool isOneTime(const std::string& filename) const;

    // GameFlag key for a queued conversation (so it survives bonfire re-entries)
    std::string queuedFlagKey(const std::string& characterId,
        const std::string& filename) const;

    // GameFlag key for a played one-time conversation
    std::string playedFlagKey(const std::string& characterId,
        const std::string& filename) const;

    // Per-character FIFO queues. Key = character id, value = ordered file paths.
    std::unordered_map<std::string, std::deque<std::string>> queues;

    // Idle roll odds: 1-in-N chance per character per bonfire entry.
    static constexpr int idleRollOdds = 8;
};