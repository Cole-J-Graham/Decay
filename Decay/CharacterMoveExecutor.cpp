#include "CharacterMoveExecutor.h"

#include "Character.h"
#include "CharacterManager.h"
#include "Enemy.h"
#include "Party.h"

#include <iostream>
#include <limits>

void CharacterMoveExecutor::execute(
    const CharacterMoveDefinition& moveDefinition,
    Character& user,
    Enemy& enemy,
    HitAnimationCallback hitAnimationCallback
)
{
    if (!moveDefinition.poseTexturePath.empty() && moveDefinition.poseDurationTurns > 0) {
        user.playTemporaryPose(
            moveDefinition.poseTexturePath,
            moveDefinition.poseDurationTurns
        );
    }

    for (const auto& effect : moveDefinition.effects) {
        applyEffect(effect, user, enemy, hitAnimationCallback);
    }
}

void CharacterMoveExecutor::applyEffect(
    const MoveEffectDefinition& effect,
    Character& user,
    Enemy& enemy,
    HitAnimationCallback hitAnimationCallback
)
{
    if (effect.type == "DAMAGE") {
        applyDamage(effect, user, enemy, hitAnimationCallback);
        return;
    }

    if (effect.type == "HEAL") {
        applyHeal(effect, user);
        return;
    }

    if (effect.type == "BLOCK") {
        applyBlock(effect, user);
        return;
    }

    if (effect.type == "BUFF_DAMAGE" ||
        effect.type == "BUFF_DEFENSE" ||
        effect.type == "DEBUFF_DAMAGE" ||
        effect.type == "DEBUFF_DEFENSE") {
        applyBuffOrDebuff(effect, user);
        return;
    }

    if (effect.type == "SELF_LOCK") {
        applySelfLock(effect, user);
        return;
    }

    std::cerr << "Unknown character move effect type: " << effect.type << "\n";
}

Character* CharacterMoveExecutor::resolveSingleCharacterTarget(
    const MoveEffectDefinition& effect,
    Character& user
)
{
    if (effect.target == "SELF") {
        return &user;
    }

    if (effect.target == "ALLY_ID") {
        auto character = CharacterManager::getInstance().getCharacter(effect.targetId);

        if (character) {
            return character.get();
        }

        return nullptr;
    }

    if (effect.target == "LOWEST_HP_ALLY") {
        auto& party = CharacterManager::getInstance().getParty();

        Character* lowest = nullptr;
        float lowestRatio = std::numeric_limits<float>::max();

        for (int i = 0; i < party.size(); i++) {
            auto character = party.getCharacter(i);

            if (!character) {
                continue;
            }

            const float maxHp = character->getHpMax();

            if (maxHp <= 0.f) {
                continue;
            }

            const float ratio = character->getHp() / maxHp;

            if (ratio < lowestRatio) {
                lowestRatio = ratio;
                lowest = character.get();
            }
        }

        return lowest;
    }

    return nullptr;
}

void CharacterMoveExecutor::applyDamage(
    const MoveEffectDefinition& effect,
    Character& user,
    Enemy& enemy,
    HitAnimationCallback hitAnimationCallback
)
{
    if (effect.target != "ENEMY") {
        std::cerr << "DAMAGE effect only supports ENEMY target right now." << "\n";
        return;
    }

    const float damage = user.getEffectiveDamage() * effect.value;

    enemy.getHp() -= damage;

    if (enemy.getHp() < 0.f) {
        enemy.getHp() = 0.f;
    }

    if (hitAnimationCallback) {
        hitAnimationCallback();
    }

    std::cout << user.getId() << " dealt " << damage << " damage." << "\n";
}

void CharacterMoveExecutor::applyHeal(
    const MoveEffectDefinition& effect,
    Character& user
)
{
    if (effect.target == "ALL_PARTY") {
        auto& party = CharacterManager::getInstance().getParty();

        for (int i = 0; i < party.size(); i++) {
            auto character = party.getCharacter(i);

            if (character) {
                character->heal(user.getHealing() * effect.value);
            }
        }

        return;
    }

    Character* target = resolveSingleCharacterTarget(effect, user);

    if (target == nullptr) {
        std::cerr << "HEAL effect target not found." << "\n";
        return;
    }

    target->heal(user.getHealing() * effect.value);
}

void CharacterMoveExecutor::applyBlock(
    const MoveEffectDefinition& effect,
    Character& user
)
{
    if (effect.target == "ALL_PARTY") {
        auto& party = CharacterManager::getInstance().getParty();

        for (int i = 0; i < party.size(); i++) {
            auto character = party.getCharacter(i);

            if (character) {
                character->addBlock(effect.value);
            }
        }

        return;
    }

    Character* target = resolveSingleCharacterTarget(effect, user);

    if (target == nullptr) {
        std::cerr << "ADD_BLOCK effect target not found." << "\n";
        return;
    }

    target->addBlock(effect.value);
}

void CharacterMoveExecutor::applyBuffOrDebuff(
    const MoveEffectDefinition& effect,
    Character& user
)
{
    Character* target = resolveSingleCharacterTarget(effect, user);

    if (target == nullptr) {
        std::cerr << "Buff/debuff target not found." << "\n";
        return;
    }

    std::string stat;
    float multiplier = effect.value;

    if (effect.type == "BUFF_DAMAGE") {
        stat = "DAMAGE";
    }
    else if (effect.type == "BUFF_DEFENSE") {
        stat = "DEFENSE";
    }
    else if (effect.type == "DEBUFF_DAMAGE") {
        stat = "DAMAGE";
    }
    else if (effect.type == "DEBUFF_DEFENSE") {
        stat = "DEFENSE";
    }

    target->addTemporaryStatMultiplier(
        effect.type,
        stat,
        multiplier,
        effect.durationTurns
    );
}

void CharacterMoveExecutor::applySelfLock(
    const MoveEffectDefinition& effect,
    Character& user
)
{
    user.lockActions(effect.durationTurns);
}