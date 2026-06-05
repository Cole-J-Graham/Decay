#include "MusicPlayer.h"
#include "SettingsManager.h"

MusicPlayer::MusicPlayer()
{
    this->setVolume(SettingsManager::getInstance().getMusicVolume());
}

MusicPlayer::~MusicPlayer()
{
    this->song.stop();
}

bool MusicPlayer::preload(const std::string& path)
{
    if (this->buffers.count(path) > 0) {
        return true; // already loaded
    }

    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(path)) {
        std::cerr << "MusicPlayer: failed to load \"" << path << "\"\n";
        return false;
    }

    this->buffers[path] = std::move(buffer);
    return true;
}

void MusicPlayer::play(const std::string& path)
{
    if (this->buffers.count(path) == 0) {
        std::cerr << "MusicPlayer: track not preloaded: " << path << "\n";
        return;
    }

    this->song.stop();
    this->song.setBuffer(this->buffers[path]);
    this->song.setVolume(this->volume);
    this->song.play();
    this->trackStarted = true;
}

void MusicPlayer::stop()
{
    this->song.stop();
}

bool MusicPlayer::isStopped() const
{
    return this->trackStarted && this->song.getStatus() == sf::Sound::Stopped;
}

void MusicPlayer::setVolume(float volume)
{
    if (volume < 0.f)   volume = 0.f;
    if (volume > 100.f) volume = 100.f;

    this->volume = volume;
    this->song.setVolume(this->volume);
}

float MusicPlayer::getVolume() const
{
    return this->volume;
}