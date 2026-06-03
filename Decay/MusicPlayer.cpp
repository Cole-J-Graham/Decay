#include "MusicPlayer.h"
#include "SettingsManager.h"

// Constructors and Destructors
MusicPlayer::MusicPlayer(const std::string& music_list)
{
    this->x = 1370;
    this->y = 74;

    this->hidden = true;
    this->fileRead = false;
    this->bufferId = 0;
    this->currentBufferId = 0;
    this->musicList = music_list;

    this->readFile(this->musicList);
    this->setVolume(SettingsManager::getInstance().getMusicVolume());
}

MusicPlayer::~MusicPlayer()
{
    this->song.stop();
}

// Core Functions
bool MusicPlayer::readFile(const std::string& input)
{
    std::ifstream file(input);

    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << input << std::endl;
        return false;
    }

    if (this->fileRead) {
        return true;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        const int id = this->bufferId;

        // Lazy load: only store the file path here. Do NOT load the sound yet.
        this->songNames[id] = line;

        std::cout << "Song path registered: " << id << " -> " << line << "\n";

        this->bufferId++;
    }

    std::cout << "Reached end of file.\n";
    this->fileRead = true;

    return true;
}

bool MusicPlayer::loadSound(int id)
{
    if (this->buffer.count(id) > 0) {
        return true;
    }

    if (this->songNames.count(id) <= 0) {
        std::cerr << "Cannot load sound. No song path registered for ID " << id << std::endl;
        return false;
    }

    const std::string& filename = this->songNames[id];

    sf::SoundBuffer soundBuffer;

    if (!soundBuffer.loadFromFile(filename)) {
        std::cerr << "Error loading sound with ID " << id << " from file " << filename << std::endl;
        return false;
    }

    this->buffer[id] = soundBuffer;

    std::cout << "Loaded sound on demand: " << id << " -> " << filename << "\n";

    return true;
}

// Music Player Functions
bool MusicPlayer::playSong(int id)
{
    if (id < 0 || id >= this->bufferId) return false;
    if (!this->loadSound(id)) return false;

    this->song.stop();
    this->song.setBuffer(this->buffer[id]);
    this->song.setVolume(this->volume);
    this->song.play();
    this->trackStarted = true;

    return true;
}

void MusicPlayer::playDirect(const std::string& path)
{
    // Find the id for this path, or load it on demand
    int targetId = -1;

    for (auto& pair : this->songNames) {
        if (pair.second == path) {
            targetId = pair.first;
            break;
        }
    }

    if (targetId == -1) {
        // Register it dynamically
        targetId = this->bufferId;
        this->songNames[targetId] = path;
        this->bufferId++;
    }

    this->playSong(targetId);
}

void MusicPlayer::stopMusic()
{
    this->song.stop();
}

void MusicManager_setPlayer(MusicPlayer* player);

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