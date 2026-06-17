#pragma once

#include <string>
#include <vector>

class CharacterStatus
{
public:
    // Temporary stat multiplier (buff/debuff).
    struct TemporaryStatMultiplier
    {
        std::string id;
        std::string stat;
        float multiplier = 1.f;
        int   turnsRemaining = 0;
    };

    // ── Stun ──────────────────────────────────────────────────────────
    void stun(int turns);
    bool isStunned() const;
    void consumeStunTurn();
    int  getStunTurns() const;

    // ── Action Lock ───────────────────────────────────────────────────
    void lockActions(int turns);
    bool isActionLocked() const;
    void consumeActionLockTurn();
    int  getActionLockTurns() const;

    // ── Temporary Stat Multipliers (buff / debuff) ────────────────────
    void addTemporaryStatMultiplier(
        const std::string& id,
        const std::string& stat,
        float multiplier,
        int durationTurns
    );
    void  tickTemporaryEffects();
    float getEffectiveDamage(float baseDamage)   const;
    float getEffectiveDefense(float baseDefense) const;

    const std::vector<TemporaryStatMultiplier>& getTemporaryStatMultipliers() const
    {
        return this->temporaryStatMultipliers;
    }

    // ── Poison ────────────────────────────────────────────────────────
    // Apply poison: flat damage per turn for N turns.
    // If already poisoned, refreshes to the worse of the two values.
    void applyPoison(float damagePerTurn, int turns);

    // Multiply the current poison damage (e.g. from a poison-buff move).
    void buffPoison(float multiplier);

    // Called once at the start of a poisoned character's turn.
    // Returns the actual damage dealt (0 if not poisoned).
    float tickPoison();

    bool  isPoisoned()     const { return this->poisonTurns > 0; }
    int   getPoisonTurns() const { return this->poisonTurns; }
    float getPoisonDamage() const { return this->poisonDamage; }

    // ── Clear (new combat) ────────────────────────────────────────────
    void clear();

private:
    int   stunTurns = 0;
    int   actionLockTurns = 0;

    std::vector<TemporaryStatMultiplier> temporaryStatMultipliers;

    // Poison state
    float poisonDamage = 0.f;   // damage dealt per tick
    int   poisonTurns = 0;     // turns remaining
    float poisonMultiplier = 1.f;   // modified by buffPoison
};