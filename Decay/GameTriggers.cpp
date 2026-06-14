#include "GameTriggers.h"
#include "TriggerManager.h"
#include "GameFlags.h"
#include "Text.h"
#include <iostream>
#include <memory>
#include <deque>
#include <utility>

// ---------------------------------------------------------------------------
// Notification helper
// ---------------------------------------------------------------------------

namespace
{
    std::unique_ptr<Text> gNotification;

    // Pending notifications waiting to be shown. Each entry is
    // (message, durationSeconds). The active notification's remaining
    // time is tracked separately so multiple GIVE_*/TAKE_* beats firing
    // back-to-back queue up instead of overwriting each other.
    std::deque<std::pair<std::string, float>> gNotificationQueue;
    float gNotificationTimeRemaining = 0.f;
    sf::Clock gNotificationClock;

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

    void enqueueNotification(const std::string& message, float durationSeconds)
    {
        ensureNotification();
        gNotificationQueue.emplace_back(message, durationSeconds);
    }

    void updateNotificationQueue()
    {
        const float elapsed = gNotificationClock.restart().asSeconds();

        if (gNotificationTimeRemaining > 0.f) {
            gNotificationTimeRemaining -= elapsed;
            return;
        }

        if (!gNotificationQueue.empty()) {
            const auto next = gNotificationQueue.front();
            gNotificationQueue.pop_front();

            gNotification->showFor(next.first, next.second);
            gNotificationTimeRemaining = next.second;
        }
    }
}

void GameTriggers::renderNotification(sf::RenderTarget* target)
{
    ensureNotification();
    updateNotificationQueue();
    gNotification->render(target);
}

void GameTriggers::showMoveUnlockNotification(const std::string& moveName)
{
    std::cout << "MOVE UNLOCK NOTIFICATION: " << moveName << "\n";
    enqueueNotification("New move unlocked: " + moveName, 6.f);
}

void GameTriggers::showNotification(const std::string& message, float durationSeconds)
{
    enqueueNotification(message, durationSeconds);
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
            enqueueNotification("Strange noises echo from within the medical ward...", 6.f);
        });

    // ── Map unlock notifications ──────────────────────────────────────────
    triggers.on("map_unlocked:Plateau", []()
        {
            auto& flags = GameFlags::getInstance();
            if (flags.has("plateau_unlock_notified")) return;
            flags.set("plateau_unlock_notified");
            enqueueNotification("New location unlocked: Plateau", 6.f);
        });

    // Add further map unlock notifications here:
    // triggers.on("map_unlocked:NextMapName", []() { ... });

    // ── Doctor intro complete ─────────────────────────────────────────────
    triggers.on("doctor_intro_complete", []()
        {
            GameFlags::getInstance().set("doctor_intro_played");
        });
}