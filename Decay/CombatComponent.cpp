#include "CombatComponent.h"

#include <iostream>

// Constructors and Destructors
CombatComponent::CombatComponent()
{
    this->enemyId = "";
    this->currentArea = "FOREST";
    this->movesInitialized = false;

    this->initEnemyDefinitions();
}

CombatComponent::~CombatComponent()
{
    for (auto& enemy : this->enemies) {
        delete enemy.second;
        enemy.second = nullptr;
    }

    this->enemies.clear();
}

// Core Functions
void CombatComponent::updateCombat(const sf::Vector2f mousePos)
{
    if (!this->enemyId.empty() && !this->movesInitialized) {
        this->initMoves();
        this->initEnemyMoves();
        this->movesInitialized = true;
    }

    if (!this->enemyId.empty() && this->enemies.count(this->enemyId) > 0) {
        this->enemies[this->enemyId]->updateText();
    }
}

void CombatComponent::renderCombat(sf::RenderTarget* target)
{
    this->renderCharacters(target);
    this->renderEnemies(target);
}

void CombatComponent::initMoves()
{
    if (this->enemyId.empty() || this->enemies.count(this->enemyId) <= 0) {
        std::cerr << "Cannot initialize moves. No active enemy." << "\n";
        return;
    }

    std::cout << "INIT MOVES" << "\n";

    CharacterManager::getInstance().getCharacter("PLAYER")->createMove(
        "Slash",
        "The player slashes at the opponent with all his might!",
        "Players basic attack",
        "Slash",
        Move::Subtractor(),
        this->enemies[this->enemyId]->getHp(),
        CharacterManager::getInstance().getCharacter("PLAYER")->getDamage(),
        CharacterManager::getInstance().getCharacter("PLAYER")->getDamage(),
        0,
        "slash",
        [this]() { this->playSlashAnimation(); }
    );

    CharacterManager::getInstance().getCharacter("PLAYER")->createMove(
        "Hefty Blow",
        "The player charges up a heavy attack for maximum damage!",
        "Players heavy attack",
        "Hefty Blow",
        Move::Subcooldown(),
        this->enemies[this->enemyId]->getHp(),
        CharacterManager::getInstance().getCharacter("PLAYER")->getDamage(),
        CharacterManager::getInstance().getCharacter("PLAYER")->getDamage(),
        1,
        "hefty_blow"
    );

    CharacterManager::getInstance().getCharacter("ZIN")->createMove(
        "Heal",
        "Zin casts a healing circle around the party!",
        "Zin's basic healing spell",
        "Heal",
        Move::Healer(),
        CharacterManager::getInstance().getCharacter("ZIN")->getHealing(),
        CharacterManager::getInstance().getCharacter("PLAYER")->getHp(),
        CharacterManager::getInstance().getCharacter("PLAYER")->getHpMax(),
        0,
        "mend"
    );

    CharacterManager::getInstance().getCharacter("THOM")->createMove(
        "Harden",
        "Thom hardens his hide!",
        "Thom's defensive ability.",
        "Harden",
        Move::Adder(),
        CharacterManager::getInstance().getCharacter("THOM")->getDefense(),
        CharacterManager::getInstance().getCharacter("THOM")->getDefense(),
        CharacterManager::getInstance().getCharacter("THOM")->getDefense(),
        0,
        "iron_wall"
    );
}

// Character Functions
void CombatComponent::renderCharacters(sf::RenderTarget* target)
{
    CharacterManager::getInstance().renderAllPartyMembers(target);
}

// Enemy Functions
void CombatComponent::initEnemyDefinitions()
{
    this->enemyDefinitions = {
        {
            "WOLF",
            "Wolf",
            25.f,
            25.f,
            5.f,
            5.f,
            0.195f,
            "Assets/HostileSprites/wolfsprite.png",
            "Assets/Entities/wolfEntity.jpeg",
            {
                {
                    { "SMITHING_STONE", 1 }
                },
                { 20, 35 },
                { 100, 150 }
            },
            { "Forest" }
        },
        {
            "WALKER",
            "Walker",
            35.f,
            35.f,
            5.f,
            5.f,
            0.195f,
            "Assets/HostileSprites/decaywalkersprite.jpeg",
            "Assets/Entities/decayEntity.jpeg",
            {
                {
                    { "HEALTH_POTION", 1 },
                    { "SMITHING_STONE", 1 }
                },
                { 35, 55 },
                { 200, 250 }
            },
            { "Forest" }
        },
        {
            "PHANTOM",
            "Phantom",
            40.f,
            40.f,
            5.f,
            5.f,
            0.195f,
            "Assets/HostileSprites/phantomSprite.jpeg",
            "Assets/Entities/phantomEntity.jpeg",
            {
                {
                    { "SMITHING_STONE", 2 }
                },
                { 60, 90 },
                { 275, 350 }
            },
            { "Forest" }
        }
    };
}

void CombatComponent::renderEnemies(sf::RenderTarget* target)
{
    for (auto& it : this->enemies) {
        if (it.second != nullptr) {
            it.second->render(target);
        }
    }
}

