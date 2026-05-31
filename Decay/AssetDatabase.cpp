#include "AssetDatabase.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

AssetDatabase& AssetDatabase::getInstance()
{
    static AssetDatabase instance;
    return instance;
}

bool AssetDatabase::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open asset database: " << filePath << "\n";
        return false;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;

        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);

        std::string id;
        std::string typeText;
        std::string path;

        std::getline(ss, id, '|');
        std::getline(ss, typeText, '|');
        std::getline(ss, path);

        id = trim(id);
        typeText = trim(typeText);
        path = trim(path);

        if (id.empty() || typeText.empty() || path.empty()) {
            std::cerr << "Invalid asset database line " << lineNumber << ": " << line << "\n";
            continue;
        }

        AssetDefinition definition;
        definition.id = id;
        definition.type = parseType(typeText);
        definition.path = path;

        if (definition.type == AssetType::Unknown) {
            std::cerr << "Unknown asset type on line " << lineNumber << ": " << typeText << "\n";
            continue;
        }

        definitions[id] = definition;
    }

    std::cout << "Loaded " << definitions.size() << " asset definitions from " << filePath << "\n";

    return true;
}

bool AssetDatabase::has(const std::string& id) const
{
    return definitions.find(id) != definitions.end();
}

const AssetDefinition& AssetDatabase::getDefinition(const std::string& id) const
{
    auto it = definitions.find(id);

    if (it == definitions.end()) {
        throw std::runtime_error("Asset definition not found: " + id);
    }

    return it->second;
}

const std::string& AssetDatabase::getPath(const std::string& id) const
{
    return getDefinition(id).path;
}

sf::Font& AssetDatabase::getFont(const std::string& id)
{
    auto loaded = fonts.find(id);

    if (loaded != fonts.end()) {
        return loaded->second;
    }

    const AssetDefinition& definition = getDefinition(id);

    if (definition.type != AssetType::Font) {
        throw std::runtime_error("Asset is not a font: " + id);
    }

    sf::Font font;

    if (!font.loadFromFile(definition.path)) {
        throw std::runtime_error("Failed to load font: " + definition.path);
    }

    fonts[id] = std::move(font);
    return fonts.at(id);
}

sf::Texture& AssetDatabase::getTexture(const std::string& id)
{
    auto loaded = textures.find(id);

    if (loaded != textures.end()) {
        return loaded->second;
    }

    const AssetDefinition& definition = getDefinition(id);

    if (definition.type != AssetType::Texture) {
        throw std::runtime_error("Asset is not a texture: " + id);
    }

    sf::Texture texture;

    if (!texture.loadFromFile(definition.path)) {
        throw std::runtime_error("Failed to load texture: " + definition.path);
    }

    textures[id] = std::move(texture);
    return textures.at(id);
}

sf::SoundBuffer& AssetDatabase::getSoundBuffer(const std::string& id)
{
    auto loaded = soundBuffers.find(id);

    if (loaded != soundBuffers.end()) {
        return loaded->second;
    }

    const AssetDefinition& definition = getDefinition(id);

    if (definition.type != AssetType::Sound) {
        throw std::runtime_error("Asset is not a sound: " + id);
    }

    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(definition.path)) {
        throw std::runtime_error("Failed to load sound: " + definition.path);
    }

    soundBuffers[id] = std::move(buffer);
    return soundBuffers.at(id);
}

AssetType AssetDatabase::parseType(const std::string& typeText) const
{
    if (typeText == "font") {
        return AssetType::Font;
    }

    if (typeText == "texture") {
        return AssetType::Texture;
    }

    if (typeText == "sound") {
        return AssetType::Sound;
    }

    if (typeText == "music") {
        return AssetType::Music;
    }

    if (typeText == "text") {
        return AssetType::Text;
    }

    return AssetType::Unknown;
}

std::string AssetDatabase::trim(const std::string& input) const
{
    const std::string whitespace = " \t\r\n";

    const std::size_t start = input.find_first_not_of(whitespace);

    if (start == std::string::npos) {
        return "";
    }

    const std::size_t end = input.find_last_not_of(whitespace);

    return input.substr(start, end - start + 1);
}