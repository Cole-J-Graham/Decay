#pragma once

#include <set>
#include <string>

// ---------------------------------------------------------------------------
// GameFlags
// A simple singleton that stores a set of named flags for the lifetime of
// the game session.  No persistence yet — flags reset on restart.
// When a save system is added, serialize/deserialize this->flags.
//
// Usage:
//   GameFlags::getInstance().set("doctor_intro_played");
//   if (GameFlags::getInstance().has("doctor_intro_played")) { ... }
//   GameFlags::getInstance().clear("doctor_intro_played");  // if ever needed
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

private:
    GameFlags() = default;

    std::set<std::string> flags;
};