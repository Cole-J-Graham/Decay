#include "ShopState.h"

#include "Inventory.h"
#include "ShopDatabase.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>

// ── Helpers ───────────────────────────────────────────────────────────────────

static std::string goldStr(int g)
{
    return std::to_string(g) + "g";
}

// ── Constructor ───────────────────────────────────────────────────────────────

ShopState::ShopState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    ShopDatabase::getInstance().load();
    this->initUi();
    this->refreshShopList();
    this->refreshInventoryList();

    // Intro event
    if (!GameFlags::getInstance().has("doctor_intro_played")){ this->introEvent = std::make_unique<EventManager>("Castle", "doctor_intro_played"); }
}

// ── State interface ───────────────────────────────────────────────────────────

void ShopState::endState()
{
    std::cout << "Leaving ShopState.\n";
}

void ShopState::updateKeybinds()
{
    this->checkForQuit();
}

void ShopState::update()
{
    this->updateMousePositions();

    // In ShopState::update(), replace the entire introEvent block with this:
    if (this->introEvent)
    {
        if (this->introEvent->hasFinished())
            this->introEvent.reset();
        else
        {
            this->introEvent->update(this->getMousePosView());
            return;
        }
    }

    this->checkForQuit();
    this->updateKeybinds();
    this->ui.update(this->getMousePosView());

    // ── Leave ──────────────────────────────────────────────────────────────
    if (this->ui.button("LEAVE_SHOP").isPressed()) {
        this->endState();
        if (!this->states->empty()) this->states->pop();
        return;
    }

    // ── Buy ────────────────────────────────────────────────────────────────
    if (this->ui.button("BUY_ITEM").isPressed()) {
        if (this->shopSelectedIndex >= 0 &&
            this->shopSelectedIndex < static_cast<int>(this->shopItemIds.size()))
        {
            this->tryBuy(this->shopItemIds[this->shopSelectedIndex]);
        }
        else {
            feedbackMessage = "Select an item to buy first.";
        }
    }

    // ── Sell ───────────────────────────────────────────────────────────────
    if (this->ui.button("SELL_ITEM").isPressed()) {
        if (this->invSelectedIndex >= 0 &&
            this->invSelectedIndex < static_cast<int>(this->sellEntries.size()))
        {
            this->trySell(this->sellEntries[this->invSelectedIndex].itemId);
        }
        else {
            feedbackMessage = "Select an item to sell first.";
        }
    }

    // ── Shop list row buttons ──────────────────────────────────────────────
    for (int i = 0; i < kVisibleRows; ++i) {
        const std::string btnId = "SHOP_ROW_" + std::to_string(i);
        try {
            if (this->ui.button(btnId).isPressed()) {
                const int realIndex = shopScrollOffset + i;
                if (realIndex < static_cast<int>(shopItemIds.size())) {
                    shopSelectedIndex = realIndex;
                }
            }
        }
        catch (...) {}
    }

    // ── Inventory list row buttons ─────────────────────────────────────────
    for (int i = 0; i < kVisibleRows; ++i) {
        const std::string btnId = "INV_ROW_" + std::to_string(i);
        try {
            if (this->ui.button(btnId).isPressed()) {
                const int realIndex = invScrollOffset + i;
                if (realIndex < static_cast<int>(sellEntries.size())) {
                    invSelectedIndex = realIndex;
                }
            }
        }
        catch (...) {}
    }

    // ── Update feedback text ───────────────────────────────────────────────
    this->ui.text("FEEDBACK_MSG").setString(feedbackMessage);

    // ── Update gold display ────────────────────────────────────────────────
    const int gold = Inventory::getInstance().getGold();
    this->ui.text("GOLD_VALUE").setString(goldStr(gold));
}

