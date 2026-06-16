#ifndef BONFIRE_STATE_H
#define BONFIRE_STATE_H

#include "State.h"
#include "UiPanel.h"
#include "CharacterManager.h"
#include "GameFlags.h"
#include "EventManager.h"
#include "CompanionConversationManager.h"

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
    void updatePartyPreview(const sf::Vector2f& mousePos);

    // Slot geometry helper — shared between render and hit-test
    sf::FloatRect getPartySlotRect(int index) const;

    // Bonfire Functions
    void restParty();
    void smithWeapon();
    void leaveBonfire();
    void visitShop();

    // Conversation Functions
    void startConversation(const std::string& filePath);
    void updateConversation(const sf::Vector2f& mousePos);
    void renderConversation(sf::RenderTarget* target);
    bool isConversationActive() const;

private:
    UiPanel      ui;
    sf::Texture  bonfireTexture;
    sf::Sprite   bonfireSprite;
    bool         hasBonfireImage = false;
    std::string  areaId;

    // Active companion conversation — null when no conversation is running
    std::unique_ptr<EventManager> activeConversation;

    // Timed feedback message for "nothing to discuss" etc.
    sf::Clock    messageClock;
    float        messageDisplayTime = 0.f;
    bool         messageTimerActive = false;

    // Slot geometry constants mirrored from renderPartyPreview
    static constexpr float kSlotX = 25.f + 12.f;
    static constexpr float kSlotStartY = 50.f + 40.f;
    static constexpr float kSlotW = 240.f - 24.f;
    static constexpr float kSlotH = 212.f;
    static constexpr float kSlotGap = 14.f;
};

#endif