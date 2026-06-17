#include "EnemyMoveExecutor.h"

#include <iostream>
#include <random>

void EnemyMoveExecutor::execute(
    const EnemyMoveDefinition& moveDefinition,
    Enemy& enemy,
    HitAnimationCallback hitAnimationCallback
)
{
    if (moveDefinition.type == "DAMAGE" && moveDefinition.target == "RANDOM_PARTY") {
        applyDamageToRandomPartyMember(moveDefinition, enemy, hitAnimationCallback);
        return;
    }

    if (moveDefinition.type == "DAMAGE" && moveDefinition.target == "ALL_PARTY") {
        applyDamageToAllPartyMembers(moveDefinition, enemy, hitAnimationCallback);
        return;
    }

    if (moveDefinition.type == "STUN" && moveDefinition.target == "RANDOM_PARTY") {
        applyStunToRandomPartyMember(moveDefinition, hitAnimationCallback);
        return;
    }

    if (moveDefinition.type == "STUN" && moveDefinition.target == "ALL_PARTY") {
        applyStunToAllPartyMembers(moveDefinition, hitAnimationCallback);
        return;
    }

    if (moveDefinition.type == "POISON" && moveDefinition.target == "RANDOM_PARTY") {
        applyPoisonToRandomPartyMember(moveDefinition, hitAnimationCallback);
        return;
    }

    if (moveDefinition.type == "POISON" && moveDefinition.target == "ALL_PARTY") {
        applyPoisonToAllPartyMembers(moveDefinition, hitAnimationCallback);
        return;
    }

    if (moveDefinition.type == "DEBUFF_DAMAGE" || moveDefinition.type == "DEBUFF_DEFENSE") {
        applyDebuffToParty(moveDefinition);
        return;
    }

    std::cerr << "Unknown enemy move behavior. Move: "
        << moveDefinition.id
        << " Type: " << moveDefinition.type
        << " Target: " << moveDefinition.target
        << "\n";
}

std::shared_ptr<Character> EnemyMoveExecutor::getRandomPartyMember()
{
    auto& party = CharacterManager::getInstance().getParty();

    if (party.size() <= 0) {
        std::cerr << "Enemy move failed. Party is empty." << "\n";
        return nullptr;
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(party.size()) - 1);

    return party.getCharacter(dist(rng));
}

void EnemyMoveExecutor::applyDamageToRandomPartyMember(
    const EnemyMoveDefinition& moveDefinition,
    Enemy& enemy,
    HitAnimationCallback hitAnimationCallback
)
{
    auto targetCharacter = getRandomPartyMember();

    if (targetCharacter == nullptr) {
        return;
    }

    const float finalDamage = enemy.getDamage() * moveDefinition.power;

    targetCharacter->takeDamage(finalDamage);

    const sf::Vector2f hitPosition = targetCharacter->getHitEffectPosition();

    if (hitAnimationCallback) {
        hitAnimationCallback(hitPosition.x, hitPosition.y);
    }

    std::cout << "Enemy used " << moveDefinition.id
        << " on " << targetCharacter->getId()
        << " for " << finalDamage << " damage." << "\n";
}

void EnemyMoveExecutor::applyDamageToAllPartyMembers(
    const EnemyMoveDefinition& moveDefinition,
    Enemy& enemy,
    HitAnimationCallback hitAnimationCallback
)
{
    auto& party = CharacterManager::getInstance().getParty();

    if (party.size() <= 0) {
        std::cerr << "Enemy damage-all failed. Party is empty." << "\n";
        return;
    }

    const float finalDamage = enemy.getDamage() * moveDefinition.power;

    for (int i = 0; i < party.size(); i++) {
        auto targetCharacter = party.getCharacter(i);

        if (targetCharacter == nullptr) {
            continue;
        }

        targetCharacter->takeDamage(finalDamage);

        const sf::Vector2f hitPosition = targetCharacter->getHitEffectPosition();

        if (hitAnimationCallback) {
            hitAnimationCallback(hitPosition.x, hitPosition.y);
        }

        std::cout << "Enemy used " << moveDefinition.id
            << " on " << targetCharacter->getId()
            << " for " << finalDamage << " damage." << "\n";
    }
}

