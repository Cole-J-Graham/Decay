#pragma once
#pragma once

#include "Rectangle.h"
#include "Text.h"
#include "Inventory.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
#include <string>

// ============================================================
//  InventoryPanel
//  Read-only inventory viewer shown during travel, aligned with
//  the Party/Stats panels (same panel region: 1400,50,270,620).
//  Pulls all data from Inventory::getInstance() each refresh —
//  owns no inventory state itself.
// ============================================================

class InventoryPanel
{
public:
    InventoryPanel();
    ~InventoryPanel();

    void update();
    void render(sf::RenderTarget* target);

private:
    void initUi();
    void refreshEntries();
    bool stacksChanged(const std::vector<Inventory::ItemStack>& stacks) const;

    std::map<std::string, std::unique_ptr<Rectangle>> rectangles;
    std::map<std::string, std::unique_ptr<Text>> text;

    // One row per stack — item name (left column) + quantity (right column)
    std::vector<std::unique_ptr<Text>> itemNameTexts;
    std::vector<std::unique_ptr<Text>> itemQuantityTexts;

    // Snapshot used to skip rebuilding rows when nothing has changed
    bool initialized = false;
    int cachedGold = -1;
    std::vector<Inventory::ItemStack> cachedStacks;

    static constexpr float colX = 1410.f;
    static constexpr float qtyX = 1610.f;
    static constexpr float colWidth = 250.f;
    static constexpr float rowHeight = 28.f;
    static constexpr float firstRowY = 105.f;
    static constexpr int maxRows = 20;
};