#include "GameTriggers.h"
#include "TriggerManager.h"
#include "GameFlags.h"
#include "Text.h"
#include <memory>

// ---------------------------------------------------------------------------
// Notification helper
// ---------------------------------------------------------------------------

namespace
{
    std::unique_ptr<Text> gNotification;

    void ensureNotification()
    {
        if (!gNotification) {
            gNotification = std::make_unique<Text>(
                20.f, 760.f,
                18,
                "",
                sf::Color(220, 200, 170, 255),
                true
            );
        }
    }

    void showNotification(const std::string& message, float durationSeconds = 5.f)
    {
        ensureNotification();
        gNotification->showFor(message, durationSeconds);
    }
}

void GameTriggers::renderNotification(sf::RenderTarget* target)
{
    ensureNotification();
    gNotification->render(target);
}

// ---------------------------------------------------------------------------
// registerAll
// ---------------------------------------------------------------------------

void GameTriggers::registerAll()
{
    auto& triggers = TriggerManager::getInstance();

    // ── Castle: first visit notification ─────────────────────────────────
    triggers.on("castle_first_visit", []()
        {
            auto& flags = GameFlags::getInstance();
            if (flags.has("castle_visited")) return;
            flags.set("castle_visited");
            showNotification("Strange noises echo from within the medical ward...", 6.f);
        });

    // ── Map unlock notifications ──────────────────────────────────────────
    triggers.on("map_unlocked:Plateau", []()
        {
            auto& flags = GameFlags::getInstance();
            if (flags.has("plateau_unlock_notified")) return;
            flags.set("plateau_unlock_notified");
            showNotification("New location unlocked: Plateau", 6.f);
        });

    // Add further map unlock notifications here:
    // triggers.on("map_unlocked:NextMapName", []() { ... });

    // ── Doctor intro complete ─────────────────────────────────────────────
    triggers.on("doctor_intro_complete", []()
        {
            GameFlags::getInstance().set("doctor_intro_played");
        });
}