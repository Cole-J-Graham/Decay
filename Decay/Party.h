#pragma once
#include <vector>
#include <memory> // for std::shared_ptr
#include"Character.h"

class Party {
public:
    //Constructors and Destructors
    Party();
    ~Party();

    //Core Functions
    void render(sf::RenderTarget* target);
    void update(const sf::Vector2f mousePos);

    //Management Functions
    bool addCharacter(const std::shared_ptr<Character>& character);
    bool removeCharacter(const std::shared_ptr<Character>& character);

    //Party Functions
    void renderPartyMembers(sf::RenderTarget* target);
    void updatePartyMembers(const sf::Vector2f mousePos);

    //Rectangle Functions
    void initRects();
    void renderRects(sf::RenderTarget* target);

    //Text Functions
    void initText();
    void renderText(sf::RenderTarget* target);

    //Getters
    std::shared_ptr<Character> getCharacter(int index) const;
    const std::vector<std::shared_ptr<Character>>& getAllCharacters() const;

    //Function to check if the party is full
    bool isFull() const { return party.size() == maxPartySize; }

    //Function to get the current size of the party
    int size() const { return party.size(); }

private:
    std::map<std::string, std::unique_ptr<Rectangle>> rectangles;
    std::map<std::string, std::unique_ptr<Text>> text;

    std::vector<std::shared_ptr<Character>> party;
    static const int maxPartySize = 3;
};