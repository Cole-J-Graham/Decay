#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

class MusicPlayer;

// Call once after MusicPlayer is constructed to wire it up.
void MusicManager_setPlayer(MusicPlayer* player);

class MusicManager
{
public:
    static MusicManager& getInstance()
    {
        static MusicManager instance;
        return instance;
    }

    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;

    // Parse songs.db (format: ContextName|path/to/track.wav) and eagerly
    // preload every track into MusicPlayer. Call this at boot after
    // MusicManager_setPlayer() has been called.
    void loadFromFile(const std::string& path);
    void preloadAll();

    // Push a new context and start its playlist from track 0.
    // No-op if this context is already on top.
    void play(const std::string& context);

    // Replace the top context (area change within the same state).
    void transition(const std::string& context);

    // Pop the current context and resume the previous one.
    void pop();

    // Call every frame — advances the playlist when a track ends.
    void update();

    const std::string& currentContext() const
    {
        static const std::string empty;
        return this->contextStack.empty() ? empty : this->contextStack.top().name;
    }

    bool hasContext(const std::string& context) const
    {
        return this->playlists.count(context) > 0;
    }

private:
    MusicManager() = default;
    ~MusicManager() = default;

    struct ContextEntry {
        std::string name;
        int trackIndex = 0;
    };

    void playCurrentTrack();
    void stopCurrent();
    bool trackFinished() const;

    void advancePlaylist()
    {
        if (this->contextStack.empty()) return;

        ContextEntry& top = this->contextStack.top();
        const auto& playlist = this->playlists[top.name];

        if (playlist.empty()) return;

        top.trackIndex = (top.trackIndex + 1) % static_cast<int>(playlist.size());
        this->playCurrentTrack();
    }

    std::map<std::string, std::vector<std::string>> playlists;
    std::stack<ContextEntry> contextStack;
};