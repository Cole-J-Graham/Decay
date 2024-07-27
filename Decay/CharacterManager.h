#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

// Forward declaration of StatsManager
class StatsManager;
class InteractionManager;

#include "Character.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>  // Assuming SFML is used for sf::Vector2f

class CharacterManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Character>> characters;
    std::unique_ptr<StatsManager> stats;
    std::unique_ptr<InteractionManager> interactions;

    // Private constructor for singleton pattern
    CharacterManager() : 
        stats(std::make_unique<StatsManager>()),
        interactions(std::make_unique<InteractionManager>()) 
    {}

    // Destructor to clean up resources
    ~CharacterManager() = default;

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
        stats->createInstance(id);
        interactions->createInstance(id);
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

    // Character Stat Functions
    void updateStats(const sf::Vector2f mousePos) {
        stats->update(mousePos);
    }

    void renderStats(sf::RenderTarget* target) {
        stats->render(target);
    }

    // Character Interaction Functions
    void updateInteractions(const sf::Vector2f mousePos) {
        interactions->update(mousePos);
    }

    void renderInteractions(sf::RenderTarget* target) {
        interactions->render(target);
    }
};

#endif // CHARACTER_MANAGER_H
