#include "InventoryPanel.h"

// Constructors and Destructors
InventoryPanel::InventoryPanel()
{
    this->initUi();
}

InventoryPanel::~InventoryPanel()
{}

// Core Functions
void InventoryPanel::update()
{
    this->refreshEntries();
}

void InventoryPanel::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    for (auto& pair : this->rectangles) {
        pair.second->render(target);
    }

    for (auto& pair : this->text) {
        pair.second->render(target);
    }

    for (size_t i = 0; i < this->itemNameTexts.size(); i++)
    {
        float y = firstRowY + static_cast<float>(i) * rowHeight;

        // Alternating row tint
        if (i % 2 == 0) {
            sf::RectangleShape rowBg(sf::Vector2f(colWidth, rowHeight - 2.f));
            rowBg.setPosition(colX, y);
            rowBg.setFillColor(sf::Color(255, 255, 255, 8));
            target->draw(rowBg);
        }

        // Row divider
        sf::RectangleShape divider(sf::Vector2f(colWidth, 1.f));
        divider.setPosition(colX, y - 3.f);
        divider.setFillColor(sf::Color(255, 255, 255, 25));
        target->draw(divider);

        this->itemNameTexts[i]->render(target);
        this->itemQuantityTexts[i]->render(target);
    }
}

// UI Functions
void InventoryPanel::initUi()
{
    // Main panel border — same region as Party/Stats panels
    this->rectangles["INVENTORYMENU"] = std::make_unique<Rectangle>(
        1400, 50, 270, 620,
        sf::Color::Transparent, sf::Color::White, 1.f, false);

    // Thin divider below header bar
    this->rectangles["HEADERDIV"] = std::make_unique<Rectangle>(
        1400, 82, 270, 1,
        sf::Color(255, 255, 255, 60), sf::Color::Transparent, 0.f, false);

    // Title
    this->text["TITLE"] = std::make_unique<Text>(
        1410, 58, 13,
        "INVENTORY",
        sf::Color(200, 200, 200, 220), false);

    // Gold — sits on the title row, right side of the panel
    this->text["GOLD"] = std::make_unique<Text>(
        1550, 58, 13,
        "Gold: 0",
        sf::Color(255, 210, 100, 255), false);

    // Column headers — sit in the band between HEADERDIV (y=82) and first row (y=105)
    this->text["ITEMLABEL"] = std::make_unique<Text>(
        1410, 88, 11,
        "ITEM",
        sf::Color(180, 180, 180, 200), false);

    this->text["QTYLABEL"] = std::make_unique<Text>(
        1610, 88, 11,
        "QTY",
        sf::Color(160, 220, 255, 200), false);
}

// Data Refresh
void InventoryPanel::refreshEntries()
{
    Inventory& inv = Inventory::getInstance();

    const int gold = inv.getGold();
    const std::vector<Inventory::ItemStack> stacks = inv.getAllStacks();

    const bool goldChanged = (gold != this->cachedGold);
    const bool itemsChanged = this->stacksChanged(stacks) || !this->initialized;

    if (goldChanged)
    {
        this->cachedGold = gold;
        this->text["GOLD"]->setString("Gold: " + std::to_string(gold));
    }

    if (!itemsChanged) return;

    this->initialized = true;
    this->cachedStacks = stacks;

    this->itemNameTexts.clear();
    this->itemQuantityTexts.clear();

    if (stacks.empty())
    {
        this->itemNameTexts.push_back(std::make_unique<Text>(
            colX, firstRowY, 12, "Empty", sf::Color(150, 150, 150, 200), false));
        this->itemQuantityTexts.push_back(std::make_unique<Text>(
            qtyX, firstRowY, 12, "", sf::Color(150, 150, 150, 200), false));
        return;
    }

    const bool hasOverflow = static_cast<int>(stacks.size()) > maxRows;
    const int visibleStacks = hasOverflow ? (maxRows - 1) : static_cast<int>(stacks.size());

    for (int i = 0; i < visibleStacks; i++)
    {
        const auto& stack = stacks[i];
        const Inventory::ItemDefinition* def = inv.getItemDefinition(stack.itemId);
        const std::string displayName = (def != nullptr) ? def->displayName : stack.itemId;

        const float y = firstRowY + static_cast<float>(i) * rowHeight;

        this->itemNameTexts.push_back(std::make_unique<Text>(
            colX, y, 12, displayName, sf::Color(220, 220, 220, 255), false));

        this->itemQuantityTexts.push_back(std::make_unique<Text>(
            qtyX, y, 12, "x" + std::to_string(stack.quantity), sf::Color(160, 220, 255, 255), false));
    }

    if (hasOverflow)
    {
        const int remaining = static_cast<int>(stacks.size()) - visibleStacks;
        const float y = firstRowY + static_cast<float>(visibleStacks) * rowHeight;

        this->itemNameTexts.push_back(std::make_unique<Text>(
            colX, y, 12, "+" + std::to_string(remaining) + " more...", sf::Color(150, 150, 150, 200), false));

        this->itemQuantityTexts.push_back(std::make_unique<Text>(
            qtyX, y, 12, "", sf::Color(150, 150, 150, 200), false));
    }
}

bool InventoryPanel::stacksChanged(const std::vector<Inventory::ItemStack>& stacks) const
{
    if (stacks.size() != this->cachedStacks.size()) return true;

    for (size_t i = 0; i < stacks.size(); i++)
    {
        if (stacks[i].itemId != this->cachedStacks[i].itemId) return true;
        if (stacks[i].quantity != this->cachedStacks[i].quantity) return true;
    }

    return false;
}