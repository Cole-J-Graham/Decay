#pragma once

#include <string>
#include <vector>

struct RewardEntry
{
    std::string itemId;
    int quantity = 1;
};

struct RewardRange
{
    int min = 0;
    int max = 0;
};

struct RewardBundle
{
    std::vector<RewardEntry> items;
    RewardRange gold;
    RewardRange exp;
};

struct RewardResult
{
    bool anyRewardGranted = false;

    int goldGranted = 0;
    int expGranted = 0;

    std::string message;
    std::vector<RewardEntry> grantedRewards;
};