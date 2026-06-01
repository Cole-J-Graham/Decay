#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include "AnimationEffectManager.h"
#include "RewardTypes.h"

// Entities
#include "CharacterManager.h"
#include "Enemy.h"

struct EnemyDefinition
{
    std::string id;
    std::string name;

    float hp;
    float hpMax;
    float damage;
    float defense;
    float scale;

    std::string spritePath;
    std::string viewerPath;

    RewardBundle rewards;
    std::vector<std::string> spawnAreas;
};

class CombatComponent
{
public:
    // Constructors and Destructors
    CombatComponent();
    ~CombatComponent();

    // Core Functions
    void updateCombat(const sf::Vector2f mousePos);
    void renderCombat(sf::RenderTarget* target);
    void initMoves();
    void updateCombatAnimations();
    void renderCombatAnimations(sf::RenderTarget* target);
    void clearCombatAnimations();

    // Character Functions
    void renderCharacters(sf::RenderTarget* target);

    // Enemy Functions
    void renderEnemies(sf::RenderTarget* target);
    bool enemyPool(const std::string& currentArea);
    void resetEnemy();
    void initEnemyMoves();

    // Combat Cleanup Functions
    void clearCurrentEnemy();
    void clearCombatMoves();

    // Area Functions
    void setCurrentArea(const std::string& area);
    const std::string& getCurrentArea() const;

    // Text Functions
    void setEnemyId(const std::string& text);

    // Getters
    const std::string& getEnemyId() const { return this->enemyId; }

    std::map<std::string, Enemy*> enemies;

private:
    void initEnemyDefinitions();
    void playHitAnimationAt(float x, float y, float scaleX = 3.f, float scaleY = 3.f);
    void playEnemyAttackAnimationAt(float x, float y);
    void playSlashAnimation();

private:
    AnimationEffectManager combatAnimations;
    std::string enemyId;
    std::string currentArea = "FOREST";

    std::vector<EnemyDefinition> enemyDefinitions;

    bool movesInitialized;
};