#pragma once

#include "CharacterMoveTypes.h"

#include <functional>

class Character;
class Enemy;

class CharacterMoveExecutor
{
public:
    using HitAnimationCallback = std::function<void()>;

public:
    static void execute(
        const CharacterMoveDefinition& moveDefinition,
        Character& user,
        Enemy& enemy,
        HitAnimationCallback hitAnimationCallback
    );

private:
    static void applyEffect(
        const MoveEffectDefinition& effect,
        Character& user,
        Enemy& enemy,
        HitAnimationCallback hitAnimationCallback
    );

    static Character* resolveSingleCharacterTarget(
        const MoveEffectDefinition& effect,
        Character& user
    );

    static void applyDamage(
        const MoveEffectDefinition& effect,
        Character& user,
        Enemy& enemy,
        HitAnimationCallback hitAnimationCallback
    );

    static void applyHeal(
        const MoveEffectDefinition& effect,
        Character& user
    );

    static void applyBlock(
        const MoveEffectDefinition& effect,
        Character& user
    );

    static void applyBuffOrDebuff(
        const MoveEffectDefinition& effect,
        Character& user
    );

    static void applySelfLock(
        const MoveEffectDefinition& effect,
        Character& user
    );
};