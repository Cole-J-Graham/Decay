#include "BonfireState.h"

#include <iostream>
#include <memory>

// Constructors and Destructors
BonfireState::BonfireState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->initUi();
}

// State Functions
void BonfireState::endState()
{
    std::cout << "Leaving BonfireState!~" << "\n";
}

void BonfireState::updateKeybinds()
{
    this->checkForQuit();
}

void BonfireState::update()
{
    this->updateMousePositions();
    this->updateKeybinds();

    this->ui.update(this->getMousePosView());

    if (this->ui.button("REST_PARTY").isPressed()) {
        this->restParty();
    }

    if (this->ui.button("SMITH_WEAPON").isPressed()) {
        this->smithWeapon();
    }

    if (this->ui.button("LEAVE_BONFIRE").isPressed()) {
        this->leaveBonfire();
    }
}

void BonfireState::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    this->ui.render(*target);
    this->renderPartyPreview(target);
}

// UI Functions
void BonfireState::initUi()
{
    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(150, 150, 150, 255);
    const sf::Color active(20, 20, 20, 70);

    this->ui.addRectangle("MAIN_PANEL", std::make_unique<Rectangle>(560, 5, 800, 800, sf::Color::Transparent, sf::Color::White, 1.f, false));
    this->ui.addRectangle("ACTION_PANEL", std::make_unique<Rectangle>(1370, 50, 400, 300, sf::Color::Transparent, sf::Color::White, 1.f, false));
    this->ui.addRectangle("MESSAGE_PANEL", std::make_unique<Rectangle>(560, 830, 800, 175, sf::Color::Transparent, sf::Color::White, 1.f, false));

    this->ui.addText("TITLE", std::make_unique<Text>(575, 20, 24, "Bonfire", sf::Color::White, false));
    this->ui.addText("MESSAGE", std::make_unique<Text>(575, 845, 16, "The bonfire waits quietly.", sf::Color::White, false));

    this->ui.addButton("REST_PARTY", std::make_unique<Button>(1385, 75, 200, 25, 0.5f, "Rest Party", idle, hover, active, false));
    this->ui.addButton("SMITH_WEAPON", std::make_unique<Button>(1385, 105, 200, 25, 0.5f, "Smith Weapon", idle, hover, active, false));
    this->ui.addButton("LEAVE_BONFIRE", std::make_unique<Button>(1385, 135, 200, 25, 0.5f, "Leave Bonfire", idle, hover, active, false));

    this->ui.addRectangle("PARTY_PREVIEW_PANEL", std::make_unique<Rectangle>(
        25, 50, 300, 750,
        sf::Color::Transparent,
        sf::Color::White,
        1.f,
        false
    ));

    this->ui.addText("PARTY_PREVIEW_TITLE", std::make_unique<Text>(
        35, 60, 16,
        "Party",
        sf::Color::White,
        false
    ));
}

void BonfireState::renderPartyPreview(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    auto& partyMembers = CharacterManager::getInstance().getAllPartyMembers();

    const float panelX = 25.f;
    const float panelY = 50.f;
    const float panelWidth = 300.f;

    const float slotX = panelX + 25.f;
    const float slotY = panelY + 70.f;
    const float slotWidth = panelWidth - 50.f;
    const float slotHeight = 180.f;
    const float slotGap = 25.f;

    for (int i = 0; i < static_cast<int>(partyMembers.size()); i++) {
        if (!partyMembers[i]) {
            continue;
        }

        const float currentSlotY = slotY + (i * (slotHeight + slotGap));

        Rectangle slotBorder(
            slotX,
            currentSlotY,
            slotWidth,
            slotHeight,
            sf::Color::Transparent,
            sf::Color::White,
            1.f,
            false
        );

        slotBorder.render(target);

        const float characterX = slotX + 25.f;
        const float characterY = currentSlotY + 15.f;

        partyMembers[i]->renderPreview(target, characterX, characterY);
    }
}

// Bonfire Functions
void BonfireState::restParty()
{
    CharacterManager::getInstance().restParty();

    this->ui.text("MESSAGE").setString("The party rests at the bonfire. HP restored.");
    std::cout << "Party rested at bonfire." << "\n";
}

void BonfireState::smithWeapon()
{
    // Temporary message until InventoryManager / smithing stones exist.
    this->ui.text("MESSAGE").setString("Smithing is not wired yet.");
    std::cout << "Smith weapon selected." << "\n";
}

void BonfireState::leaveBonfire()
{
    this->endState();

    if (!this->states->empty()) {
        this->states->pop();
    }
}