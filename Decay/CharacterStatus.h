#pragma once

#include <string>
#include <vector>

class CharacterStatus
{
public:
    // Temporary stat multiplier (buff/debuff). Exposed publicly so UI code
    // (status effect indicators) can enumerate what's currently active —
    // CharacterStatus itself stays presentation-agnostic.
    struct TemporaryStatMultiplier
    {
        std::string id;
        std::string stat;
        float multiplier = 1.f;
        int turnsRemaining = 0;
    };

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

    // Read-only view of currently active multipliers, for status-effect UI
    const std::vector<TemporaryStatMultiplier>& getTemporaryStatMultipliers() const
    {
        return this->temporaryStatMultipliers;
    }

    void clear();

private:
    int stunTurns = 0;
    int actionLockTurns = 0;

    std::vector<TemporaryStatMultiplier> temporaryStatMultipliers;
};