#include "SettingsMenuState.h"
#include "MusicPlayer.h"
#include "SfxManager.h"
#include "SettingsManager.h"

#include <string>

SettingsMenuState::SettingsMenuState(sf::RenderWindow* window,
    std::stack<State*>* states,
    MusicPlayer* musicPlayer,
    bool                fromPause)
    : State(window, states)
    , musicPlayer(musicPlayer)
    , fromPause(fromPause)
{

    this->initOverlay();
    this->initPanel();
    this->refreshLabels();
}

void SettingsMenuState::initOverlay()
{
    this->overlay.setSize(sf::Vector2f(1920.f, 1080.f));
    this->overlay.setPosition(0.f, 0.f);
    this->overlay.setFillColor(sf::Color(0, 0, 0, 170));
}

void SettingsMenuState::initPanel()
{
    // --- Layout ----------------------------------------------------------
    const float panelW = 420.f;
    const float panelH = 320.f;
    const float panelX = (1920.f - panelW) / 2.f;
    const float panelY = (1080.f - panelH) / 2.f;

    const sf::Color idle(70, 70, 70, 90);
    const sf::Color hover(150, 150, 150, 220);
    const sf::Color active(20, 20, 20, 70);
    const sf::Color escHint(180, 180, 180, 120);

    const float arrowW = 32.f;
    const float arrowH = 26.f;

    // Volume row: [label]  [−][ val ][+]
    const float labelX = panelX + 20.f;
    const float ctrlRightEdge = panelX + panelW - 20.f;
    const float plusX = ctrlRightEdge - arrowW;
    const float valueW = 56.f;
    const float valueX = plusX - valueW - 4.f;
    const float minusX = valueX - arrowW - 4.f;

    const float row1Y = panelY + 80.f;
    const float row2Y = panelY + 140.f;

    // --- Background & dividers -------------------------------------------
    this->panel.addRectangle("BORDER", std::make_unique<Rectangle>(
        panelX, panelY, panelW, panelH,
        sf::Color(10, 10, 10, 225), sf::Color::White, 1.f, false));

    this->panel.addRectangle("HEADERDIV", std::make_unique<Rectangle>(
        panelX, panelY + 42.f, panelW, 1.f,
        sf::Color(255, 255, 255, 55), sf::Color::Transparent, 0.f, false));

    this->panel.addRectangle("FOOTERDIV", std::make_unique<Rectangle>(
        panelX, panelY + panelH - 58.f, panelW, 1.f,
        sf::Color(255, 255, 255, 30), sf::Color::Transparent, 0.f, false));

    // --- Header: title left, ESC hint right ------------------------------
    this->panel.addText("TITLE", std::make_unique<Text>(
        panelX + 16.f, panelY + 12.f, 13,
        "SETTINGS",
        sf::Color(200, 200, 200, 220), false));

    this->panel.addText("ESC_HINT", std::make_unique<Text>(
        panelX + panelW - 56.f, panelY + 12.f, 11,
        "[ esc ]",
        sf::Color(160, 160, 160, 140), false));

    // --- Music row -------------------------------------------------------
    this->panel.addText("MUSIC_LABEL", std::make_unique<Text>(
        labelX, row1Y + 4.f, 12,
        "Music Volume",
        sf::Color(210, 210, 210, 200), false));

    this->panel.addButton("MUSIC_MINUS", std::make_unique<Button>(
        minusX, row1Y, arrowW, arrowH, 0.5f, "-",
        idle, hover, active, false));

    this->panel.addRectangle("MUSIC_VALUE", std::make_unique<Rectangle>(
        "70%",
        sf::Color(255, 255, 255, 200), 12,
        valueX, row1Y, valueW, arrowH,
        sf::Color::Transparent, sf::Color::Transparent, 0.f, false));

    this->panel.addButton("MUSIC_PLUS", std::make_unique<Button>(
        plusX, row1Y, arrowW, arrowH, 0.5f, "+",
        idle, hover, active, false));

    // --- SFX row ---------------------------------------------------------
    this->panel.addText("SFX_LABEL", std::make_unique<Text>(
        labelX, row2Y + 4.f, 12,
        "SFX Volume",
        sf::Color(210, 210, 210, 200), false));

    this->panel.addButton("SFX_MINUS", std::make_unique<Button>(
        minusX, row2Y, arrowW, arrowH, 0.5f, "-",
        idle, hover, active, false));

    this->panel.addRectangle("SFX_VALUE", std::make_unique<Rectangle>(
        "70%",
        sf::Color(255, 255, 255, 200), 12,
        valueX, row2Y, valueW, arrowH,
        sf::Color::Transparent, sf::Color::Transparent, 0.f, false));

    this->panel.addButton("SFX_PLUS", std::make_unique<Button>(
        plusX, row2Y, arrowW, arrowH, 0.5f, "+",
        idle, hover, active, false));

    const float backW = 300.f;
    const float backX = panelX + (panelW - backW) / 2.f;

    this->panel.addButton("BACK", std::make_unique<Button>(
        backX, panelY + panelH - 46.f, backW, 28.f, 0.5f, "Back",
        idle, hover, active, false));
}

