#include "CombatConsole.h"

CombatConsole::CombatConsole()
{
    this->initUi();
}

void CombatConsole::update(sf::Vector2f mousePos)
{
    this->ui.update(mousePos);
}

void CombatConsole::render(sf::RenderTarget& target)
{
    this->ui.render(target);
}

// ── Combat console ────────────────────────────────────────────────────────

void CombatConsole::enableContinue()
{
    if (!this->consoleActive)
    {
        this->consoleActive = true;
        this->ui.button("COMBAT_CONSOLE_CONTINUE").show();
        this->ui.text("COMBAT_CONTINUE_HINT").setShown();
    }
}

void CombatConsole::disableContinue()
{
    this->consoleActive = false;
    this->ui.button("COMBAT_CONSOLE_CONTINUE").setIdle();
    this->ui.button("COMBAT_CONSOLE_CONTINUE").hide();
    this->ui.text("COMBAT_CONTINUE_HINT").setHidden();
}

bool CombatConsole::continueClicked() const
{
    return this->consoleActive &&
        const_cast<UiPanel&>(this->ui).button("COMBAT_CONSOLE_CONTINUE").isPressed();
}

void CombatConsole::setMessage(const std::string& msg)
{
    this->ui.text("COMBAT_MESSAGE").setString(msg);
}

void CombatConsole::showMessage()
{
    this->ui.text("COMBAT_MESSAGE").setShown();
}

void CombatConsole::hideMessage()
{
    this->ui.text("COMBAT_MESSAGE").setHidden();
}

void CombatConsole::setTurnIndicator(const std::string& text)
{
    this->ui.text("TURN_INDICATOR_TEXT").setString(text);
}

// ── Defeat panel ──────────────────────────────────────────────────────────

void CombatConsole::showDefeatPanel()
{
    // Hide normal console
    this->ui.rectangle("COMBATCONSOLE_BG").hide();
    this->ui.rectangle("COMBATCONSOLE_ACCENT").hide();
    this->ui.text("COMBAT_MESSAGE").setHidden();
    this->ui.rectangle("HOSTILEBORDER").hide();

    // Show defeat panel
    this->ui.rectangle("DEFEAT_BG").show();
    this->ui.rectangle("DEFEAT_ACCENT").show();
    this->ui.text("DEFEAT_TITLE").setShown();
    this->ui.text("DEFEAT_SUBTITLE").setShown();
    this->ui.button("DEFEAT_BONFIRE").show();
    this->ui.button("DEFEAT_LOAD").show();
}

void CombatConsole::hideDefeatPanel()
{
    this->ui.rectangle("DEFEAT_BG").hide();
    this->ui.rectangle("DEFEAT_ACCENT").hide();
    this->ui.text("DEFEAT_TITLE").setHidden();
    this->ui.text("DEFEAT_SUBTITLE").setHidden();
    this->ui.button("DEFEAT_BONFIRE").hide();
    this->ui.button("DEFEAT_LOAD").hide();

    // Restore normal console
    this->ui.rectangle("COMBATCONSOLE_BG").show();
    this->ui.rectangle("COMBATCONSOLE_ACCENT").show();
    this->ui.rectangle("HOSTILEBORDER").show();
}

bool CombatConsole::defeatBonfireClicked() const
{
    return const_cast<UiPanel&>(this->ui).button("DEFEAT_BONFIRE").isPressed();
}

bool CombatConsole::defeatLoadClicked() const
{
    return const_cast<UiPanel&>(this->ui).button("DEFEAT_LOAD").isPressed();
}

void CombatConsole::showConsoleBackground()
{
    this->ui.rectangle("COMBATCONSOLE_BG").show();
    this->ui.rectangle("COMBATCONSOLE_ACCENT").show();
}

void CombatConsole::hideConsoleBackground()
{
    this->ui.rectangle("COMBATCONSOLE_BG").hide();
    this->ui.rectangle("COMBATCONSOLE_ACCENT").hide();
}

// ── UI init ───────────────────────────────────────────────────────────────

void CombatConsole::initUi()
{
    // ── Enemy zone border ─────────────────────────────────────────────
    this->ui.addRectangle("HOSTILEBORDER", std::make_unique<Rectangle>(
        1695, 420, 200, 200,
        sf::Color::Transparent, sf::Color(255, 80, 80, 120), 1.f, false));

    // ── Combat console ────────────────────────────────────────────────
    this->ui.addRectangle("COMBATCONSOLE_BG", std::make_unique<Rectangle>(
        350, 825, 1250, 175,
        sf::Color(10, 10, 20, 210), sf::Color(255, 255, 255, 50), 1.f, false));

    this->ui.addRectangle("COMBATCONSOLE_ACCENT", std::make_unique<Rectangle>(
        350, 825, 1250, 2,
        sf::Color(255, 200, 80, 160), sf::Color::Transparent, 0.f, false));

    this->ui.addText("COMBAT_MESSAGE", std::make_unique<Text>(
        355, 835, 16, "", sf::Color::White, true));

    this->ui.addText("COMBAT_CONTINUE_HINT", std::make_unique<Text>(
        1455, 830, 12, "[ Click to continue ]",
        sf::Color(180, 180, 180, 140), true));

    this->ui.addButton("COMBAT_CONSOLE_CONTINUE", std::make_unique<Button>(
        350, 825, 1250, 175, 0.5f, "",
        sf::Color(0, 0, 0, 0), sf::Color(255, 255, 255, 12),
        sf::Color(255, 255, 255, 25), true));

    // ── Turn indicator ────────────────────────────────────────────────
    this->ui.addRectangle("TURN_INDICATOR_BG", std::make_unique<Rectangle>(
        350, 800, 1250, 22,
        sf::Color(20, 20, 35, 200), sf::Color(255, 255, 255, 40), 1.f, false));

    this->ui.addText("TURN_INDICATOR_TEXT", std::make_unique<Text>(
        360, 803, 12, "", sf::Color(160, 220, 255, 220), false));

    // ── Defeat panel — hidden until party wipes ───────────────────────
    this->ui.addRectangle("DEFEAT_BG", std::make_unique<Rectangle>(
        560, 390, 800, 220,
        sf::Color(20, 5, 5, 230), sf::Color(180, 40, 40, 120), 1.f, true));

    this->ui.addRectangle("DEFEAT_ACCENT", std::make_unique<Rectangle>(
        560, 390, 800, 2,
        sf::Color(200, 60, 60, 220), sf::Color::Transparent, 0.f, true));

    this->ui.addText("DEFEAT_TITLE", std::make_unique<Text>(
        760, 405, 22, "THE PARTY HAS FALLEN",
        sf::Color(220, 100, 100, 255), true));

    this->ui.addText("DEFEAT_SUBTITLE", std::make_unique<Text>(
        620, 438, 13,
        "The decay claims another... but perhaps not forever.",
        sf::Color(180, 160, 160, 200), true));

    this->ui.addButton("DEFEAT_BONFIRE", std::make_unique<Button>(
        580, 475, 320, 35, 0.5f, "Return to Last Bonfire",
        sf::Color(80, 40, 20, 180), sf::Color(180, 100, 40, 255),
        sf::Color(40, 20, 10, 200), true));

    this->ui.addButton("DEFEAT_LOAD", std::make_unique<Button>(
        920, 475, 220, 35, 0.5f, "Load Last Save",
        sf::Color(40, 40, 60, 180), sf::Color(100, 100, 180, 255),
        sf::Color(20, 20, 40, 200), true));
}