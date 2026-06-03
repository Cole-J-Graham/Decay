#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

// ---------------------------------------------------------------------------
// TriggerManager
// A fire/listen singleton.  States call fire() at natural transition points
// and know nothing else.  All "what happens when X fires" logic lives in
// GameTriggers.cpp, registered once at startup via registerAll().
//
// Usage:
//   // Register (in GameTriggers::registerAll):
//   TriggerManager::getInstance().on("castle_first_visit", []() { ... });
//
//   // Fire (from a state at a natural transition point):
//   TriggerManager::getInstance().fire("castle_first_visit");
//
// Multiple listeners can be registered for the same key.
// ---------------------------------------------------------------------------

class TriggerManager
{
public:
    static TriggerManager& getInstance()
    {
        static TriggerManager instance;
        return instance;
    }

    // Non-copyable
    TriggerManager(const TriggerManager&) = delete;
    TriggerManager& operator=(const TriggerManager&) = delete;

    // Register a callback for a trigger key.
    // Multiple calls with the same key append additional listeners.
    void on(const std::string& key, std::function<void()> callback);

    // Fire all listeners registered for this key.
    // Safe to call even if no listeners are registered.
    void fire(const std::string& key);

private:
    TriggerManager() = default;

    std::unordered_map<std::string, std::vector<std::function<void()>>> listeners;
};