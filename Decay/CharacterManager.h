#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

#include "Party.h"
#include "Character.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class CharacterManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<Character>> characters;
    Party party;

    int passCount = 0;
    int passCountMax = 0;
    bool clicked = false;

private:
    CharacterManager()
        : party()
    {}

    ~CharacterManager() = default;

public:
    CharacterManager(const CharacterManager&) = delete;
    CharacterManager& operator=(const CharacterManager&) = delete;

    static CharacterManager& getInstance()
    {
        static CharacterManager instance;
        return instance;
    }

    // Character Functions
    void addCharacter(const std::string& id, const std::shared_ptr<Character>& character)
    {
        characters[id] = character;
    }

    std::shared_ptr<Character> getCharacter(const std::string& id)
    {
        auto it = characters.find(id);

        if (it != characters.end()) {
            return it->second;
        }

        return nullptr;
    }

    const std::unordered_map<std::string, std::shared_ptr<Character>>& getAllCharacters() const
    {
        return characters;
    }

    void updateAll(const sf::Vector2f mousePos)
    {
        for (auto& pair : characters) {
            pair.second->update(mousePos);
        }
    }

    void renderAll(sf::RenderTarget* target)
    {
        for (auto& pair : characters) {
            pair.second->render(target);
        }
    }

    // Stats Functions
    std::unordered_map<std::string, StatsModule*> getAllStats() const
    {
        std::unordered_map<std::string, StatsModule*> allStats;

        for (const auto& pair : characters) {
            const auto& character = pair.second;

            if (character) {
                allStats[pair.first] = character->getStats().get();
            }
        }

        return allStats;
    }

    void updateStatsPanel(const sf::Vector2f mousePos)
    {
        for (auto& pair : characters) {
            if (pair.second) {
                pair.second->getStats()->update(mousePos);
            }
        }

        this->updateStatsSelection();
    }

    void renderStatsPanel(sf::RenderTarget* target)
    {
        for (auto& pair : characters) {
            if (pair.second) {
                pair.second->getStats()->render(target);
            }
        }

        this->positionStatsButtons();
    }

    void updateStatsSelection()
    {
        this->passCountMax = static_cast<int>(characters.size());

        for (auto& pair : characters) {
            auto button = pair.second->getStats()->getButtons()[pair.second->getStats()->getButtonId()];

            if (button && button->isPressed()) {
                this->clicked = true;
            }

            if (this->passCount != this->passCountMax && this->clicked) {
                pair.second->getStats()->getCurrentInstance() = false;
                this->passCount++;
            }
            else if (this->passCount == this->passCountMax) {
                pair.second->getStats()->getCurrentInstance() = true;
                this->passCount = 0;
                this->clicked = false;
            }
        }
    }

    void positionStatsButtons()
    {
        float height = 20.f;

        for (auto& pair : characters) {
            if (pair.second) {
                auto button = pair.second->getStats()->getButtons()[pair.second->getStats()->getButtonId()];

                if (button) {
                    button->setPosition(1690.f, height += 30.f);
                }
                else {
                    std::cerr << "Button not found for ID: "
                        << pair.second->getStats()->getButtonId()
                        << std::endl;
                }
            }
        }
    }

    // Party Functions
    void updatePartyPanel(const sf::Vector2f& mousePos)
    {
        this->party.update(mousePos);
        this->updateCharacterSelectionForParty(mousePos);
    }

    void renderPartyPanel(sf::RenderTarget* target)
    {
        this->party.render(target);
        this->renderCharacterSelectionForParty(target);
    }

    void updateCharacterSelectionForParty(const sf::Vector2f& mousePos)
    {
        std::shared_ptr<Character> selectedCharacter = nullptr;

        // Pass 1: update every inactive character button first.
        for (auto& pair : characters) {
            if (!pair.second || party.containsCharacter(pair.second)) {
                continue;
            }

            pair.second->updateIdButton(mousePos);
        }

        // Pass 2: after all buttons know the current mouse state, pick only one.
        for (auto& pair : characters) {
            if (!pair.second || party.containsCharacter(pair.second)) {
                continue;
            }

            if (pair.second->idButtonLeftClicked()) {
                selectedCharacter = pair.second;
                break;
            }
        }

        if (selectedCharacter == nullptr) {
            return;
        }

        if (party.isFull()) {
            party.removeCharacter(party.getCharacter(0));
        }

        party.addCharacter(selectedCharacter);
    }

    void renderCharacterSelectionForParty(sf::RenderTarget* target)
    {
        const float colX = 1538.f;
        const float colWidth = 125.f;   // fills from divider to panel right edge (1538+125=1663, panel ends ~1670)
        const float rowHeight = 28.f;
        float y = 105.f;

        for (auto& pair : characters) {
            if (!pair.second || party.containsCharacter(pair.second)) continue;

            // Row tint behind inactive button
            sf::RectangleShape rowBg(sf::Vector2f(colWidth, rowHeight - 2.f));
            rowBg.setPosition(colX, y + 1.f);
            rowBg.setFillColor(sf::Color(255, 255, 255, 5));
            target->draw(rowBg);

            int x = static_cast<int>(colX);
            int yPos = static_cast<int>(y);
            pair.second->setIdButtonPosition(x, yPos);
            pair.second->renderIdButton(target);
            y += rowHeight;
        }
    }

    void renderAllPartyButtons(sf::RenderTarget* target)
    {
        party.renderPartyMembersButtons(target);
    }

    void renderAllPartyMembers(sf::RenderTarget* target)
    {
        party.renderPartyMembers(target);
    }

    bool addCharacterToParty(const std::string& id)
    {
        auto character = getCharacter(id);

        if (character) {
            return party.addCharacter(character);
        }

        return false;
    }

    bool removeCharacterFromParty(const std::string& id)
    {
        auto character = getCharacter(id);

        if (character) {
            return party.removeCharacter(character);
        }

        return false;
    }

    Party& getParty()
    {
        return party;
    }

    const std::vector<std::shared_ptr<Character>>& getAllPartyMembers() const
    {
        return party.getAllCharacters();
    }

    void clearAllCharacterMoves()
    {
        for (auto& pair : characters) {
            pair.second->clearMoves();
        }
    }

    void restParty() { this->party.restParty(); }

    void addExpToParty(float amount) { this->party.addExpToParty(amount); }
};

#endif