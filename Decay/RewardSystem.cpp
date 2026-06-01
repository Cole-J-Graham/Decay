#include "RewardSystem.h"

#include <random>
#include <sstream>

namespace
{
    int rollRange(const RewardRange& range)
    {
        if (range.max <= range.min) {
            return range.min;
        }

        static std::random_device dev;
        static std::mt19937 rng(dev());

        std::uniform_int_distribution<int> dist(range.min, range.max);
        return dist(rng);
    }
}

RewardResult RewardSystem::grantRewards(
    const RewardBundle& rewards,
    Inventory& inventory
)
{
    RewardResult result;

    result.goldGranted = rollRange(rewards.gold);
    result.expGranted = rollRange(rewards.exp);

    inventory.addGold(result.goldGranted);

    if (result.goldGranted > 0 || result.expGranted > 0) {
        result.anyRewardGranted = true;
    }

    for (const auto& reward : rewards.items) {
        if (reward.itemId.empty() || reward.quantity <= 0) {
            continue;
        }

        if (!inventory.addItem(reward.itemId, reward.quantity)) {
            continue;
        }

        result.grantedRewards.push_back(reward);
        result.anyRewardGranted = true;
    }

    std::ostringstream message;
    message << "Rewards acquired:";

    if (result.goldGranted > 0) {
        message << "\n- Gold x" << result.goldGranted;
    }

    if (result.expGranted > 0) {
        message << "\n- EXP x" << result.expGranted;
    }

    for (const auto& reward : result.grantedRewards) {
        const Inventory::ItemDefinition* definition =
            inventory.getItemDefinition(reward.itemId);

        if (definition != nullptr) {
            message << "\n- " << definition->displayName << " x" << reward.quantity;
        }
        else {
            message << "\n- " << reward.itemId << " x" << reward.quantity;
        }
    }

    result.message = message.str();
    return result;
}