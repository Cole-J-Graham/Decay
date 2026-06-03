#include "PauseMenuState.h"
#include "SettingsMenuState.h"

PauseMenuState::PauseMenuState(sf::RenderWindow* window,
    std::stack<State*>* states,
    MusicPlayer* musicPlayer)
    : State(window, states)
    , musicPlayer(musicPlayer)
{
    this->initOverlay();
    this->initPanel();
}

void PauseMenuState::initOverlay()
{
    // Fullscreen semi-transparent black — dims whatever is underneath
    this->overlay.setSize(sf::Vector2f(1920.f, 1080.f));
    this->overlay.setPosition(0.f, 0.f);
    this->overlay.setFillColor(sf::Color(0, 0, 0, 160));
}

void PauseMenuState::initPanel()
{
    const float panelX = 760.f;   // centered in 1920px: (1920 - 400) / 2
    const float panelY = 340.f;   // centered in 1080px: (1080 - 400) / 2
    const float panelW = 400.f;
    const float panelH = 400.f;

    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(100, 130, 100, 200);
    const sf::Color active(20, 20, 20, 70);
    const float btnW = 300.f, btnH = 30.f;  // button dimensions
    const float btnX = panelX + (panelW - 300.f) / 2.f;  // horizontally centered in panel

    // Outer border
    this->panel.addRectangle("BORDER", std::make_unique<Rectangle>(
        panelX, panelY, panelW, panelH,
        sf::Color(10, 10, 10, 220), sf::Color::White, 1.f, false));

    // Header divider
    this->panel.addRectangle("HEADERDIV", std::make_unique<Rectangle>(
        panelX, panelY + 40.f, panelW, 1,
        sf::Color(255, 255, 255, 60), sf::Color::Transparent, 0.f, false));

    // Separator above quit button
    this->panel.addRectangle("FOOTERDIV", std::make_unique<Rectangle>(
        panelX, panelY + panelH - 60.f, panelW, 1,
        sf::Color(255, 255, 255, 30), sf::Color::Transparent, 0.f, false));

    // Title
    this->panel.addText("TITLE", std::make_unique<Text>(
        panelX + 16.f, panelY + 10.f, 13,
        "MENU",
        sf::Color(200, 200, 200, 220), false));

    // ESC hint — top-right of header
    this->panel.addText("ESC_HINT", std::make_unique<Text>(
        panelX + panelW - 56.f, panelY + 10.f, 11,
        "[ esc ]",
        sf::Color(160, 160, 160, 140), false));

    // Continue
    this->panel.addButton("CONTINUE", std::make_unique<Button>(
        btnX, panelY + 60.f, 300.f, 28.f, 0.5f, "Continue",
        idle, hover, active, false));

    // Save (stubbed)
    this->panel.addButton("SAVE", std::make_unique<Button>(
        btnX, panelY + 100.f, 300.f, 28.f, 0.5f, "Save",
        idle, sf::Color(100, 120, 160, 200), active, false));

    // Load (stubbed)
    this->panel.addButton("LOAD", std::make_unique<Button>(
        btnX, panelY + 140.f, 300.f, 28.f, 0.5f, "Load",
        idle, sf::Color(100, 120, 160, 200), active, false));

    // Settings
    this->panel.addButton("SETTINGS", std::make_unique<Button>(
        btnX, panelY + 180.f, 300.f, 28.f, 0.5f, "Settings",
        idle, hover, active, false));

    // Quit — red tint hover to signal danger
    this->panel.addButton("QUIT", std::make_unique<Button>(
        btnX, panelY + panelH - 50.f, 300.f, 28.f, 0.5f, "Quit to Desktop",
        idle, sf::Color(160, 60, 60, 220), active, false));
}

void PauseMenuState::update()
{
    this->updateMousePositions();
    this->panel.update(this->getMousePosView());

    const bool escDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    // Ignore ESC until it has been fully released at least once after opening
    if (!this->escWasDown && escDown && this->escReleasedOnce) {
        this->quit = true;
    }

    if (!escDown) {
        this->escReleasedOnce = true;
    }

    this->escWasDown = escDown;

    if (this->panel.button("CONTINUE").isPressed()) {
        this->quit = true;
    }

    if (this->panel.button("SETTINGS").isPressed()) {
        this->states->push(new SettingsMenuState(
            this->window, this->states, this->musicPlayer, true));
    }

    if (this->panel.button("SAVE").isPressed()) {
        // TODO
    }

    if (this->panel.button("LOAD").isPressed()) {
        // TODO
    }

    if (this->panel.button("QUIT").isPressed()) {
        this->window->close();
    }
}

void PauseMenuState::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    // Draw the overlay first so the panel sits on top
    target->draw(this->overlay);
    this->panel.render(*target);
}

void PauseMenuState::endState()
{
    // Nothing to clean up — UiPanel owns everything via unique_ptr
}