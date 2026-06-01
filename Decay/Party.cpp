#include "Party.h"

// Constructors and Destructors
Party::Party()
{
    this->initUi();
}

Party::~Party()
{
}

// Core Functions
void Party::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

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
    if (target == nullptr) {
        return;
    }

    for (int i = 0; i < static_cast<int>(party.size()); i++) {
        if (party[i]) {
            party[i]->render(target);
        }
    }
}

void Party::renderPartyMembersButtons(sf::RenderTarget* target)
{
    int width = 1401;
    int height = 50;

    for (int i = 0; i < static_cast<int>(party.size()); i++) {
        int x = width;
        int y = height += 26;

        party[i]->setIdButtonPosition(x, y);
        party[i]->renderIdButton(target);
    }
}

void Party::updatePartyMembers(const sf::Vector2f mousePos)
{
    for (int i = 0; i < static_cast<int>(party.size()); i++) {
        if (party[i]) {
            party[i]->updateIdButton(mousePos);
        }
    }

    this->removePartyMemberOnRightClick();
}

void Party::updateFramePositions()
{
    if (party.size() > 0) {
        party[0]->setSpritePosition(frameOneX, frameOneY);
    }

    if (party.size() > 1) {
        party[1]->setSpritePosition(frameTwoX, frameTwoY);
    }

    if (party.size() > 2) {
        party[2]->setSpritePosition(frameThreeX, frameThreeY);
    }
}

void Party::restParty()
{
    for (auto& character : this->party) {
        if (character) {
            character->rest();
        }
    }
}

void Party::addExpToParty(float amount)
{
    if (amount <= 0.f) {
        return;
    }

    for (auto& character : this->party) {
        if (character) {
            character->addExp(amount);
        }
    }
}

// UI Functions
void Party::initUi()
{
    this->ui.addRectangle("PARTYMENU", std::make_unique<Rectangle>(1400, 50, 225, 600, sf::Color::Transparent,
        sf::Color::White,
        1.f,
        false
    ));

    this->ui.addRectangle("LABELSEPARATOR", std::make_unique<Rectangle>(1400, 50, 225, 25, sf::Color::Transparent,
        sf::Color::White,
        1.f,
        false
    ));

    this->ui.addText("LABELSEPARATORTEXT", std::make_unique<Text>(1402, 50, 16, "ACTIVE         |     INACTIVE",
        sf::Color::White,
        false
    ));
}

// Getters
std::shared_ptr<Character> Party::getCharacter(int index) const
{
    if (index >= 0 && index < party.size()) {
        return party[index];
    }

    return nullptr;
}

const std::vector<std::shared_ptr<Character>>& Party::getAllCharacters() const
{
    return party;
}