#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <string>

enum class AssetType
{
    Font,
    Texture,
    Sound,
    Music,
    Text,
    Unknown
};

struct AssetDefinition
{
    std::string id;
    AssetType type = AssetType::Unknown;
    std::string path;
};

class AssetDatabase
{
public:
    static AssetDatabase& getInstance();

    bool loadFromFile(const std::string& filePath);

    bool has(const std::string& id) const;

    const AssetDefinition& getDefinition(const std::string& id) const;
    const std::string& getPath(const std::string& id) const;

    sf::Font& getFont(const std::string& id);
    sf::Texture& getTexture(const std::string& id);
    sf::SoundBuffer& getSoundBuffer(const std::string& id);

private:
    AssetDatabase() = default;

    AssetType parseType(const std::string& typeText) const;
    std::string trim(const std::string& input) const;

private:
    std::map<std::string, AssetDefinition> definitions;

    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
};