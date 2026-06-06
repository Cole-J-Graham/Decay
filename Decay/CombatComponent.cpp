#include "CombatComponent.h"

#include "EnemyDatabase.h"
#include "EnemyMoveDatabase.h"

#include <iostream>

// Constructors and Destructors
CombatComponent::CombatComponent()
{
    this->enemyId = "";
    this->currentArea = "FOREST";
    this->movesInitialized = false;
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

    Enemy* activeEnemy = this->enemies[this->enemyId];

    auto& characterManager = CharacterManager::getInstance();
    const auto& allCharacters = characterManager.getAllCharacters();

    for (const auto& pair : allCharacters) {
        const std::string& characterId = pair.first;
        const auto& character = pair.second;

        if (!character) {
            continue;
        }

        std::vector<const CharacterMoveDefinition*> moveDefinitions =
            CharacterMoveDatabase::getInstance().getMovesForOwner(characterId);

        for (const CharacterMoveDefinition* moveDefinition : moveDefinitions) {
            if (moveDefinition == nullptr) {
                continue;
            }

            Character* characterPtr = character.get();

            character->createMove(
                moveDefinition->id,
                moveDefinition->message,
                moveDefinition->tip,
                moveDefinition->buttonText,
                [this, characterPtr, activeEnemy, moveDefinition]() {
                    std::map<std::string, Move*>& charMoves = characterPtr->getMoves();
                    auto it = charMoves.find(moveDefinition->id);
                    if (it != charMoves.end() && !it->second->canUse()) {
                        return;
                    }
                    if (it != charMoves.end()) {
                        it->second->consumeMp();
                        // Save MP back to character so it persists after moves are cleared
                        characterPtr->setMoveMp(moveDefinition->id, it->second->getMp());
                    }
                    CharacterMoveExecutor::execute(
                        *moveDefinition,
                        *characterPtr,
                        *activeEnemy,
                        [this]() { this->playSlashAnimation(); }
                    );
                },
                moveDefinition->sfxId
            );

            // Restore saved MP (persists across combats); first combat uses mpMax as default
            std::map<std::string, Move*>& charMoves = characterPtr->getMoves();
            auto it = charMoves.find(moveDefinition->id);
            if (it != charMoves.end()) {
                int savedMp = characterPtr->getMoveMp(moveDefinition->id, moveDefinition->mpMax);
                it->second->initMp(moveDefinition->mpMax, savedMp);
            }
        }
    }
}

// Character Functions
void CombatComponent::renderCharacters(sf::RenderTarget* target)
{
    CharacterManager::getInstance().renderAllPartyMembers(target);
}

// Enemy Functions
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
    const auto& enemyDefinitions = EnemyDatabase::getInstance().getAllEnemies();

    if (enemyDefinitions.empty()) {
        std::cerr << "Enemy database is empty. No enemy spawned." << "\n";
        return false;
    }

    std::vector<const EnemyDefinition*> validEnemies;

    for (const auto& enemy : enemyDefinitions) {
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

    Enemy* enemy = this->enemies[this->enemyId];

    const EnemyDefinition* activeEnemyDefinition =
        EnemyDatabase::getInstance().getEnemy(this->enemyId);

    if (activeEnemyDefinition == nullptr) {
        std::cerr << "Cannot initialize enemy moves. Enemy definition not found: "
            << this->enemyId << "\n";
        return;
    }

    int moveIndex = 0;

    for (const auto& moveId : activeEnemyDefinition->moveIds) {
        const EnemyMoveDefinition* moveDefinition =
            EnemyMoveDatabase::getInstance().getMove(moveId);

        if (moveDefinition == nullptr) {
            std::cerr << "Enemy move definition not found: " << moveId << "\n";
            continue;
        }

        enemy->createMove(
            moveIndex,
            moveDefinition->message,
            [this, enemy, moveDefinition]() {
                EnemyMoveExecutor::execute(
                    *moveDefinition,
                    *enemy,
                    [this](float x, float y) {
                        this->playEnemyAttackAnimationAt(x, y);
                    }
                );
            },
            moveDefinition->sfxId
        );

        moveIndex++;
    }
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