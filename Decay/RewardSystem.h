#pragma once

#include "Inventory.h"
#include "RewardTypes.h"

class RewardSystem
{
public:
    static RewardResult grantRewards(
        const RewardBundle& rewards,
        Inventory& inventory
    );
};