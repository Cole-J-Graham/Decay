#include "SaveSlotState.h"
#include "GameTriggers.h"
#include "TravelState.h"

#include <string>

SaveSlotState::SaveSlotState(sf::RenderWindow* window,
    std::stack<State*>* states,
    Mode mode,
    MapComponent* map)
    : State(window, states)
    , mode(mode)
    , map(map)
{
    this->initOverlay();
    this->initPanel();
}

void SaveSlotState::initOverlay()
{
    // Fullscreen semi-transparent black — dims whatever is underneath
    this->overlay.setSize(sf::Vector2f(1920.f, 1080.f));
    this->overlay.setPosition(0.f, 0.f);
    this->overlay.setFillColor(sf::Color(0, 0, 0, 160));
}

void SaveSlotState::initPanel()
{
    const float panelW = 700.f;
    const float panelH = 700.f;
    const float panelX = (1920.f - panelW) / 2.f;
    const float panelY = (1080.f - panelH) / 2.f;

    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(100, 130, 100, 200);
    const sf::Color active(20, 20, 20, 70);

    // Outer border
    this->panel.addRectangle("BORDER", std::make_unique<Rectangle>(
        panelX, panelY, panelW, panelH,
        sf::Color(10, 10, 10, 220), sf::Color::White, 1.f, false));

    // Header divider
    this->panel.addRectangle("HEADERDIV", std::make_unique<Rectangle>(
        panelX, panelY + 40.f, panelW, 1,
        sf::Color(255, 255, 255, 60), sf::Color::Transparent, 0.f, false));

    // Separator above the Back button
    this->panel.addRectangle("FOOTERDIV", std::make_unique<Rectangle>(
        panelX, panelY + panelH - 60.f, panelW, 1,
        sf::Color(255, 255, 255, 30), sf::Color::Transparent, 0.f, false));

    // Title
    const std::string title = (this->mode == Mode::Save) ? "SAVE GAME" : "LOAD GAME";
    this->panel.addText("TITLE", std::make_unique<Text>(
        panelX + 16.f, panelY + 10.f, 13,
        title,
        sf::Color(200, 200, 200, 220), false));

    // ESC hint — top-right of header
    this->panel.addText("ESC_HINT", std::make_unique<Text>(
        panelX + panelW - 56.f, panelY + 10.f, 11,
        "[ esc ]",
        sf::Color(160, 160, 160, 140), false));

    // Slot grid — 2 columns x 5 rows = 10 slots
    const float slotW = 320.f;
    const float slotH = 60.f;
    const float colGap = 20.f;
    const float rowGap = 15.f;
    const float col1X = panelX + 20.f;
    const float col2X = col1X + slotW + colGap;
    const float gridStartY = panelY + 60.f;

    for (int slot = 0; slot < numSlots; slot++)
    {
        const int row = slot / 2;
        const int col = slot % 2;
        const float x = (col == 0) ? col1X : col2X;
        const float y = gridStartY + static_cast<float>(row) * (slotH + rowGap);

        this->panel.addButton("SLOT" + std::to_string(slot), std::make_unique<Button>(
            x, y, slotW, slotH, 0.5f, this->buildSlotLabel(slot),
            idle, hover, active, false));
    }

    // Back
    const float backW = 300.f;
    this->panel.addButton("BACK", std::make_unique<Button>(
        panelX + (panelW - backW) / 2.f, panelY + panelH - 50.f, backW, 28.f, 0.5f, "Back",
        idle, hover, active, false));
}

std::string SaveSlotState::buildSlotLabel(int slot) const
{
    const SaveManager::SlotSummary summary = SaveManager::getInstance().getSlotSummary(slot);

    if (!summary.exists) {
        return "Slot " + std::to_string(slot + 1) + ": Empty";
    }

    std::string label = "Slot " + std::to_string(slot + 1) + ": "
        + summary.location + "  Lv." + std::to_string(summary.partyLevel);

    if (!summary.timestamp.empty()) {
        label += "\n" + summary.timestamp;
    }

    return label;
}

void SaveSlotState::update()
{
    this->updateMousePositions();

    const bool escDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    if (!this->escWasDown && escDown && this->escReleasedOnce) {
        this->quit = true;
    }
    if (!escDown) {
        this->escReleasedOnce = true;
    }
    this->escWasDown = escDown;

    // Don't touch the panel at all until the click that opened this state
    // has been released. Calling panel.update() while that click is still
    // "down" would register a press edge on the overlapping button below —
    // and whatever SFX/side-effects Button::update() fires on that edge
    // would happen regardless of what our logic below does with isPressed().
    // Deferring the update entirely means that spurious edge never occurs.
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->clickReleasedOnce = true;
    }
    if (!this->clickReleasedOnce) {
        return;
    }

    this->panel.update(this->getMousePosView());

    if (this->panel.button("BACK").isPressed()) {
        this->quit = true;
        return;
    }

    for (int slot = 0; slot < numSlots; slot++)
    {
        if (!this->panel.button("SLOT" + std::to_string(slot)).isPressed()) continue;

        if (this->mode == Mode::Save)
        {
            if (SaveManager::getInstance().saveToSlot(slot, this->map))
            {
                GameTriggers::showNotification("Saved to Slot " + std::to_string(slot + 1));
                this->quit = true;
            }
        }
        else // Mode::Load
        {
            const SaveManager::SlotSummary summary = SaveManager::getInstance().getSlotSummary(slot);
            if (!summary.exists) break;

            if (SaveManager::getInstance().loadFromSlot(slot, this->map))
            {
                if (this->map == nullptr)
                {
                    this->states->push(new TravelState(this->window, this->states));
                }
                else
                {
                    GameTriggers::showNotification("Loaded Slot " + std::to_string(slot + 1));
                }

                this->quit = true;
            }
        }

        break;
    }
}

void SaveSlotState::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    target->draw(this->overlay);
    this->panel.render(*target);
}

void SaveSlotState::endState()
{
    // Nothing to clean up — UiPanel owns everything via unique_ptr
}