void ShopState::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    this->ui.render(*target);

    // ── Draw buy list rows ─────────────────────────────────────────────────
    {
        const float colX = 30.f;
        const float colY = 110.f;
        const float colW = 430.f;
        const float rowH = 28.f;

        for (int i = 0; i < kVisibleRows; ++i) {
            const int realIndex = shopScrollOffset + i;
            if (realIndex >= static_cast<int>(shopItemIds.size())) break;

            const std::string& id = shopItemIds[realIndex];
            const ShopItemDefinition* def = ShopDatabase::getInstance().findItem(id);
            if (!def) continue;

            const float ry = colY + i * rowH;
            const bool  selected = (realIndex == shopSelectedIndex);

            if (selected) {
                sf::RectangleShape hl(sf::Vector2f(colW, rowH - 2.f));
                hl.setPosition(colX, ry);
                hl.setFillColor(sf::Color(220, 140, 60, 50));
                target->draw(hl);
            }

            const std::string stockStr = (def->stock < 0)
                ? "∞"
                : std::to_string(def->stock);

            this->renderListRow(target,
                def->itemId,
                goldStr(def->buyPrice) + "  [" + stockStr + "]",
                colX, ry, colW,
                selected);
        }
    }

    // ── Draw sell / inventory list rows ────────────────────────────────────
    {
        const float colX = 1260.f;
        const float colY = 110.f;
        const float colW = 350.f;
        const float rowH = 28.f;

        for (int i = 0; i < kVisibleRows; ++i) {
            const int realIndex = invScrollOffset + i;
            if (realIndex >= static_cast<int>(sellEntries.size())) break;

            const SellEntry& entry = sellEntries[realIndex];
            const ShopItemDefinition* def = ShopDatabase::getInstance().findItem(entry.itemId);

            const float ry = colY + i * rowH;
            const bool  selected = (realIndex == invSelectedIndex);

            if (selected) {
                sf::RectangleShape hl(sf::Vector2f(colW, rowH - 2.f));
                hl.setPosition(colX, ry);
                hl.setFillColor(sf::Color(80, 180, 80, 50));
                target->draw(hl);
            }

            const int sellPrice = def
                ? static_cast<int>(std::floor(def->buyPrice * def->sellMultiplier))
                : 0;

            this->renderListRow(target,
                entry.itemId + " x" + std::to_string(entry.count),
                goldStr(sellPrice),
                colX, ry, colW,
                selected,
                sf::Color(180, 230, 180, 220));
        }
    }

    // ── Intro event overlay — rendered on top of everything else ───────────
    if (this->introEvent) {
        this->introEvent->render(target);
    }
}

// ── Private: UI setup ─────────────────────────────────────────────────────────

