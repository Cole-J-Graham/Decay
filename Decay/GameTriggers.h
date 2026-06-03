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

class GameTriggers
{
public:
    static void registerAll();
    static void renderNotification(sf::RenderTarget* target);
};