#include"Character.h"
#include <memory>
#include <unordered_map>
#include <string>

class CharacterManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Character>> characters;

    // Private constructor for singleton pattern
    CharacterManager() {}

public:
    // Disable copy constructor and assignment operator
    CharacterManager(const CharacterManager&) = delete;
    CharacterManager& operator=(const CharacterManager&) = delete;

    // Access the singleton instance
    static CharacterManager& getInstance() {
        static CharacterManager instance;
        return instance;
    }

    // Create and add a new character
    void addCharacter(const std::string& id, const std::shared_ptr<Character>& character) {
        characters[id] = character;
    }

    // Get a character by ID
    std::shared_ptr<Character> getCharacter(const std::string& id) {
        auto it = characters.find(id);
        if (it != characters.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Update all characters
    void updateAll(const sf::Vector2f mousePos) {
        for (auto& pair : characters) {
            pair.second->update(mousePos);
        }
    }

    // Render all characters
    void renderAll(sf::RenderTarget* target) {
        for (auto& pair : characters) {
            pair.second->render(target);
        }
    }
};
