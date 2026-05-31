#pragma once
#include <vector>
#include <memory> // for std::shared_ptr
#include"Character.h"
#include "UiPanel.h"

class Party {
public:
    //Constructors and Destructors
    Party();
    ~Party();

    //Core Functions
    void render(sf::RenderTarget* target);
    void update(const sf::Vector2f mousePos);
    void initUi();

    //Management Functions
    bool addCharacter(const std::shared_ptr<Character>& character);
    bool removeCharacter(const std::shared_ptr<Character>& character);

    //Party Functions
    void renderPartyMembers(sf::RenderTarget* target);
    void updatePartyMembers(const sf::Vector2f mousePos);
    void renderPartyMembersButtons(sf::RenderTarget* target);
    void updateFramePositions();

    //Getters
    std::shared_ptr<Character> getCharacter(int index) const;
    const std::vector<std::shared_ptr<Character>>& getAllCharacters() const;

    //Modifiers and Operators
    bool isFull() const { return party.size() == maxPartySize; }
    int size() const { return party.size(); }
    bool containsCharacter(const std::shared_ptr<Character>& character) const {
        for (const auto& partyMember : party) {
            if (partyMember == character) {
                return true;  // Character is already in the party
            }
        }
        return false;  // Character not found in the party
    }

private:
    UiPanel ui;
    std::vector<std::shared_ptr<Character>> party;

    static const int maxPartySize = 3;
    const float frameOneX = 25.f;
    const float frameOneY = 150.f;

    const float frameTwoX = 25.f;
    const float frameTwoY = 420.f;

    const float frameThreeX = 25.f;
    const float frameThreeY = 690.f;
};