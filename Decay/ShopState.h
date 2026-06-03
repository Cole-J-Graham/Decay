#pragma once

#include "State.h"
#include "UiPanel.h"
#include "ShopDatabase.h"
#include "EventManager.h"
#include "GameFlags.h"
#include "TriggerManager.h"

class ShopState : public State
{
public:
    ShopState(sf::RenderWindow* window, std::stack<State*>* states);
    ~ShopState() = default;

    // State interface
    void endState();
    void updateKeybinds();
    void update();
    void render(sf::RenderTarget* target = nullptr);

private:
    // ── UI ────────────────────────────────────────────────────────────
    void initUi();

    // Populate the list panels from current data; call once in init
    // and again after any buy/sell transaction.
    void refreshShopList();
    void refreshInventoryList();

    // ── Transactions ──────────────────────────────────────────────────
    void tryBuy(const std::string& itemId);
    void trySell(const std::string& itemId);

    // ── Scroll helpers ────────────────────────────────────────────────
    void scrollShop(int delta);   // +1 = down, -1 = up
    void scrollInventory(int delta);

    // ── List-row rendering ────────────────────────────────────────────
    // Draws one text row inside a column; returns the y-pos after the row.
    float renderListRow(sf::RenderTarget* target,
        const std::string& label,
        const std::string& price,
        float x, float y, float w,
        bool highlight,
        sf::Color textColour = sf::Color(220, 200, 170, 255));

private:
    UiPanel ui;

    // ── Doctor intro event ────────────────────────────────────────────
    // Constructed only on first visit (flag "doctor_intro_played" not set).
    // Runs to completion before the shop UI becomes interactive.
    // Fires "doctor_intro_complete" when done, which sets the flag via GameTriggers.
    std::unique_ptr<EventManager> introEvent;

    // ── Shop list state ───────────────────────────────────────────────
    // Items currently visible in the buy list (subset of ShopDatabase)
    std::vector<std::string> shopItemIds;   // ordered for display
    int shopScrollOffset = 0;
    int shopSelectedIndex = -1;           // index into shopItemIds
    static constexpr int kVisibleRows = 10;

    // ── Inventory list state ──────────────────────────────────────────
    // Player items eligible for selling (id + count snapshot)
    struct SellEntry { std::string itemId; int count = 0; };
    std::vector<SellEntry> sellEntries;
    int invScrollOffset = 0;
    int invSelectedIndex = -1;             // index into sellEntries

    // ── Feedback message ──────────────────────────────────────────────
    std::string feedbackMessage = "The slot in the door slides open.";
};