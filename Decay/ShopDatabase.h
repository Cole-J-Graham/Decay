#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// ── Data ─────────────────────────────────────────────────────────────────────

struct ShopItemDefinition
{
    std::string itemId;
    int         buyPrice = 0;
    float       sellMultiplier = 0.5f;
    int         stock = -1;   // -1 = unlimited
};

// ── Singleton ─────────────────────────────────────────────────────────────────

class ShopDatabase
{
public:
    static ShopDatabase& getInstance();

    // Loads (or reloads) shop.db.  Call once at startup or on demand.
    void load(const std::string& path = "Assets/Data/shop.db");

    // Returns nullptr if itemId isn't in the shop catalogue.
    const ShopItemDefinition* findItem(const std::string& itemId) const;

    const std::vector<ShopItemDefinition>& getAllItems() const;

private:
    ShopDatabase() = default;
    ShopDatabase(const ShopDatabase&) = delete;
    ShopDatabase& operator=(const ShopDatabase&) = delete;

    std::vector<ShopItemDefinition>                    items;
    std::unordered_map<std::string, std::size_t>       index;  // itemId → items[]
};