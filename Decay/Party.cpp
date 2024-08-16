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
    this->renderPartyMembers(target);
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

//Rectangle Functions
void Party::initRects()
{
    this->rectangles["PARTYMENU"] = std::make_unique<Rectangle>(1400, 50, 300, 600, sf::Color::Transparent,
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
    this->text["HP"] = std::make_unique<Text>(1405, 55, 16, "Current Party Members",
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