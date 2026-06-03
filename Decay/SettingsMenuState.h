#pragma once

#include "State.h"
#include "UiPanel.h"
#include "Rectangle.h"
#include "Button.h"
#include "Text.h"

class MusicPlayer;

class SettingsMenuState : public State
{
public:
    // fromPause = true  → ESC pops twice (settings + pause), returning to game
    // fromPause = false → ESC pops once (settings only), returning to main menu
    SettingsMenuState(sf::RenderWindow* window,
        std::stack<State*>* states,
        MusicPlayer* musicPlayer,
        bool                fromPause = false);
    ~SettingsMenuState() = default;

    void update()  override;
    void render(sf::RenderTarget* target = nullptr) override;
    void endState() override;

private:
    void initOverlay();
    void initPanel();

    // Snap v to the nearest 5-step boundary, then clamp [0, 100]
    static int clampVolume(int v);

    void applyMusicVolume();
    void applySfxVolume();
    void refreshLabels();

    // Pop this state (and optionally the pause state beneath it)
    void closeSettings();

    sf::RectangleShape overlay;
    UiPanel panel;

    MusicPlayer* musicPlayer = nullptr;  // non-owning

    bool fromPause = false;  // controls double-pop on ESC

    bool escWasDown = false;
    bool escReleasedOnce = false;
};