#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class Inventory
{
public:
    enum class ItemCategory
    {
        Material,
        Consumable,
        Equipment,
        KeyItem,
        QuestItem,
        Misc
    };

    struct ItemDefinition
    {
        std::string id;
        std::string displayName;
        std::string description;

        ItemCategory category = ItemCategory::Misc;

        int maxStack = 99;
        bool usable = false;
        bool keyItem = false;
    };

    struct ItemStack
    {
        std::string itemId;
        int quantity = 0;
    };

public:
    // Compatibility singleton.
    // This lets your current states/systems access Inventory easily for now.
    static Inventory& getInstance();

    // Keep constructor public so this can later move into GameContext cleanly.
    Inventory() = default;

    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    // Definition functions
    bool registerItem(const ItemDefinition& definition);
    bool isItemRegistered(const std::string& itemId) const;
    const ItemDefinition* getItemDefinition(const std::string& itemId) const;

    // Inventory functions
    bool loadItemDefinitionsFromFile(const std::string& filePath);
    bool addItem(const std::string& itemId, int quantity = 1);
    bool removeItem(const std::string& itemId, int quantity = 1);
    bool consumeItem(const std::string& itemId, int quantity = 1);
    void addGold(int amount);
    void addExperience(int amount);

    int getGold() const;
    int getExperience() const;
    bool spendGold(int amount);

    bool hasItem(const std::string& itemId, int quantity = 1) const;
    int getQuantity(const std::string& itemId) const;

    bool isEmpty() const;
    void clear();

    // Useful for UI / save systems
    std::vector<ItemStack> getAllStacks() const;
    std::vector<ItemStack> getStacksByCategory(ItemCategory category) const;

private:
    ItemCategory stringToCategory(const std::string& category) const;
    bool stringToBool(const std::string& value) const;
    bool isValidQuantity(int quantity) const;
    int getMaxStackForItem(const std::string& itemId) const;

private:
    int gold = 0;
    int experience = 0;

    std::unordered_map<std::string, ItemDefinition> itemDefinitions;
    std::unordered_map<std::string, int> itemQuantities;
};