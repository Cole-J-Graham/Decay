#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

class MusicPlayer;

// Free function — call once after MusicPlayer is constructed in TravelState
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

    // Load all contexts and playlists from a db file
    // Format per line: ContextName|path/to/track.wav
    void loadFromFile(const std::string& path)
    {
        std::ifstream file(path);

        if (!file.is_open()) {
            std::cerr << "MusicManager: failed to open " << path << "\n";
            return;
        }

        std::string line;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            const std::size_t sep = line.find('|');

            if (sep == std::string::npos) {
                std::cerr << "MusicManager: malformed line: " << line << "\n";
                continue;
            }

            const std::string context = line.substr(0, sep);
            const std::string trackPath = line.substr(sep + 1);

            this->playlists[context].push_back(trackPath);
            std::cout << "MusicManager: registered [" << context << "] -> " << trackPath << "\n";
        }
    }

    // Push a new context — starts its playlist from track 0
    // No-op if this context is already on top
    void play(const std::string& context)
    {
        if (this->playlists.count(context) == 0) {
            std::cerr << "MusicManager: no playlist for context: " << context << "\n";
            return;
        }

        if (!this->contextStack.empty() && this->contextStack.top().name == context) {
            return;
        }

        this->contextStack.push({ context, 0 });
        this->playCurrentTrack();
    }

    // Transition the current top to a new context (area change within same state)
    // Replaces the top rather than pushing so pop() returns to what was below
    void transition(const std::string& context)
    {
        if (this->playlists.count(context) == 0) {
            std::cerr << "MusicManager: no playlist for context: " << context << "\n";
            return;
        }

        if (!this->contextStack.empty() && this->contextStack.top().name == context) {
            return;
        }

        if (!this->contextStack.empty()) {
            this->contextStack.top() = { context, 0 };
        }
        else {
            this->contextStack.push({ context, 0 });
        }

        this->playCurrentTrack();
    }

    // Pop the current context and resume the previous one
    void pop()
    {
        if (this->contextStack.empty()) return;

        this->contextStack.pop();

        if (!this->contextStack.empty()) {
            this->playCurrentTrack();
        }
        else {
            this->stopCurrent();
        }
    }

    // Call every frame from TravelState::update() — advances playlist when track ends
    void update()
    {
        if (this->contextStack.empty()) return;

        if (this->trackFinished()) {
            this->advancePlaylist();
        }
    }

    const std::string& currentContext() const
    {
        static const std::string empty = "";
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

        // Loop back to start when we reach the end
        top.trackIndex = (top.trackIndex + 1) % static_cast<int>(playlist.size());
        this->playCurrentTrack();
    }

    std::map<std::string, std::vector<std::string>> playlists;
    std::stack<ContextEntry> contextStack;
};