void ShopState::initUi()
{
    const sf::Color border(255, 255, 255, 60);
    const sf::Color divider(255, 255, 255, 40);
    const sf::Color transparent(sf::Color::Transparent);

    const sf::Color btnIdle(60, 90, 55, 160);
    const sf::Color btnHover(100, 200, 80, 255);
    const sf::Color btnActive(28, 50, 20, 200);

    const sf::Color btnBuyIdle(55, 55, 90, 160);
    const sf::Color btnBuyHover(80, 100, 200, 255);
    const sf::Color btnBuyActive(20, 20, 60, 200);

    const sf::Color btnDangerIdle(90, 30, 30, 160);
    const sf::Color btnDangerHover(200, 60, 60, 255);
    const sf::Color btnDangerActive(50, 10, 10, 200);

    // ── Left panel: shop stock ─────────────────────────────────────────────
    this->ui.addRectangle("SHOP_PANEL", std::make_unique<Rectangle>(
        25, 50, 460, 750, transparent, border, 1.f, false));

    this->ui.addText("SHOP_TITLE", std::make_unique<Text>(
        38, 57, 13, "DOCTOR'S STOCK", sf::Color(200, 200, 200, 220), false));

    this->ui.addRectangle("SHOP_HEADER_DIV", std::make_unique<Rectangle>(
        25, 82, 460, 1, divider, transparent, 0.f, false));

    for (int i = 0; i < kVisibleRows; ++i) {
        const float ry = 110.f + i * 28.f;
        this->ui.addButton("SHOP_ROW_" + std::to_string(i),
            std::make_unique<Button>(30.f, ry, 430.f, 26.f, 0.f, "",
                transparent, sf::Color(255, 255, 255, 15), transparent, false));
    }

    this->ui.addButton("BUY_ITEM", std::make_unique<Button>(
        38.f, 750.f, 200.f, 30.f, 0.5f, "Buy Selected",
        btnBuyIdle, btnBuyHover, btnBuyActive, false));

    // ── Centre panel: doctor dialogue ─────────────────────────────────────
    this->ui.addRectangle("CENTRE_PANEL", std::make_unique<Rectangle>(
        500, 50, 910, 750, transparent, border, 1.f, false));

    this->ui.addText("CENTRE_TITLE", std::make_unique<Text>(
        515, 57, 13, "THE MEDICAL WARD", sf::Color(200, 200, 200, 220), false));

    this->ui.addRectangle("CENTRE_HEADER_DIV", std::make_unique<Rectangle>(
        500, 82, 910, 1, divider, transparent, 0.f, false));

    this->ui.addRectangle("DOOR_SLOT_BG", std::make_unique<Rectangle>(
        510, 92, 890, 120, sf::Color(20, 15, 10, 180), sf::Color(255, 200, 100, 60), 1.f, false));

    this->ui.addText("DOCTOR_VOICE", std::make_unique<Text>(
        522, 100, 12,
        "\"Slide your coin through the slot.\n"
        " I'll slide the goods back.\n"
        " No touching. No exceptions.\"",
        sf::Color(200, 180, 140, 230), false));

    this->ui.addRectangle("GOLD_PANEL", std::make_unique<Rectangle>(
        510, 630, 890, 60, sf::Color(30, 25, 10, 160), sf::Color(255, 200, 100, 60), 1.f, false));

    this->ui.addText("GOLD_LABEL", std::make_unique<Text>(
        522, 640, 13, "GOLD:", sf::Color(200, 200, 200, 180), false));

    this->ui.addText("GOLD_VALUE", std::make_unique<Text>(
        590, 640, 15, "0g", sf::Color(255, 210, 80, 255), false));

    this->ui.addRectangle("FEEDBACK_PANEL", std::make_unique<Rectangle>(
        510, 700, 890, 80, transparent, sf::Color(255, 255, 255, 25), 1.f, false));

    this->ui.addText("FEEDBACK_LABEL", std::make_unique<Text>(
        522, 706, 11, "LOG", sf::Color(180, 180, 180, 160), false));

    this->ui.addRectangle("FEEDBACK_DIV", std::make_unique<Rectangle>(
        510, 720, 890, 1, sf::Color(255, 255, 255, 25), transparent, 0.f, false));

    this->ui.addText("FEEDBACK_MSG", std::make_unique<Text>(
        522, 726, 14, feedbackMessage, sf::Color(220, 200, 170, 255), false));

    this->ui.addButton("LEAVE_SHOP", std::make_unique<Button>(
        550.f, 815.f, 200.f, 30.f, 0.5f, "Leave",
        btnDangerIdle, btnDangerHover, btnDangerActive, false));

    // ── Right panel: player inventory ─────────────────────────────────────
    this->ui.addRectangle("INV_PANEL", std::make_unique<Rectangle>(
        1430, 50, 380, 750, transparent, border, 1.f, false));

    this->ui.addText("INV_TITLE", std::make_unique<Text>(
        1443, 57, 13, "YOUR PACK", sf::Color(200, 200, 200, 220), false));

    this->ui.addRectangle("INV_HEADER_DIV", std::make_unique<Rectangle>(
        1430, 82, 380, 1, divider, transparent, 0.f, false));

    for (int i = 0; i < kVisibleRows; ++i) {
        const float ry = 110.f + i * 28.f;
        this->ui.addButton("INV_ROW_" + std::to_string(i),
            std::make_unique<Button>(1435.f, ry, 350.f, 26.f, 0.f, "",
                transparent, sf::Color(255, 255, 255, 15), transparent, false));
    }

    this->ui.addButton("SELL_ITEM", std::make_unique<Button>(
        1493.f, 750.f, 200.f, 30.f, 0.5f, "Sell Selected",
        btnIdle, btnHover, btnActive, false));

    // ── Doctor portrait ───────────────────────────────────────────────────────
    const float portraitX = 1430.f;
    const float portraitY = 420.f;
    const float portraitW = 380.f;
    const float portraitH = 320.f;

    this->ui.addRectangle("DOCTOR_PORTRAIT_BG", std::make_unique<Rectangle>(
        portraitX, portraitY, portraitW, portraitH,
        sf::Color(20, 15, 10, 180), sf::Color::Transparent, 0.f, false));

    this->ui.addRectangle("DOCTOR_PORTRAIT_BORDER", std::make_unique<Rectangle>(
        portraitX, portraitY, portraitW, portraitH,
        sf::Color::Transparent, sf::Color(255, 255, 255, 60), 1.f, false));

    this->ui.addRectangle("DOCTOR_PORTRAIT_ACCENT", std::make_unique<Rectangle>(
        portraitX, portraitY, portraitW, 3.f,
        sf::Color(220, 140, 60, 180), sf::Color::Transparent, 0.f, false));

    this->ui.addSprite("DOCTOR_PORTRAIT", std::make_unique<UiSprite>(
        "doctor_sprite", portraitX, portraitY, 1.f, 1.f, false));
    this->ui.sprite("DOCTOR_PORTRAIT").fitInside(portraitX, portraitY, portraitW, portraitH, 8.f);
}

