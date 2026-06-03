#include "Inventory.h"

#include <algorithm>

// Singleton
Inventory& Inventory::getInstance()
{
    static Inventory instance;
    return instance;
}

// Definition functions
bool Inventory::registerItem(const ItemDefinition& definition)
{
    if (definition.id.empty()) {
        return false;
    }

    if (definition.maxStack <= 0) {
        return false;
    }

    this->itemDefinitions[definition.id] = definition;
    return true;
}

bool Inventory::isItemRegistered(const std::string& itemId) const
{
    return this->itemDefinitions.find(itemId) != this->itemDefinitions.end();
}

const Inventory::ItemDefinition* Inventory::getItemDefinition(const std::string& itemId) const
{
    auto it = this->itemDefinitions.find(itemId);

    if (it == this->itemDefinitions.end()) {
        return nullptr;
    }

    return &it->second;
}

// Inventory functions
bool Inventory::loadItemDefinitionsFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open inventory definition file: " << filePath << "\n";
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        // Allows comments in the db file.
        if (line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);
        std::string id;
        std::string displayName;
        std::string category;
        std::string maxStackText;
        std::string usableText;
        std::string keyItemText;
        std::string description;

        std::getline(ss, id, '|');
        std::getline(ss, displayName, '|');
        std::getline(ss, category, '|');
        std::getline(ss, maxStackText, '|');
        std::getline(ss, usableText, '|');
        std::getline(ss, keyItemText, '|');
        std::getline(ss, description);

        if (id.empty() || displayName.empty() || maxStackText.empty()) {
            std::cerr << "Invalid inventory item line: " << line << "\n";
            continue;
        }

        ItemDefinition definition;
        definition.id = id;
        definition.displayName = displayName;
        definition.category = this->stringToCategory(category);
        definition.maxStack = std::stoi(maxStackText);
        definition.usable = this->stringToBool(usableText);
        definition.keyItem = this->stringToBool(keyItemText);
        definition.description = description;

        this->registerItem(definition);
    }

    return true;
}

bool Inventory::addItem(const std::string& itemId, int quantity)
{
    if (!this->isValidQuantity(quantity)) {
        return false;
    }

    if (!this->isItemRegistered(itemId)) {
        return false;
    }

    const int currentQuantity = this->getQuantity(itemId);
    const int maxStack = this->getMaxStackForItem(itemId);

    if (currentQuantity + quantity > maxStack) {
        this->itemQuantities[itemId] = maxStack;
        return true;
    }

    this->itemQuantities[itemId] = currentQuantity + quantity;
    return true;
}

bool Inventory::removeItem(const std::string& itemId, int quantity)
{
    if (!this->isValidQuantity(quantity)) {
        return false;
    }

    auto it = this->itemQuantities.find(itemId);

    if (it == this->itemQuantities.end()) {
        return false;
    }

    if (it->second < quantity) {
        return false;
    }

    it->second -= quantity;

    if (it->second <= 0) {
        this->itemQuantities.erase(it);
    }

    return true;
}

bool Inventory::consumeItem(const std::string& itemId, int quantity)
{
    return this->removeItem(itemId, quantity);
}

bool Inventory::hasItem(const std::string& itemId, int quantity) const
{
    if (!this->isValidQuantity(quantity)) {
        return false;
    }

    return this->getQuantity(itemId) >= quantity;
}

int Inventory::getQuantity(const std::string& itemId) const
{
    auto it = this->itemQuantities.find(itemId);

    if (it == this->itemQuantities.end()) {
        return 0;
    }

    return it->second;
}

bool Inventory::isEmpty() const
{
    return this->itemQuantities.empty();
}

void Inventory::clear()
{
    this->itemQuantities.clear();
}

std::vector<Inventory::ItemStack> Inventory::getAllStacks() const
{
    std::vector<ItemStack> stacks;

    for (const auto& pair : this->itemQuantities) {
        stacks.push_back(ItemStack{ pair.first, pair.second });
    }

    std::sort(stacks.begin(), stacks.end(),
        [](const ItemStack& a, const ItemStack& b)
        {
            return a.itemId < b.itemId;
        });

    return stacks;
}

std::vector<Inventory::ItemStack> Inventory::getStacksByCategory(ItemCategory category) const
{
    std::vector<ItemStack> stacks;

    for (const auto& pair : this->itemQuantities) {
        const ItemDefinition* definition = this->getItemDefinition(pair.first);

        if (definition == nullptr) {
            continue;
        }

        if (definition->category == category) {
            stacks.push_back(ItemStack{ pair.first, pair.second });
        }
    }

    std::sort(stacks.begin(), stacks.end(),
        [](const ItemStack& a, const ItemStack& b)
        {
            return a.itemId < b.itemId;
        });

    return stacks;
}

void Inventory::addGold(int amount)
{
    if (amount > 0) {
        this->gold += amount;
    }
}

void Inventory::addExperience(int amount)
{
    if (amount > 0) {
        this->experience += amount;
    }
}

bool Inventory::spendGold(int amount) {
    if (amount <= 0 || this->gold < amount) return false;
    this->gold -= amount;
    return true;
}

int Inventory::getGold() const
{
    return this->gold;
}

int Inventory::getExperience() const
{
    return this->experience;
}

// Helpers
Inventory::ItemCategory Inventory::stringToCategory(const std::string& category) const
{
    if (category == "Material") {
        return ItemCategory::Material;
    }

    if (category == "Consumable") {
        return ItemCategory::Consumable;
    }

    if (category == "Equipment") {
        return ItemCategory::Equipment;
    }

    if (category == "KeyItem") {
        return ItemCategory::KeyItem;
    }

    if (category == "QuestItem") {
        return ItemCategory::QuestItem;
    }

    return ItemCategory::Misc;
}

bool Inventory::stringToBool(const std::string& value) const
{
    return value == "true" || value == "1" || value == "TRUE";
}

bool Inventory::isValidQuantity(int quantity) const
{
    return quantity > 0;
}

int Inventory::getMaxStackForItem(const std::string& itemId) const
{
    const ItemDefinition* definition = this->getItemDefinition(itemId);

    if (definition == nullptr) {
        return 0;
    }

    return definition->maxStack;
}