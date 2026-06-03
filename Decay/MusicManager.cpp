#include "MusicManager.h"
#include "MusicPlayer.h"

static MusicPlayer* gMusicPlayer = nullptr;

void MusicManager_setPlayer(MusicPlayer* player)
{
    gMusicPlayer = player;
}

void MusicManager::playCurrentTrack()
{
    if (this->contextStack.empty()) return;
    if (gMusicPlayer == nullptr) return;

    const ContextEntry& top = this->contextStack.top();
    const auto& playlist = this->playlists[top.name];

    if (playlist.empty()) return;

    const std::string& path = playlist[top.trackIndex];

    std::cout << "MusicManager: playing [" << top.name << "] track "
        << top.trackIndex << " -> " << path << "\n";

    gMusicPlayer->playDirect(path);
}

void MusicManager::stopCurrent()
{
    if (gMusicPlayer != nullptr) {
        gMusicPlayer->stopMusic();
    }
}

bool MusicManager::trackFinished() const
{
    if (gMusicPlayer == nullptr) return false;
    return gMusicPlayer->isStopped();
}