#pragma once

#include <string>
#include <vector>

class CharacterStatus
{
public:
    // Stun
    void stun(int turns);
    bool isStunned() const;
    void consumeStunTurn();
    int getStunTurns() const;

    // Action Lock
    void lockActions(int turns);
    bool isActionLocked() const;
    void consumeActionLockTurn();
    int getActionLockTurns() const;

    // Temporary Stat Multipliers
    void addTemporaryStatMultiplier(
        const std::string& id,
        const std::string& stat,
        float multiplier,
        int durationTurns
    );

    void tickTemporaryEffects();

    float getEffectiveDamage(float baseDamage) const;
    float getEffectiveDefense(float baseDefense) const;

    void clear();

private:
    struct TemporaryStatMultiplier
    {
        std::string id;
        std::string stat;
        float multiplier = 1.f;
        int turnsRemaining = 0;
    };

private:
    int stunTurns = 0;
    int actionLockTurns = 0;

    std::vector<TemporaryStatMultiplier> temporaryStatMultipliers;
};