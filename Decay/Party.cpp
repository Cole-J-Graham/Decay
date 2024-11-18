#include "Party.h"
//Constructors and Destructors
Party::Party()
{
    //Initialization
    this->initRects();
    this->initText();
}

Party::~Party()
{

}

//Core Functions
void Party::render(sf::RenderTarget* target)
{
    this->renderRects(target);
    this->renderText(target);
    this->renderPartyMembersButtons(target);
}

void Party::update(const sf::Vector2f mousePos)
{
    this->updatePartyMembers(mousePos);
}

//Management Functions
bool Party::addCharacter(const std::shared_ptr<Character>& character) 
{
    //Adds a character to the party if there is space
    if (party.size() < maxPartySize) {
        party.push_back(character);
        this->updateFramePositions();
        return true;
    }
    return false; // Party is full
}

bool Party::removeCharacter(const std::shared_ptr<Character>& character) 
{
    //Removes a character from the party
    auto it = std::find(party.begin(), party.end(), character);
    if (it != party.end()) {
        party.erase(it);
        return true;
    }
    return false; // Character not found
}

//Party Functions
void Party::renderPartyMembers(sf::RenderTarget* target)
{
    for (int i = 0; i < party.size(); i++) {
        party[i]->render(target);
    }
}

void Party::updatePartyMembers(const sf::Vector2f mousePos)
{
    for (int i = 0; i < party.size(); i++) {
        party[i]->update(mousePos);
    }
}

void Party::renderPartyMembersButtons(sf::RenderTarget* target)
{
    int width = 1401;
    int height = 50;
    for (int i = 0; i < party.size(); i++) {
        party[i]->renderIdButton(target);
        party[i]->setIdButtonPosition(width, height += 26);
    }
}

void Party::updateFramePositions() {
    // Make sure to update positions based on the actual size of the party
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


//Rectangle Functions
void Party::initRects()
{
    this->rectangles["PARTYMENU"] = std::make_unique<Rectangle>(1400, 50, 225, 600, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
    this->rectangles["LABELSEPARATOR"] = std::make_unique<Rectangle>(1400, 50, 225, 25, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
}

void Party::renderRects(sf::RenderTarget* target)
{
    for (auto& pair : rectangles) {
        pair.second->render(target);
    }
}

//Text Functions
void Party::initText()
{
    this->text["LABELSEPARATORTEXT"] = std::make_unique<Text>(1402, 50, 16, "ACTIVE         |     INACTIVE",
        sf::Color::White, false);
}

void Party::renderText(sf::RenderTarget* target)
{
    for (auto& pair : text) {
        pair.second->render(target);
    }
}

//Getters
std::shared_ptr<Character> Party::getCharacter(int index) const 
{
    if (index >= 0 && index < party.size()) {
        return party[index];
    }
    return nullptr; // Invalid index
}

const std::vector<std::shared_ptr<Character>>& Party::getAllCharacters() const
{
    return party;
}