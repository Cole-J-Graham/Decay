#pragma once

#include "EnemyTypes.h"
#include "CharacterManager.h"
#include "Enemy.h"

#include <functional>
#include <memory>

class EnemyMoveExecutor
{
public:
    using HitAnimationCallback = std::function<void(float x, float y)>;

    static void execute(
        const EnemyMoveDefinition& moveDefinition,
        Enemy& enemy,
        HitAnimationCallback hitAnimationCallback
    );

private:
    static std::shared_ptr<Character> getRandomPartyMember();

    // Damage
    static void applyDamageToRandomPartyMember(
        const EnemyMoveDefinition& moveDefinition,
        Enemy& enemy,
        HitAnimationCallback hitAnimationCallback);

    static void applyDamageToAllPartyMembers(
        const EnemyMoveDefinition& moveDefinition,
        Enemy& enemy,
        HitAnimationCallback hitAnimationCallback);

    // Stun
    static void applyStunToRandomPartyMember(
        const EnemyMoveDefinition& moveDefinition,
        HitAnimationCallback hitAnimationCallback);

    static void applyStunToAllPartyMembers(
        const EnemyMoveDefinition& moveDefinition,
        HitAnimationCallback hitAnimationCallback);

    // Poison
    static void applyPoisonToRandomPartyMember(
        const EnemyMoveDefinition& moveDefinition,
        HitAnimationCallback hitAnimationCallback);

    static void applyPoisonToAllPartyMembers(
        const EnemyMoveDefinition& moveDefinition,
        HitAnimationCallback hitAnimationCallback);

    // Debuff (DEBUFF_DAMAGE / DEBUFF_DEFENSE — always targets ALL_PARTY)
    static void applyDebuffToParty(const EnemyMoveDefinition& moveDefinition);
};