#include "SfxManager.h"

SfxManager& SfxManager::getInstance()
{
    static SfxManager instance;
    return instance;
}

bool SfxManager::loadFromFile(const std::string& databasePath)
{
    std::ifstream file(databasePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open SFX database: " << databasePath << "\n";
        return false;
    }

    std::string line;
    int loadedCount = 0;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        if (line[0] == '#') {
            continue;
        }

        std::vector<std::string> parts = this->splitLine(line, '|');

        if (parts.size() < 2) {
            std::cerr << "Invalid SFX database line: " << line << "\n";
            continue;
        }

        const std::string id = parts[0];
        const std::string path = parts[1];

        if (id.empty() || path.empty()) {
            std::cerr << "Invalid SFX entry. ID or path empty: " << line << "\n";
            continue;
        }

        if (this->loadSound(id, path)) {
            this->definitions[id] = SfxDefinition{ id, path };
            loadedCount++;
        }
    }

    std::cout << "Loaded " << loadedCount << " SFX definitions from " << databasePath << "\n";

    return true;
}

bool SfxManager::loadSound(const std::string& id, const std::string& path)
{
    if (this->buffers.count(id) > 0) {
        std::cerr << "Duplicate SFX id skipped: " << id << "\n";
        return false;
    }

    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(path)) {
        std::cerr << "Failed to load SFX: " << id << " from " << path << "\n";
        return false;
    }

    this->buffers[id] = buffer;
    return true;
}

void SfxManager::update()
{
    this->activeSounds.remove_if([](const sf::Sound& sound) {
        return sound.getStatus() == sf::Sound::Stopped;
        });
}

bool SfxManager::play(const std::string& id)
{
    return this->play(id, 100.f, 1.f);
}

bool SfxManager::play(const std::string& id, float volume)
{
    return this->play(id, volume, 1.f);
}

bool SfxManager::play(const std::string& id, float volume, float pitch)
{
    auto it = this->buffers.find(id);

    if (it == this->buffers.end()) {
        std::cerr << "SFX id not found: " << id << "\n";
        return false;
    }

    this->activeSounds.emplace_back();

    sf::Sound& sound = this->activeSounds.back();
    sound.setBuffer(it->second);
    sound.setVolume((volume / 100.f) * this->masterVolume);
    sound.setPitch(pitch);
    sound.play();

    return true;
}

void SfxManager::setMasterVolume(float volume)
{
    if (volume < 0.f) {
        volume = 0.f;
    }

    if (volume > 100.f) {
        volume = 100.f;
    }

    this->masterVolume = volume;
}

float SfxManager::getMasterVolume() const
{
    return this->masterVolume;
}

bool SfxManager::hasSound(const std::string& id) const
{
    return this->buffers.count(id) > 0;
}

void SfxManager::stopAll()
{
    for (auto& sound : this->activeSounds) {
        sound.stop();
    }

    this->activeSounds.clear();
}

std::vector<std::string> SfxManager::splitLine(const std::string& line, char delimiter) const
{
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        parts.push_back(item);
    }

    return parts;
}