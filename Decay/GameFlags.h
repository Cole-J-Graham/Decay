#pragma once

#include <set>
#include <string>

// ---------------------------------------------------------------------------
// GameFlags
// A simple singleton that stores a set of named flags for the lifetime of
// the game session.
//
// Usage:
//   GameFlags::getInstance().set("doctor_intro_played");
//   if (GameFlags::getInstance().has("doctor_intro_played")) { ... }
//   GameFlags::getInstance().clear("doctor_intro_played");  // if ever needed
//
// Save/Load: getAllFlags()/setAll() let SaveManager snapshot and restore
// the full flag set as the [FLAGS] section of a save file.
// ---------------------------------------------------------------------------

class GameFlags
{
public:
    static GameFlags& getInstance()
    {
        static GameFlags instance;
        return instance;
    }

    // Non-copyable
    GameFlags(const GameFlags&) = delete;
    GameFlags& operator=(const GameFlags&) = delete;

    void set(const std::string& flag) { this->flags.insert(flag); }
    bool has(const std::string& flag) const { return this->flags.count(flag) > 0; }
    void clear(const std::string& flag) { this->flags.erase(flag); }
    void clearAll() { this->flags.clear(); }

    // Save/Load support
    const std::set<std::string>& getAllFlags() const { return this->flags; }
    void setAll(const std::set<std::string>& savedFlags) { this->flags = savedFlags; }

private:
    GameFlags() = default;

    std::set<std::string> flags;
};