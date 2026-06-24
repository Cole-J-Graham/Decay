#include "MainMenuState.h"
#include "IntroState.h"
#include "TravelState.h"
#include "SettingsMenuState.h"
#include "SaveSlotState.h"
#include "MusicManager.h"

#include <iostream>
#include <memory>

// ── Constructor ───────────────────────────────────────────────────────────

MainMenuState::MainMenuState(sf::RenderWindow* window,
    std::stack<State*>* states,
    MusicPlayer* musicPlayer)
    : State(window, states)
    , musicPlayer(musicPlayer)
{
    this->initUi();
    this->initCharacters();
    MusicManager::getInstance().play("main_title");
}

// ── State Functions ───────────────────────────────────────────────────────

void MainMenuState::endState()
{
    std::cout << "Ending MainMenuState!~\n";
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
        this->states->push(new IntroState(this->window, this->states, this->musicPlayer));
        std::cout << "Starting intro!\n";
    }

    if (this->ui.button("SETTINGS_STATE").isPressed()) {
        this->states->push(new SettingsMenuState(this->window, this->states, this->musicPlayer));
    }

    if (this->ui.button("EXIT_STATE").isPressed()) {
        this->quit = true;
    }

    if (this->ui.button("LOAD_STATE").isPressed()) {
        this->states->push(new SaveSlotState(this->window, this->states, SaveSlotState::Mode::Load));
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;
    this->ui.render(*target);
}

// ── UI Functions ──────────────────────────────────────────────────────────

void MainMenuState::initUi()
{
    // ── Palette ───────────────────────────────────────────────────────
    const sf::Color btnIdle(20, 20, 20, 180);
    const sf::Color btnHover(80, 80, 80, 255);
    const sf::Color btnActive(10, 10, 10, 220);

    // ── Center animation — same as before ─────────────────────────────
    {
        auto anim = std::make_unique<AnimationPlayer>();
        anim->setFramesFromTextureIds({
            "decay_menu_1", "decay_menu_2", "decay_menu_3",
            "decay_menu_4", "decay_menu_5", "decay_menu_6"
            });
        anim->setFrameTimes({ 1.65f, 1.60f, 1.55f, 0.57f, 0.57f, 0.55f });
        anim->setLooping(true);
        anim->fitInside(560.f, 5.f, 800.f, 800.f, 0.f);
        anim->play();
        this->ui.addAnimation("DECAY_LOGO_ANIMATION", std::move(anim));
    }

    // ── Top-right logo ─────────────────────────────────────────────────
    this->ui.addSprite("MAIN_MENU_LOGO", std::make_unique<UiSprite>(
        "main_menu_logo", 1600.f, 50.f, 0.2f, 0.2f, false));

    // ── Left panel — thin vertical rule + bottom-anchored buttons ─────
    // Vertical separator between left column and the center animation
    this->ui.addRectangle("LEFT_RULE", std::make_unique<Rectangle>(
        555.f, 0.f, 1.f, 1080.f,
        sf::Color(255, 255, 255, 18), sf::Color::Transparent, 0.f, false));

    // Horizontal rule above buttons
    this->ui.addRectangle("BTN_RULE_TOP", std::make_unique<Rectangle>(
        40.f, 820.f, 460.f, 1.f,
        sf::Color(255, 255, 255, 40), sf::Color::Transparent, 0.f, false));

    // Horizontal rule below buttons
    this->ui.addRectangle("BTN_RULE_BOTTOM", std::make_unique<Rectangle>(
        40.f, 1010.f, 460.f, 1.f,
        sf::Color(255, 255, 255, 20), sf::Color::Transparent, 0.f, false));

    // ── Game title + flavour text — upper-left ─────────────────────────
    this->ui.addText("GAME_SUBTITLE", std::make_unique<Text>(
        50.f, 122.f, 13,
        "The world did not end all at once...",
        sf::Color(140, 140, 140, 160), false));

    this->ui.addRectangle("TITLE_RULE", std::make_unique<Rectangle>(
        48.f, 148.f, 200.f, 1.f,
        sf::Color(255, 255, 255, 40), sf::Color::Transparent, 0.f, false));

    // ── Buttons — bottom-left, evenly spaced ──────────────────────────
    const float btnX = 48.f;
    const float btnW = 200.f;
    const float btnH = 32.f;
    const float btnGap = 14.f;
    float btnY = 836.f;

    this->ui.addButton("GAME_STATE", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "New Game",
        btnIdle, btnHover, btnActive, false));

    btnY += btnH + btnGap;
    this->ui.addButton("LOAD_STATE", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "Load Game",
        btnIdle, btnHover, btnActive, false));

    btnY += btnH + btnGap;
    this->ui.addButton("SETTINGS_STATE", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "Settings",
        btnIdle, btnHover, btnActive, false));

    btnY += btnH + btnGap;
    this->ui.addButton("EXIT_STATE", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "Quit",
        btnIdle, btnHover, btnActive, false));

    // ── Version stamp — very bottom-left ──────────────────────────────
    this->ui.addText("VERSION", std::make_unique<Text>(
        48.f, 1055.f, 10,
        "Early Access",
        sf::Color(100, 90, 75, 120), false));
}

// ── Character Functions ───────────────────────────────────────────────────

void MainMenuState::initCharacters()
{
    InitializeCharacters::getInstance().initialize();
}