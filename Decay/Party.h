#pragma once
#include <vector>
#include <memory>
#include "Character.h"
#include "UiPanel.h"

class Party {
public:
    // Constructors and Destructors
    Party();
    ~Party();

    // Core Functions
    void render(sf::RenderTarget* target);
    void update(const sf::Vector2f mousePos);
    void initUi();

    // Management Functions
    bool addCharacter(const std::shared_ptr<Character>& character);
    bool addToSlot(int slot, const std::shared_ptr<Character>& character);  // explicit slot (0-2)
    bool removeCharacter(const std::shared_ptr<Character>& character);
    void removePartyMemberOnRightClick();

    // Save/Load support — empties the active party so a saved composition
    // can be restored via addToSlot(). Mirrors removeCharacter's cleanup
    // (frame positions) but for all members at once.
    void clear();

    // Party Functions
    void renderPartyMembers(sf::RenderTarget* target);
    void updatePartyMembers(const sf::Vector2f mousePos);
    void renderPartyMembersButtons(sf::RenderTarget* target);
    void updateFramePositions();
    void restParty();
    void addExpToParty(float amount);

    // Getters
    std::shared_ptr<Character> getCharacter(int index) const;
    const std::vector<std::shared_ptr<Character>>& getAllCharacters() const;

    // Modifiers and Operators
    bool isFull() const { return static_cast<int>(party.size()) == maxPartySize; }
    int size() const { return static_cast<int>(party.size()); }
    bool containsCharacter(const std::shared_ptr<Character>& character) const {
        for (const auto& m : party)
            if (m == character) return true;
        return false;
    }

    static const int maxPartySize = 3;

private:
    UiPanel ui;
    std::vector<std::shared_ptr<Character>> party;

    const float frameOneX = 25.f;  const float frameOneY = 150.f;
    const float frameTwoX = 25.f;  const float frameTwoY = 420.f;
    const float frameThreeX = 25.f;  const float frameThreeY = 690.f;
};