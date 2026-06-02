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

void CharacterStatus::clear()
{
    this->stunTurns = 0;
    this->actionLockTurns = 0;
    this->temporaryStatMultipliers.clear();
}