void EnemyMoveExecutor::applyStunToRandomPartyMember(
    const EnemyMoveDefinition& moveDefinition,
    HitAnimationCallback hitAnimationCallback
)
{
    auto targetCharacter = getRandomPartyMember();

    if (targetCharacter == nullptr) {
        return;
    }

    const int stunTurns = static_cast<int>(moveDefinition.power);

    targetCharacter->stun(stunTurns);

    const sf::Vector2f hitPosition = targetCharacter->getHitEffectPosition();

    if (hitAnimationCallback) {
        hitAnimationCallback(hitPosition.x, hitPosition.y);
    }

    std::cout << "Enemy used " << moveDefinition.id
        << " and stunned " << targetCharacter->getId()
        << " for " << stunTurns << " turn(s)." << "\n";
}

void EnemyMoveExecutor::applyStunToAllPartyMembers(
    const EnemyMoveDefinition& moveDefinition,
    HitAnimationCallback hitAnimationCallback
)
{
    auto& party = CharacterManager::getInstance().getParty();

    if (party.size() <= 0) {
        std::cerr << "Enemy stun-all failed. Party is empty." << "\n";
        return;
    }

    const int stunTurns = static_cast<int>(moveDefinition.power);

    for (int i = 0; i < party.size(); i++) {
        auto targetCharacter = party.getCharacter(i);

        if (targetCharacter == nullptr) {
            continue;
        }

        targetCharacter->stun(stunTurns);

        const sf::Vector2f hitPosition = targetCharacter->getHitEffectPosition();

        if (hitAnimationCallback) {
            hitAnimationCallback(hitPosition.x, hitPosition.y);
        }

        std::cout << "Enemy used " << moveDefinition.id
            << " and stunned " << targetCharacter->getId()
            << " for " << stunTurns << " turn(s)." << "\n";
    }
}

// ── Poison ────────────────────────────────────────────────────────────────

void EnemyMoveExecutor::applyPoisonToRandomPartyMember(
    const EnemyMoveDefinition& moveDefinition,
    HitAnimationCallback hitAnimationCallback
)
{
    auto target = getRandomPartyMember();
    if (!target) return;

    target->applyPoison(moveDefinition.power, moveDefinition.durationTurns);

    const sf::Vector2f pos = target->getHitEffectPosition();
    if (hitAnimationCallback) hitAnimationCallback(pos.x, pos.y);

    std::cout << "Enemy used " << moveDefinition.id
        << " and poisoned " << target->getId()
        << " for " << moveDefinition.power << " dmg/turn x"
        << moveDefinition.durationTurns << " turns.\n";
}

void EnemyMoveExecutor::applyPoisonToAllPartyMembers(
    const EnemyMoveDefinition& moveDefinition,
    HitAnimationCallback hitAnimationCallback
)
{
    auto& party = CharacterManager::getInstance().getParty();
    if (party.size() <= 0) return;

    for (int i = 0; i < party.size(); i++)
    {
        auto target = party.getCharacter(i);
        if (!target) continue;

        target->applyPoison(moveDefinition.power, moveDefinition.durationTurns);

        const sf::Vector2f pos = target->getHitEffectPosition();
        if (hitAnimationCallback) hitAnimationCallback(pos.x, pos.y);

        std::cout << "Enemy used " << moveDefinition.id
            << " and poisoned " << target->getId()
            << " for " << moveDefinition.power << " dmg/turn x"
            << moveDefinition.durationTurns << " turns.\n";
    }
}

// ── Debuffs ───────────────────────────────────────────────────────────────

void EnemyMoveExecutor::applyDebuffToParty(const EnemyMoveDefinition& moveDefinition)
{
    const std::string stat = (moveDefinition.type == "DEBUFF_DAMAGE") ? "DAMAGE" : "DEFENSE";

    auto& party = CharacterManager::getInstance().getParty();
    if (party.size() <= 0) return;

    for (int i = 0; i < party.size(); i++)
    {
        auto target = party.getCharacter(i);
        if (!target) continue;

        target->addTemporaryStatMultiplier(
            moveDefinition.id,
            stat,
            moveDefinition.power,   // e.g. 0.6 = 40% less damage
            moveDefinition.durationTurns
        );

        std::cout << "Enemy used " << moveDefinition.id
            << " and debuffed " << target->getId()
            << " " << stat << " by x" << moveDefinition.power
            << " for " << moveDefinition.durationTurns << " turns.\n";
    }
}