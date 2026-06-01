#pragma once

#include "EnemyTypes.h"
#include "CharacterManager.h"
#include "Enemy.h"

#include <SFML/System/Vector2.hpp>

#include <functional>
#include <memory>
#include <string>

class EnemyMoveExecutor
{
public:
    using HitAnimationCallback = std::function<void(float x, float y)>;

public:
    static void execute(
        const EnemyMoveDefinition& moveDefinition,
        Enemy& enemy,
        HitAnimationCallback hitAnimationCallback
    );

private:
    static std::shared_ptr<Character> getRandomPartyMember();

    static void applyDamageToRandomPartyMember(
        const EnemyMoveDefinition& moveDefinition,
        Enemy& enemy,
        HitAnimationCallback hitAnimationCallback
    );

    static void applyDamageToAllPartyMembers(
        const EnemyMoveDefinition& moveDefinition,
        Enemy& enemy,
        HitAnimationCallback hitAnimationCallback
    );

    static void applyStunToRandomPartyMember(
        const EnemyMoveDefinition& moveDefinition,
        HitAnimationCallback hitAnimationCallback
    );

    static void applyStunToAllPartyMembers(
        const EnemyMoveDefinition& moveDefinition,
        HitAnimationCallback hitAnimationCallback
    );
};