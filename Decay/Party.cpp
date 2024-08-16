#include "Party.h"
//Constructors and Destructors
Party::Party()
{

}

Party::~Party()
{

}

//Core Functions

//Management Functions
bool Party::addCharacter(const std::shared_ptr<Character>& character) {
    //Adds a character to the party if there is space
    if (characters.size() < maxPartySize) {
        characters.push_back(character);
        return true;
    }
    return false; // Party is full
}

bool Party::removeCharacter(const std::shared_ptr<Character>& character) {
    //Removes a character from the party
    auto it = std::find(characters.begin(), characters.end(), character);
    if (it != characters.end()) {
        characters.erase(it);
        return true;
    }
    return false; // Character not found
}

//Getters
std::shared_ptr<Character> Party::getCharacter(int index) const {
    if (index >= 0 && index < characters.size()) {
        return characters[index];
    }
    return nullptr; // Invalid index
}

const std::vector<std::shared_ptr<Character>>& Party::getAllCharacters() const
{
    return characters;
}