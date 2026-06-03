#ifndef BONFIRE_STATE_H
#define BONFIRE_STATE_H

#include "State.h"
#include "UiPanel.h"
#include "CharacterManager.h"
#include "GameFlags.h"

class BonfireState : public State
{
public:
    // Constructors and Destructors
    BonfireState(sf::RenderWindow* window, std::stack<State*>* states, const std::string& areaId = "");
    ~BonfireState() = default;

    // State Functions
    void endState();
    void updateKeybinds();
    void update();
    void render(sf::RenderTarget* target = nullptr);

private:
    // UI Functions
    void initUi();
    void renderPartyPreview(sf::RenderTarget* target);

    // Bonfire Functions
    void restParty();
    void smithWeapon();
    void leaveBonfire();
    void visitShop();

private:
    UiPanel ui;
    sf::Texture  bonfireTexture;
    sf::Sprite   bonfireSprite;
    bool         hasBonfireImage = false;
    std::string  areaId;

};

#endif