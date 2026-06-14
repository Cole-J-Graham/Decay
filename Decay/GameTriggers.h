#pragma once

// ---------------------------------------------------------------------------
// GameTriggers
// One static call at game startup wires every trigger registration.
// All "what happens when X fires" logic lives here — not scattered in states.
//
// To add a new trigger:
//   1. Pick a key string (e.g. "plateau_first_visit")
//   2. Add a TriggerManager::getInstance().on(...) block below in registerAll()
//   3. Call TriggerManager::getInstance().fire("plateau_first_visit") from
//      whatever state detects that moment
// ---------------------------------------------------------------------------

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class GameTriggers
{
public:
    static void registerAll();
    static void renderNotification(sf::RenderTarget* target);
    static void showMoveUnlockNotification(const std::string& moveName);

    // General-purpose notification used by the event/reward system
    // (GIVE_*/TAKE_* beats fire these for things like "+50 Gold",
    // "Obtained: Health Potion x1", "-10 HP"). Notifications queue —
    // if one is already showing, new ones wait their turn rather than
    // overwriting it.
    static void showNotification(const std::string& message, float durationSeconds = 3.f);
};