void SettingsMenuState::update()
{
    this->updateMousePositions();
    this->panel.update(this->getMousePosView());

    const bool escDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    if (!this->escWasDown && escDown && this->escReleasedOnce) {
        this->closeSettings();
    }
    if (!escDown) {
        this->escReleasedOnce = true;
    }
    this->escWasDown = escDown;

    if (this->panel.button("BACK").isPressed()) {
        this->quit = true;
    }

    if (this->panel.button("MUSIC_MINUS").isPressed()) {
        SettingsManager& settings =
            SettingsManager::getInstance();

        settings.setMusicVolume(
            clampVolume(
                static_cast<int>(settings.getMusicVolume()) - 10
            )
        );
        this->applyMusicVolume();
        this->refreshLabels();
    }
    if (this->panel.button("MUSIC_PLUS").isPressed()) {
        SettingsManager& settings =
            SettingsManager::getInstance();

        settings.setMusicVolume(
            clampVolume(
                static_cast<int>(settings.getMusicVolume()) + 10
            )
        );

        this->applyMusicVolume();
        this->refreshLabels();
        this->applyMusicVolume();
        this->refreshLabels();
    }

    // --- SFX controls ----------------------------------------------------
    if (this->panel.button("SFX_MINUS").isPressed()) {
        SettingsManager& settings =
            SettingsManager::getInstance();

        settings.setSfxVolume(
            clampVolume(
                static_cast<int>(settings.getSfxVolume()) - 10
            )
        );

        this->applySfxVolume();
        this->refreshLabels();
        this->applySfxVolume();
        this->refreshLabels();
    }
    if (this->panel.button("SFX_PLUS").isPressed()) {
        SettingsManager& settings =
            SettingsManager::getInstance();

        settings.setSfxVolume(
            clampVolume(
                static_cast<int>(settings.getSfxVolume()) + 10
            )
        );

        this->applySfxVolume();
        this->refreshLabels();
        this->applySfxVolume();
        this->refreshLabels();
    }
}

void SettingsMenuState::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    target->draw(this->overlay);
    this->panel.render(*target);
}

void SettingsMenuState::endState() {}

int SettingsMenuState::clampVolume(int v)
{
    // Snap to nearest 10 just in case the seed value wasn't on a boundary
    v = ((v + 5) / 10) * 10;
    if (v < 0)   return 0;
    if (v > 300) return 300;
    return v;
}

void SettingsMenuState::applyMusicVolume()
{
    const float volume =
        SettingsManager::getInstance().getMusicVolume();

    if (this->musicPlayer != nullptr)
    {
        this->musicPlayer->setVolume(volume);
    }

    SettingsManager::getInstance().saveToFile();
}

void SettingsMenuState::applySfxVolume()
{
    const float volume =
        SettingsManager::getInstance().getSfxVolume();

    SfxManager::getInstance().setMasterVolume(volume);

    SettingsManager::getInstance().saveToFile();
}

void SettingsMenuState::refreshLabels()
{
    const int musicVolume =
        static_cast<int>(
            SettingsManager::getInstance().getMusicVolume()
            );

    const int sfxVolume =
        static_cast<int>(
            SettingsManager::getInstance().getSfxVolume()
            );

    this->panel.rectangle("MUSIC_VALUE")
        .setText(std::to_string(musicVolume) + "%");

    this->panel.rectangle("SFX_VALUE")
        .setText(std::to_string(sfxVolume) + "%");
}

void SettingsMenuState::closeSettings()
{
    // Always quit this state
    this->quit = true;

    // If we were pushed from the pause menu, also close the pause menu so
    // ESC lands the player straight back in the game.
    if (this->fromPause && this->states != nullptr && !this->states->empty()) {
        State* pauseState = this->states->top();
        // Don't pop here — mark the pause state for removal too.
        // The stack owner (Game::update) drains quit states each frame,
        // so setting quit on the state below us achieves the double-pop.
        pauseState->quit = true;
    }
}