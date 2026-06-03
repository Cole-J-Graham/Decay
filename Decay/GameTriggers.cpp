#include "GameTriggers.h"
#include "TriggerManager.h"
#include "GameFlags.h"

// ---------------------------------------------------------------------------
// Notification helper
// We use Text directly rather than a manager — showFor() handles everything.
// A shared singleton-style notification Text lives here so any trigger can
// reach it without states needing to own or pass it.
// ---------------------------------------------------------------------------
#include "Text.h"
#include <memory>

namespace
{
    // A single screen notification Text, positioned bottom-left.
    // States must call GameTriggers::renderNotification() and
    // GameTriggers::updateNotification() each frame.
    std::unique_ptr<Text> gNotification;

    void ensureNotification()
    {
        if (!gNotification) {
            gNotification = std::make_unique<Text>(
                20.f, 760.f,   // x, y  — bottom-left, above the default ticker position
                18,            // character size
                "",
                sf::Color(220, 200, 170, 255),
                true           // hidden by default
            );
        }
    }

    void showNotification(const std::string& message, float durationSeconds = 5.f)
    {
        ensureNotification();
        gNotification->showFor(message, durationSeconds);
    }
}

// ---------------------------------------------------------------------------
// Public accessors — call these from TravelState::render() / update()
// ---------------------------------------------------------------------------

// Forward declarations so GameTriggers.h stays clean
namespace GameTriggerDisplay
{
    void update();
    void render(sf::RenderTarget* target);
}

namespace GameTriggerDisplay
{
    void update()
    {
        // Text::render() calls update() internally, nothing needed here
        // unless you want to do extra logic.
    }
}

void GameTriggers::renderNotification(sf::RenderTarget* target)
{
    ensureNotification();
    gNotification->render(target);
}

// ---------------------------------------------------------------------------
// registerAll — the only place game trigger logic lives
// ---------------------------------------------------------------------------

void GameTriggers::registerAll()
{
    auto& triggers = TriggerManager::getInstance();
    auto& flags = GameFlags::getInstance();

    // ── Castle: first visit notification ────────────────────────────────────
    // Fired from TravelState when the player's current map changes to "castle".
    // The notification hints at the doctor so the player knows the bonfire
    // button label changed.
    triggers.on("castle_first_visit", [&flags]()
        {
            if (flags.has("castle_visited")) return;
            flags.set("castle_visited");

            showNotification(
                "Strange noises echo from within the medical ward...",
                6.f
            );
        });

    // ── Map fully explored: unlock notification ──────────────────────────────
    // Fired from MapViewer::tryUnlockNextMap with the newly unlocked map's
    // display name.  We use a parameterised key pattern:
    //   "map_unlocked:<displayName>"
    // so each new unlock is one more registration here.
    //
    // Castle is unlocked by "none" (always unlocked) in maps.db right now,
    // so this block is a template for future maps that ARE gated.
    // Example: plateau is unlocked when castle is fully explored.
    triggers.on("map_unlocked:Plateau", [&flags]()
        {
            if (flags.has("plateau_unlock_notified")) return;
            flags.set("plateau_unlock_notified");

            showNotification("New location unlocked: Plateau", 6.f);
        });

    // Add further map unlock notifications here, one block each:
    // triggers.on("map_unlocked:NextMapName", [&flags]() { ... });

    // ── Doctor intro: mark it played after BonfireState fires the event ──────
    // BonfireState fires "doctor_intro_complete" when the event manager reports
    // the intro event has finished.  We set the flag here so nothing else needs
    // to know about it.
    triggers.on("doctor_intro_complete", [&flags]()
        {
            flags.set("doctor_intro_played");
        });
}