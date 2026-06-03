#include "MainMenuState.h"
#include "TravelState.h"
#include "SettingsMenuState.h"

#include <iostream>
#include <memory>

// Constructors and Destructors
MainMenuState::MainMenuState(sf::RenderWindow* window,
    std::stack<State*>* states,
    MusicPlayer* musicPlayer)
    : State(window, states)
    , musicPlayer(musicPlayer)
{
    this->initUi();
    this->initCharacters();
}

// State Functions
void MainMenuState::endState()
{
    std::cout << "Ending MainMenuState!~" << "\n";
}

void MainMenuState::updateKeybinds()
{
    this->checkForQuit();
}

void MainMenuState::update()
{
    this->checkForQuit();
    this->updateMousePositions();
    this->updateKeybinds();

    this->ui.update(this->getMousePosView());

    if (this->ui.button("GAME_STATE").isPressed()) {
        this->states->push(new TravelState(this->window, this->states));
        std::cout << "Starting gamestate!" << "\n";
    }

    if (this->ui.button("SETTINGS_STATE").isPressed()) {
        this->states->push(new SettingsMenuState(this->window, this->states, this->musicPlayer));
    }

    if (this->ui.button("EXIT_STATE").isPressed()) {
        this->quit = true;
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    this->ui.render(*target);
}

// UI Functions
void MainMenuState::initUi()
{
    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(150, 150, 150, 255);
    const sf::Color active(20, 20, 20, 70);

    this->ui.addSprite("MAIN_MENU_LOGO", std::make_unique<UiSprite>(
        "main_menu_logo",
        1600,
        50,
        0.2f,
        0.2f,
        false
    ));

    this->ui.addButton("GAME_STATE", std::make_unique<Button>(
        100, 100, 100, 25, 0.5f, "Start",
        idle,
        hover,
        active,
        false
    ));

    this->ui.addButton("SETTINGS_STATE", std::make_unique<Button>(
        100, 150, 100, 25, 0.5f, "Settings",
        idle,
        hover,
        active,
        false
    ));

    this->ui.addButton("EXIT_STATE", std::make_unique<Button>(
        100, 175, 100, 25, 0.5f, "Quit",
        idle,
        hover,
        active,
        false
    ));

    this->ui.addAnimation("DECAY_LOGO_ANIMATION", std::make_unique<AnimationPlayer>());

    //Animations
    auto decayLogo = std::make_unique<AnimationPlayer>();

    decayLogo->setFramesFromTextureIds({ "decay_menu_1","decay_menu_2","decay_menu_3","decay_menu_4","decay_menu_5","decay_menu_6" });

    decayLogo->setFrameTimes({
        1.65f, // slow hold
        1.60f, // slow hold
        1.55f, // slow hold
        0.57f, // drip starts moving
        0.57f, // fast
        0.55f  // fastest
        });

    decayLogo->setLooping(true);
    decayLogo->fitInside(560.f, 5.f, 800.f, 800.f, 0.f);
    decayLogo->play();

    this->ui.addAnimation("DECAY_LOGO_ANIMATION", std::move(decayLogo));
}
// Character Functions
void MainMenuState::initCharacters()
{
    InitializeCharacters::getInstance().initialize();
}