#include "MusicManager.h"
#include "MusicPlayer.h"

static MusicPlayer* gMusicPlayer = nullptr;

void MusicManager_setPlayer(MusicPlayer* player)
{
    gMusicPlayer = player;
}

void MusicManager::loadFromFile(const std::string& path)
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
        if (sep == std::string::npos) continue;

        const std::string context = line.substr(0, sep);
        const std::string trackPath = line.substr(sep + 1);
        this->playlists[context].push_back(trackPath);
    }

    std::cout << "MusicManager: parsed playlists from " << path << "\n";
}

void MusicManager::preloadAll()
{
    if (gMusicPlayer == nullptr) {
        std::cerr << "MusicManager: no player set, cannot preload\n";
        return;
    }

    int count = 0;
    for (auto& [context, playlist] : this->playlists) {
        for (auto& trackPath : playlist) {
            if (gMusicPlayer->preload(trackPath)) count++;
        }
    }

    std::cout << "MusicManager: preloaded " << count << " tracks\n";
}

void MusicManager::play(const std::string& context)
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

void MusicManager::transition(const std::string& context)
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

void MusicManager::pop()
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

void MusicManager::update()
{
    if (this->contextStack.empty()) return;

    if (this->trackFinished()) {
        this->advancePlaylist();
    }
}

void MusicManager::playCurrentTrack()
{
    if (this->contextStack.empty() || gMusicPlayer == nullptr) return;

    const ContextEntry& top = this->contextStack.top();
    const auto& playlist = this->playlists[top.name];

    if (playlist.empty()) return;

    const std::string& path = playlist[top.trackIndex];

    std::cout << "MusicManager: playing [" << top.name << "] track "
        << top.trackIndex << " -> " << path << "\n";

    gMusicPlayer->play(path);
}

void MusicManager::stopCurrent()
{
    if (gMusicPlayer != nullptr) {
        gMusicPlayer->stop();
    }
}

bool MusicManager::trackFinished() const
{
    if (gMusicPlayer == nullptr) return false;
    return gMusicPlayer->isStopped();
}