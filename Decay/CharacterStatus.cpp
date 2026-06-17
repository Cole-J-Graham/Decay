#include "CharacterStatus.h"

#include <algorithm>

void CharacterStatus::stun(int turns)
{
    if (turns <= 0) {
        return;
    }

    this->stunTurns += turns;
}

bool CharacterStatus::isStunned() const
{
    return this->stunTurns > 0;
}

void CharacterStatus::consumeStunTurn()
{
    if (this->stunTurns > 0) {
        this->stunTurns--;
    }
}

int CharacterStatus::getStunTurns() const
{
    return this->stunTurns;
}

void CharacterStatus::lockActions(int turns)
{
    if (turns <= 0) {
        return;
    }

    this->actionLockTurns += turns;
}

bool CharacterStatus::isActionLocked() const
{
    return this->actionLockTurns > 0;
}

void CharacterStatus::consumeActionLockTurn()
{
    if (this->actionLockTurns > 0) {
        this->actionLockTurns--;
    }
}

int CharacterStatus::getActionLockTurns() const
{
    return this->actionLockTurns;
}

void CharacterStatus::addTemporaryStatMultiplier(
    const std::string& id,
    const std::string& stat,
    float multiplier,
    int durationTurns
)
{
    if (durationTurns <= 0) {
        return;
    }

    TemporaryStatMultiplier effect;
    effect.id = id;
    effect.stat = stat;
    effect.multiplier = multiplier;
    effect.turnsRemaining = durationTurns;

    this->temporaryStatMultipliers.push_back(effect);
}

void CharacterStatus::tickTemporaryEffects()
{
    for (auto& effect : this->temporaryStatMultipliers) {
        effect.turnsRemaining--;
    }

    this->temporaryStatMultipliers.erase(
        std::remove_if(
            this->temporaryStatMultipliers.begin(),
            this->temporaryStatMultipliers.end(),
            [](const TemporaryStatMultiplier& effect)
            {
                return effect.turnsRemaining <= 0;
            }
        ),
        this->temporaryStatMultipliers.end()
    );
}

float CharacterStatus::getEffectiveDamage(float baseDamage) const
{
    float result = baseDamage;

    for (const auto& effect : this->temporaryStatMultipliers) {
        if (effect.stat == "DAMAGE") {
            result *= effect.multiplier;
        }
    }

    return result;
}

float CharacterStatus::getEffectiveDefense(float baseDefense) const
{
    float result = baseDefense;

    for (const auto& effect : this->temporaryStatMultipliers) {
        if (effect.stat == "DEFENSE") {
            result *= effect.multiplier;
        }
    }

    return result;
}

// ── Poison ────────────────────────────────────────────────────────────────

void CharacterStatus::applyPoison(float damagePerTurn, int turns)
{
    if (turns <= 0 || damagePerTurn <= 0.f) return;

    // Refresh to the worse of the two — higher damage or longer duration
    this->poisonDamage = std::max(this->poisonDamage, damagePerTurn);
    this->poisonTurns = std::max(this->poisonTurns, turns);
    this->poisonMultiplier = 1.f; // reset multiplier on fresh application
}

void CharacterStatus::buffPoison(float multiplier)
{
    if (multiplier <= 0.f) return;
    this->poisonMultiplier *= multiplier;
}

float CharacterStatus::tickPoison()
{
    if (this->poisonTurns <= 0) return 0.f;

    const float damage = this->poisonDamage * this->poisonMultiplier;
    this->poisonTurns--;

    if (this->poisonTurns <= 0)
    {
        this->poisonDamage = 0.f;
        this->poisonMultiplier = 1.f;
    }

    return damage;
}

// ── Clear ─────────────────────────────────────────────────────────────────

void CharacterStatus::clear()
{
    this->stunTurns = 0;
    this->actionLockTurns = 0;
    this->poisonDamage = 0.f;
    this->poisonTurns = 0;
    this->poisonMultiplier = 1.f;
    this->temporaryStatMultipliers.clear();
}