// ── Private: list refresh ─────────────────────────────────────────────────────

void ShopState::refreshShopList()
{
    shopItemIds.clear();
    for (const auto& def : ShopDatabase::getInstance().getAllItems()) {
        if (def.stock != 0) {
            shopItemIds.push_back(def.itemId);
        }
    }
    shopScrollOffset = 0;
    shopSelectedIndex = -1;
}

void ShopState::refreshInventoryList()
{
    sellEntries.clear();
    for (const auto& stack : Inventory::getInstance().getAllStacks()) {
        if (stack.quantity > 0) {
            sellEntries.push_back({ stack.itemId, stack.quantity });
        }
    }
    invScrollOffset = 0;
    invSelectedIndex = -1;
}

// ── Private: transactions ─────────────────────────────────────────────────────

void ShopState::tryBuy(const std::string& itemId)
{
    const ShopItemDefinition* def = ShopDatabase::getInstance().findItem(itemId);
    if (!def) {
        feedbackMessage = "Unknown item.";
        return;
    }

    auto& inv = Inventory::getInstance();
    if (inv.getGold() < def->buyPrice) {
        feedbackMessage = "Not enough gold.";
        return;
    }

    inv.spendGold(def->buyPrice);
    inv.addItem(itemId, 1);

    if (def->stock > 0) {
        const_cast<ShopItemDefinition*>(def)->stock -= 1;
    }

    feedbackMessage = "Bought " + itemId + " for " + goldStr(def->buyPrice) + ".";
    std::cout << "[Shop] Bought: " << itemId << "\n";

    this->refreshShopList();
    this->refreshInventoryList();
}

void ShopState::trySell(const std::string& itemId)
{
    const ShopItemDefinition* def = ShopDatabase::getInstance().findItem(itemId);
    const int sellPrice = def
        ? static_cast<int>(std::floor(def->buyPrice * def->sellMultiplier))
        : 0;

    if (sellPrice <= 0) {
        feedbackMessage = "He doesn't want that.";
        return;
    }

    auto& inv = Inventory::getInstance();
    inv.removeItem(itemId, 1);
    inv.addGold(sellPrice);

    feedbackMessage = "Sold " + itemId + " for " + goldStr(sellPrice) + ".";
    std::cout << "[Shop] Sold: " << itemId << "\n";

    this->refreshInventoryList();
}

// ── Private: scroll ───────────────────────────────────────────────────────────

void ShopState::scrollShop(int delta)
{
    shopScrollOffset = std::clamp(
        shopScrollOffset + delta,
        0,
        std::max(0, static_cast<int>(shopItemIds.size()) - kVisibleRows));
}

void ShopState::scrollInventory(int delta)
{
    invScrollOffset = std::clamp(
        invScrollOffset + delta,
        0,
        std::max(0, static_cast<int>(sellEntries.size()) - kVisibleRows));
}

// ── Private: list-row helper ──────────────────────────────────────────────────

float ShopState::renderListRow(sf::RenderTarget* target,
    const std::string& label,
    const std::string& price,
    float x, float y, float w,
    bool  highlight,
    sf::Color textColour)
{
    sf::Font& font = AssetDatabase::getInstance().getFont("ticker_font");

    sf::Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(13);
    nameText.setFillColor(textColour);
    nameText.setString(label);
    nameText.setPosition(x + 4.f, y + 4.f);
    target->draw(nameText);

    sf::Text priceText;
    priceText.setFont(font);
    priceText.setCharacterSize(13);
    priceText.setFillColor(sf::Color(255, 210, 80, 200));
    priceText.setString(price);
    const float pw = priceText.getLocalBounds().width;
    priceText.setPosition(x + w - pw - 8.f, y + 4.f);
    target->draw(priceText);

    sf::RectangleShape sep(sf::Vector2f(w, 1.f));
    sep.setPosition(x, y + 27.f);
    sep.setFillColor(sf::Color(255, 255, 255, 15));
    target->draw(sep);

    return y + 28.f;
}