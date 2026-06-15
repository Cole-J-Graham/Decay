#pragma once

#include "State.h"
#include "UiPanel.h"
#include "Rectangle.h"
#include "Button.h"
#include "Text.h"
#include "SaveManager.h"

class MapComponent;

// ============================================================
//  SaveSlotState
//  Slot-picker overlay for saving/loading, built with UiPanel the
//  same way PauseMenuState builds its panel.
//
//  Pushed from:
//   - PauseMenuState's SAVE/LOAD buttons, with mode = Save/Load and
//     a live MapComponent* (so map/unlock state can be read/applied
//     directly).
//   - MainMenuState's LOAD button, with mode = Load and map = nullptr
//     (no TravelState exists yet — SaveManager stashes the map/unlock
//     state as "pending"; the freshly-pushed TravelState applies it
//     via applyPendingMapState() once its MapComponent exists).
// ============================================================

class SaveSlotState : public State
{
public:
    enum class Mode { Save, Load };

    SaveSlotState(sf::RenderWindow* window,
        std::stack<State*>* states,
        Mode mode,
        MapComponent* map = nullptr);
    ~SaveSlotState() = default;

    void update() override;
    void render(sf::RenderTarget* target = nullptr) override;
    void endState() override;

private:
    void initOverlay();
    void initPanel();

    std::string buildSlotLabel(int slot) const;

    sf::RectangleShape overlay;   // fullscreen dark tint
    UiPanel panel;

    Mode mode;
    MapComponent* map = nullptr;  // non-owning; nullptr for main-menu loads

    bool escWasDown = false;      // edge-detect for ESC toggle
    bool escReleasedOnce = false;
    bool clickReleasedOnce = false;

    static constexpr int numSlots = SaveManager::maxSlots;
};