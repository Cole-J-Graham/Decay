#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include "State.h"
#include "UiPanel.h"
#include "InitializeCharacters.h"

class MusicPlayer;   // forward declaration — full type only needed in .cpp

class MainMenuState : public State
{
public:
    // Constructors and Destructors
    // Pass an optional MusicPlayer so SettingsMenuState can control its volume.
    MainMenuState(sf::RenderWindow* window,
        std::stack<State*>* states,
        MusicPlayer* musicPlayer = nullptr);
    ~MainMenuState() = default;

    // State Functions
    void endState();
    void updateKeybinds();
    void update();
    void render(sf::RenderTarget* target = nullptr);

private:
    // UI Functions
    void initUi();

    // Character Functions
    void initCharacters();

private:
    UiPanel ui;
    MusicPlayer* musicPlayer = nullptr;   // non-owning; may be nullptr
};

#endif