#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

// Forward declaration of StatsManager
class StatsManager;

#include "Party.h"
#include "Character.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>  // Assuming SFML is used for sf::Vector2f

class CharacterManager {
private:
    std::map<std::string, std::unique_ptr<Button>> buttons;
    std::unordered_map<std::string, std::shared_ptr<Character>> characters;
    Party party;

    int passCount;
    int passCountMax;
    bool partyHidden;
    bool statsHidden;
    bool clicked;

    // Private constructor for singleton pattern
    CharacterManager() :
        party()
    {
        this->initButtons();
        this->partyHidden = true;
        this->statsHidden = true;
        this->clicked = false;
    }

    //Destructor to clean up resources
    ~CharacterManager() = default;

public:
    //Disable copy constructor and assignment operator
    CharacterManager(const CharacterManager&) = delete;
    CharacterManager& operator=(const CharacterManager&) = delete;

    //Core Functions
    static CharacterManager& getInstance() {
        static CharacterManager instance;
        return instance;
    }

    //Character Functions
    void addCharacter(const std::string& id, const std::shared_ptr<Character>& character) {
        characters[id] = character;
    }

    std::shared_ptr<Character> getCharacter(const std::string& id) {
        auto it = characters.find(id);
        if (it != characters.end()) {
            return it->second;
        }
        return nullptr;
    }

    const std::unordered_map<std::string, std::shared_ptr<Character>>& getAllCharacters() const {
        return characters;
    }

    void updateAll(const sf::Vector2f mousePos) {
        for (auto& pair : characters) {
            pair.second->update(mousePos);
            if (!this->statsHidden) { pair.second->getStats()->update(mousePos); }
        }
        this->updateButtons(mousePos);
    }

    void renderAll(sf::RenderTarget* target) {
        for (auto& pair : characters) {
            pair.second->render(target);
        }
    }

    //Character Stat Functions
    std::unordered_map<std::string, StatsModule*> getAllStats() const {
        std::unordered_map<std::string, StatsModule*> allStats;

        for (const auto& pair : characters) {
            const auto& character = pair.second;
            if (character) {
                // Extract the raw pointer from the unique_ptr
                allStats[pair.first] = character->getStats().get();
            }
        }

        return allStats;
    }

    void clearAllCharacterMoves() {
        for (auto& pair : characters) {
            pair.second->clearMoves();
        }
    }

    void renderAllStats(sf::RenderTarget* target) {
        for (auto& pair : characters) {
            if (!this->statsHidden) { pair.second->getStats()->render(target); }
        }
        if (!this->partyHidden) { this->party.render(target); }
        this->renderButtons(target);
    }

    //Character Party Functions
    bool addCharacterToParty(const std::string& id) {
        auto character = getCharacter(id);
        if (character) {
            return party.addCharacter(character);
        }
        return false;
    }

    bool removeCharacterFromParty(const std::string& id) {
        auto character = getCharacter(id);
        if (character) {
            return party.removeCharacter(character);
        }
        return false;
    }

    Party& getParty() {
        return party;
    }

    const std::vector<std::shared_ptr<Character>>& getAllPartyMembers() const {
        return party.getAllCharacters();
    }

    //Button Functions
    void initButtons() {
        this->buttons["OPENPARTY"] = std::make_unique<Button>(1370, 775, 100, 25, 0.5f, "Party",
            sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
        this->buttons["OPENSTATS"] = std::make_unique<Button>(1475, 775, 100, 25, 0.5f, "Stats",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    }

    void renderButtons(sf::RenderTarget* target) {
        //Render Character Manager Buttons
        for (auto& pair : buttons) {
            pair.second->render(target);
        }

        //Render Stats Buttons
        int height = 20;
        for (auto& pair : characters) {
            if (pair.second) { // Check if pointer is valid
                auto button = pair.second->getStats()->getButtons()[pair.second->getStats()->getButtonId()];
                if (button) {
                    button->setPosition(1705, height += 30);
                }
                else {
                    std::cerr << "Button not found for ID: " << pair.second->getStats()->getButtonId() << std::endl;
                }
            }
        }
    }

    void updateButtons(const sf::Vector2f mousePos) {
        for (auto& it : this->buttons) {
        if (it.second) { // Ensure button is valid
            it.second->update(mousePos);
            }
        }

        //Open the party or stats menus if they are currently hidden
        if (this->buttons["OPENPARTY"] && this->buttons["OPENPARTY"]->isPressed()) {
            this->partyHidden = !this->partyHidden;
        }

        if (this->buttons["OPENSTATS"] && this->buttons["OPENSTATS"]->isPressed()) {
            this->statsHidden = !this->statsHidden;
        }

        // Select the button and display stats while hiding all other stats
        this->passCountMax = static_cast<int>(characters.size());
        for (auto& pair : characters) {
            auto button = pair.second->getStats()->getButtons()[pair.second->getStats()->getButtonId()];
            if (button && button->isPressed()) {
                this->clicked = true;
            }

            if (this->passCount != this->passCountMax && this->clicked) {
                pair.second->getStats()->getCurrentInstance() = false;
                this->passCount++;
            } else if (this->passCount == this->passCountMax) {
                pair.second->getStats()->getCurrentInstance() = true;
                this->passCount = 0;
                this->clicked = false;
            }
        }
    }
};

#endif // CHARACTER_MANAGER_H