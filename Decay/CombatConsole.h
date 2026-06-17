#pragma once

// ---------------------------------------------------------------------------
// CombatConsole
// Owns the UiPanel for CombatState and all UI-level helpers:
//   - Combat console (message bar, click-to-continue)
//   - Turn indicator
//   - Defeat panel (return to bonfire / load save buttons)
//
// CombatState holds one of these and delegates all panel access through it.
// This keeps CombatState free of UI boilerplate.
// ---------------------------------------------------------------------------

#include "UiPanel.h"
#include <string>

class CombatConsole
{
public:
    CombatConsole();

    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget& target);

    // ── Combat console ────────────────────────────────────────────────
    void enableContinue();
    void disableContinue();
    bool continueClicked() const;

    void setMessage(const std::string& msg);
    void showMessage();
    void hideMessage();

    void setTurnIndicator(const std::string& text);

    // ── Defeat panel ──────────────────────────────────────────────────
    void showDefeatPanel();
    void hideDefeatPanel();

    bool defeatBonfireClicked() const;
    bool defeatLoadClicked()    const;

    // ── Visibility helpers used by resetCombat ────────────────────────
    void showConsoleBackground();
    void hideConsoleBackground();

private:
    void initUi();

    UiPanel ui;
    bool    consoleActive = false;
};