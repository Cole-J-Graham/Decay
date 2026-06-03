#include "TriggerManager.h"

#include <iostream>

void TriggerManager::on(const std::string& key, std::function<void()> callback)
{
    this->listeners[key].push_back(std::move(callback));
}

void TriggerManager::fire(const std::string& key)
{
    auto it = this->listeners.find(key);
    if (it == this->listeners.end()) {
        return;  // No listeners registered — safe no-op.
    }

    for (auto& callback : it->second) {
        callback();
    }
}