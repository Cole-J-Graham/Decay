#pragma once

#include "State.h"
#include "UiPanel.h"
#include "Rectangle.h"
#include "Button.h"
#include "Text.h"

class MusicPlayer;

class PauseMenuState : public State
{
public:
    PauseMenuState(sf::RenderWindow* window,
        std::stack<State*>* states,
        MusicPlayer* musicPlayer = nullptr);
    ~PauseMenuState() = default;

    void update() override;
    void render(sf::RenderTarget* target = nullptr) override;
    void endState() override;

private:
    void initOverlay();
    void initPanel();

    sf::RectangleShape overlay;   // fullscreen dark tint
    UiPanel panel;

    MusicPlayer* musicPlayer = nullptr;  // non-owning; forwarded to SettingsMenuState

    bool escWasDown = false;      // edge-detect for ESC toggle
    bool escReleasedOnce = false;
};