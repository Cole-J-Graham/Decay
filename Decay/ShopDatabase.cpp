#include "ShopDatabase.h"

#include <fstream>
#include <sstream>
#include <iostream>

ShopDatabase& ShopDatabase::getInstance()
{
    static ShopDatabase instance;
    return instance;
}

void ShopDatabase::load(const std::string& path)
{
    items.clear();
    index.clear();

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "ShopDatabase: cannot open " << path << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Strip leading whitespace
        const std::size_t first = line.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) continue;
        line = line.substr(first);

        // Skip comments and blank lines
        if (line.empty() || line[0] == '#') continue;

        std::istringstream ss(line);
        std::string token;

        ShopItemDefinition def;

        // item_id
        if (!std::getline(ss, token, '|')) continue;
        def.itemId = token;

        // buy_price
        if (!std::getline(ss, token, '|')) continue;
        try { def.buyPrice = std::stoi(token); }
        catch (...) { continue; }

        // sell_multiplier (optional)
        if (std::getline(ss, token, '|')) {
            try { def.sellMultiplier = std::stof(token); }
            catch (...) { def.sellMultiplier = 0.5f; }
        }

        // stock (optional)
        if (std::getline(ss, token, '|')) {
            try { def.stock = std::stoi(token); }
            catch (...) { def.stock = -1; }
        }

        index[def.itemId] = items.size();
        items.push_back(std::move(def));
    }

    std::cout << "ShopDatabase: loaded " << items.size() << " item(s) from " << path << "\n";
}

const ShopItemDefinition* ShopDatabase::findItem(const std::string& itemId) const
{
    auto it = index.find(itemId);
    if (it == index.end()) return nullptr;
    return &items[it->second];
}

const std::vector<ShopItemDefinition>& ShopDatabase::getAllItems() const
{
    return items;
}