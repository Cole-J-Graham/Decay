#pragma once

#include <vector>
#include <string>
#include <memory>

// Singleton class for managing the player's inventory
class Inventory {
public:
    // Nested Item class
    class Item {
    public:
        // Constructor
        Item(const std::string& name, int quantity)
            : name(name), quantity(quantity) {}

        // Getters
        std::string getName() const { return name; }
        int getQuantity() const { return quantity; }

        // Setters
        void setQuantity(int qty) { quantity = qty; }

    private:
        std::string name;
        int quantity;
    };

    // Static method to access the singleton instance
    static Inventory& getInstance() {
        static Inventory instance;
        return instance;
    }

    // Delete copy constructor and assignment operator
    Inventory(const Inventory&) = delete;
    void operator=(const Inventory&) = delete;

    // Add an item to the inventory
    void addItem(const Item& item) {
        inventory.push_back(item);
    }

    // Remove an item from the inventory by name
    void removeItem(const std::string& itemName) {
        inventory.erase(
            std::remove_if(inventory.begin(), inventory.end(),
                [&](const Item& item) { return item.getName() == itemName; }),
            inventory.end());
    }

    // Get the list of items in the inventory
    const std::vector<Item>& getItems() const { return inventory; }

private:
    // Private constructor for singleton pattern
    Inventory() {}

    // Inventory data
    std::vector<Item> inventory;
};