bool CombatComponent::enemyPool(const std::string& currentArea)
{
    if (this->enemyDefinitions.empty()) {
        std::cerr << "Enemy pool is empty. No enemy spawned." << "\n";
        return false;
    }

    std::vector<const EnemyDefinition*> validEnemies;

    for (const auto& enemy : this->enemyDefinitions) {
        const bool canSpawnHere =
            std::find(enemy.spawnAreas.begin(), enemy.spawnAreas.end(), currentArea) != enemy.spawnAreas.end();

        if (canSpawnHere) {
            validEnemies.push_back(&enemy);
        }
    }

    if (validEnemies.empty()) {
        std::cerr << "No valid enemies found for area: " << currentArea << "\n";
        return false;
    }

    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::size_t> enemyRange(0, validEnemies.size() - 1);

    const EnemyDefinition& selectedEnemy = *validEnemies[enemyRange(rng)];

    this->clearCurrentEnemy();

    this->enemies[selectedEnemy.id] = new Enemy(
        selectedEnemy.name,
        selectedEnemy.hp,
        selectedEnemy.hpMax,
        selectedEnemy.damage,
        selectedEnemy.defense,
        selectedEnemy.scale,
        selectedEnemy.spritePath,
        selectedEnemy.viewerPath,
        selectedEnemy.rewards,
        false
    );

    this->setEnemyId(selectedEnemy.id);
    return true;
}

void CombatComponent::resetEnemy()
{
    auto it = this->enemies.find(this->enemyId);

    if (it != this->enemies.end()) {
        delete it->second;
        this->enemies.erase(it);

        std::cout << "Enemy " << this->enemyId << " has been deleted." << std::endl;

        this->enemyId = "";

        CharacterManager::getInstance().clearAllCharacterMoves();
        this->movesInitialized = false;

        this->enemyPool(this->currentArea);
    }
    else {
        std::cout << "Enemy " << this->enemyId << " not found." << std::endl;
    }
}

void CombatComponent::initEnemyMoves()
{
    if (this->enemyId.empty() || this->enemies.count(this->enemyId) <= 0) {
        std::cerr << "Cannot initialize enemy moves. No active enemy." << "\n";
        return;
    }

    this->enemies[this->enemyId]->createMove(
        0,
        "The creature uses its razor sharp claws to attack!",
        [this]() {
            auto& party = CharacterManager::getInstance().getParty();

            if (party.size() <= 0) {
                std::cerr << "Enemy attack failed. Party is empty." << "\n";
                return;
            }

            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<int> dist(0, static_cast<int>(party.size()) - 1);

            auto targetCharacter = party.getCharacter(dist(rng));

            if (targetCharacter == nullptr) {
                std::cerr << "Enemy attack failed. Target was null." << "\n";
                return;
            }

            targetCharacter->takeDamage(this->enemies[this->enemyId]->getDamage());

            const sf::Vector2f hitPosition = targetCharacter->getHitEffectPosition();
            this->playEnemyAttackAnimationAt(hitPosition.x, hitPosition.y);

            std::cout << "Enemy attacked " << targetCharacter->getId() << "\n";
        },
        "bash_light"
    );
}

// Combat Cleanup Functions
void CombatComponent::clearCurrentEnemy()
{
    if (this->enemyId.empty()) {
        return;
    }

    auto it = this->enemies.find(this->enemyId);

    if (it != this->enemies.end()) {
        delete it->second;
        this->enemies.erase(it);
    }

    this->enemyId = "";
}

void CombatComponent::clearCombatMoves()
{
    CharacterManager::getInstance().clearAllCharacterMoves();
    this->movesInitialized = false;
    this->clearCombatAnimations();
}

// Area Functions
void CombatComponent::setCurrentArea(const std::string& area)
{
    this->currentArea = area;
}

const std::string& CombatComponent::getCurrentArea() const
{
    return this->currentArea;
}

// Text Functions
void CombatComponent::setEnemyId(const std::string& text)
{
    this->enemyId = text;
    std::cout << "--------------------ENEMY ID SET TO: " << this->enemyId << "\n";
}

//Animation Functions
void CombatComponent::updateCombatAnimations()
{
    this->combatAnimations.update();
}

void CombatComponent::renderCombatAnimations(sf::RenderTarget* target)
{
    this->combatAnimations.render(target);
}

void CombatComponent::clearCombatAnimations()
{
    this->combatAnimations.clear();
}

void CombatComponent::playHitAnimationAt(float x, float y, float scaleX, float scaleY)
{
    AnimationEffectRequest request;

    request.sourceType = AnimationEffectRequest::SourceType::SpriteSheet;
    request.spriteSheetTextureId = "hit_animation";

    request.frameWidth = 64;
    request.frameHeight = 64;
    request.frameCount = 6;
    request.row = 0;

    request.frameTime = 0.05f;
    request.looping = false;

    request.x = x;
    request.y = y;
    request.scaleX = scaleX;
    request.scaleY = scaleY;

    this->combatAnimations.play(request);
}

void CombatComponent::playEnemyAttackAnimationAt(float x, float y)
{
    this->playHitAnimationAt(x, y, 3.f, 3.f);
}

void CombatComponent::playSlashAnimation()
{
    this->playHitAnimationAt(1695.f, 420.f, 3.f, 3.f);
}