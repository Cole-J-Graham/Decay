#pragma once
#include <vector>
#include <memory> // for std::shared_ptr
#include"Character.h"

class Party {
private:
    std::vector<std::shared_ptr<Character>> characters;
    static const int maxPartySize = 3;

public:
    //Constructors and Destructors
    Party();
    ~Party();

    //Core Functions

    //ManagementFunctions
    bool addCharacter(const std::shared_ptr<Character>& character);
    bool removeCharacter(const std::shared_ptr<Character>& character);

    //Getters
    std::shared_ptr<Character> getCharacter(int index) const;
    const std::vector<std::shared_ptr<Character>>& getAllCharacters() const;

    //Function to check if the party is full
    bool isFull() const { return characters.size() == maxPartySize; }

    //Function to get the current size of the party
    int size() const { return characters.size(); }
};