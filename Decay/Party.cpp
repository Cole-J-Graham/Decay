#include "Party.h"

// Constructors and Destructors
Party::Party()
{
    this->initUi();
}

Party::~Party()
{}

// Core Functions
void Party::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    this->ui.render(*target);
    this->renderPartyMembersButtons(target);
}

void Party::update(const sf::Vector2f mousePos)
{
    this->updatePartyMembers(mousePos);
}

// Management Functions
bool Party::addCharacter(const std::shared_ptr<Character>& character)
{
    if (party.size() < maxPartySize) {
        party.push_back(character);
        this->updateFramePositions();
        return true;
    }
    return false;
}

bool Party::removeCharacter(const std::shared_ptr<Character>& character)
{
    auto it = std::find(party.begin(), party.end(), character);
    if (it != party.end()) {
        party.erase(it);
        this->updateFramePositions();
        return true;
    }
    return false;
}

void Party::removePartyMemberOnRightClick()
{
    for (int i = 0; i < static_cast<int>(party.size()); i++) {
        if (party[i] && party[i]->idButtonIsClicked()) {
            this->removeCharacter(party[i]);
            return;
        }
    }
}

// Party Functions
void Party::renderPartyMembers(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    for (int i = 0; i < static_cast<int>(party.size()); i++) {
        if (party[i]) party[i]->render(target);
    }
}

void Party::renderPartyMembersButtons(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    const float activeColX = 1410.f;
    const float colWidth = 122.f;   // fills up to the divider at x=1535 with a small margin
    const float rowHeight = 28.f;
    const float firstRowY = 105.f;

    for (int slot = 0; slot < maxPartySize; slot++)
    {
        float y = firstRowY + slot * rowHeight;

        // Alternating row tint
        if (slot % 2 == 0) {
            sf::RectangleShape rowBg(sf::Vector2f(colWidth, rowHeight - 2.f));
            rowBg.setPosition(activeColX, y);
            rowBg.setFillColor(sf::Color(255, 255, 255, 8));
            target->draw(rowBg);
        }

        // Row divider
        sf::RectangleShape divider(sf::Vector2f(colWidth, 1.f));
        divider.setPosition(activeColX, y - 3.f);
        divider.setFillColor(sf::Color(255, 255, 255, 25));
        target->draw(divider);

        if (slot < static_cast<int>(party.size()) && party[slot])
        {
            // Occupied slot — render character button
            int x = static_cast<int>(activeColX);
            int yPos = static_cast<int>(y);
            party[slot]->setIdButtonPosition(x, yPos);
            party[slot]->renderIdButton(target);
        }
        else
        {
            // Empty slot — draw a dim placeholder with slot number
            sf::RectangleShape slotBg(sf::Vector2f(colWidth - 2.f, rowHeight - 4.f));
            slotBg.setPosition(activeColX + 1.f, y + 1.f);
            slotBg.setFillColor(sf::Color(255, 255, 255, 10));
            slotBg.setOutlineColor(sf::Color(255, 255, 255, 20));
            slotBg.setOutlineThickness(1.f);
            target->draw(slotBg);
        }
    }

    // Closing separator
    float bottomY = firstRowY + maxPartySize * rowHeight;
    sf::RectangleShape sep(sf::Vector2f(colWidth, 2.f));
    sep.setPosition(activeColX, bottomY + 4.f);
    sep.setFillColor(sf::Color(255, 255, 255, 40));
    target->draw(sep);
}

void Party::updatePartyMembers(const sf::Vector2f mousePos)
{
    for (int i = 0; i < static_cast<int>(party.size()); i++) {
        if (party[i]) party[i]->updateIdButton(mousePos);
    }
    this->removePartyMemberOnRightClick();
}

void Party::updateFramePositions()
{
    if (party.size() > 0) party[0]->setSpritePosition(frameOneX, frameOneY);
    if (party.size() > 1) party[1]->setSpritePosition(frameTwoX, frameTwoY);
    if (party.size() > 2) party[2]->setSpritePosition(frameThreeX, frameThreeY);
}

void Party::restParty()
{
    for (auto& character : this->party) {
        if (character) character->rest();
    }
}

void Party::addExpToParty(float amount)
{
    if (amount <= 0.f) return;
    for (auto& character : this->party) {
        if (character) character->addExp(amount);
    }
}

bool Party::addToSlot(int slot, const std::shared_ptr<Character>& character)
{
    if (slot < 0 || slot >= maxPartySize) return false;
    if (containsCharacter(character)) return false;

    // Grow vector to fit the slot if needed, padding with nullptr
    while (static_cast<int>(party.size()) <= slot)
        party.push_back(nullptr);

    if (party[slot] != nullptr) return false;  // slot occupied

    party[slot] = character;
    this->updateFramePositions();
    return true;
}

// UI Functions
void Party::initUi()
{
    // Main panel border
    this->ui.addRectangle("PARTYMENU", std::make_unique<Rectangle>(
        1400, 50, 270, 620,
        sf::Color::Transparent, sf::Color::White, 1.f, false));

    // Thin divider below header bar
    this->ui.addRectangle("HEADERDIV", std::make_unique<Rectangle>(
        1400, 82, 270, 1,
        sf::Color(255, 255, 255, 60), sf::Color::Transparent, 0.f, false));

    // Vertical divider splitting ACTIVE | INACTIVE columns
    this->ui.addRectangle("COLDIV", std::make_unique<Rectangle>(
        1535, 83, 1, 537,
        sf::Color(255, 255, 255, 40), sf::Color::Transparent, 0.f, false));

    // Title
    this->ui.addText("TITLE", std::make_unique<Text>(
        1410, 58, 13,
        "PARTY",
        sf::Color(200, 200, 200, 220), false));

    // Column headers — sit in the band between HEADERDIV (y=82) and first row (y=105)
    this->ui.addText("ACTIVELABEL", std::make_unique<Text>(
        1420, 88, 11,
        "ACTIVE",
        sf::Color(180, 180, 180, 200), false));

    this->ui.addText("INACTIVELABEL", std::make_unique<Text>(
        1550, 88, 11,
        "INACTIVE",
        sf::Color(160, 220, 255, 200), false));
}

// Getters
std::shared_ptr<Character> Party::getCharacter(int index) const
{
    if (index >= 0 && index < static_cast<int>(party.size()))
        return party[index];
    return nullptr;
}

const std::vector<std::shared_ptr<Character>>& Party::getAllCharacters() const
{
    return party;
}
