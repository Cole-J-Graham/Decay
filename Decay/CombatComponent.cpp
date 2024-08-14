#include "CombatComponent.h"
//Constructors and Destructors
CombatComponent::CombatComponent()
{
    //Initialization
    srand(time(NULL));

    //Variables
    this->enemyRangeMin = 0;
    this->enemyRangeMax = 2;
    this->enemyId = "";
    this->movesInitialized = false;
}

CombatComponent::~CombatComponent()
{
    //Delete Enemies
    auto ie = this->enemies.begin();
    for (ie = this->enemies.begin(); ie != this->enemies.end(); ++ie) {
        delete ie->second;
    }

    //Delete Moves
    auto im = this->enemies.begin();
    for (im = this->enemies.begin(); im != this->enemies.end(); ++im) {
        delete im->second;
    }
}

//Core Functions
void CombatComponent::updateCombat(const sf::Vector2f mousePos)
{
    if (!this->enemyId.empty() && !this->movesInitialized) { 
        this->initMoves();
        this->initEnemyMoves();
        this->movesInitialized = true;
    }
    this->enemies[this->enemyId]->updateText();
}

void CombatComponent::renderCombat(sf::RenderTarget* target)
{
    this->renderCharacters(target);
    this->renderEnemies(target);
}

void CombatComponent::initMoves()
{
    CharacterManager::getInstance().getCharacter("PLAYER")->createMove(
        "Slash", 
        "The player slashes at the opponent with all his might!",
        "Players basic attack", 
        "Slash", 
        Move::Subtractor(), 
        this->enemies[this->enemyId]->getHp(), 
        CharacterManager::getInstance().getCharacter("PLAYER")->getDamage(), 
        0);

    CharacterManager::getInstance().getCharacter("PLAYER")->createMove(
        "Hefty Blow", 
        "The player charges up a heavy attack for maximum damage!",
        "Players heavy attack", 
        "Hefty Blow", 
        Move::Subcooldown(), 
        this->enemies[this->enemyId]->getHp(), 
        CharacterManager::getInstance().getCharacter("PLAYER")->getDamage(), 
        1);

    CharacterManager::getInstance().getCharacter("ZIN")->createMove(
        "Heal", 
        "Zin casts a healing circle around the party!",
        "Zin's basic healing spell", 
        "Heal", 
        Move::Adder(), 
        CharacterManager::getInstance().getCharacter("ZIN")->getHealing(),
        CharacterManager::getInstance().getCharacter("ZIN")->getHealing(),
        0);

    CharacterManager::getInstance().getCharacter("THOM")->createMove(
        "Harden",
        "Thom hardens his hide!",
        "Thom's defensive ability.",
        "Harden",
        Move::Adder(),
        CharacterManager::getInstance().getCharacter("THOM")->getDefense(),
        CharacterManager::getInstance().getCharacter("THOM")->getDefense(),
        0);
}

//Character Functions
void CombatComponent::renderCharacters(sf::RenderTarget* target)
{
    CharacterManager::getInstance().renderAll(target);
}

//Enemy Functions
void CombatComponent::renderEnemies(sf::RenderTarget* target)
{
    for (auto& it : this->enemies) {
        it.second->render(target);
    }
}

void CombatComponent::enemyPool()
{
    //Insert random integers
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> enemyRange(this->enemyRangeMin, this->enemyRangeMax);

    switch (enemyRange(rng)) {
    case 0:
        this->enemies["WOLF"] = new Enemy("Wolf", 25, 25, 5, 5, 0.195, "Assets/HostileSprites/wolfsprite.png", "Assets/Entities/wolfEntity.jpeg", false);
        this->setEnemyId("WOLF");
        break;
    case 1:
        this->enemies["WALKER"] = new Enemy("Walker", 25, 25, 5, 5, 0.195, "Assets/HostileSprites/decaywalkersprite.jpeg", "Assets/Entities/decayEntity.jpeg", false);
        this->setEnemyId("WALKER");
        break;
    case 2:
        this->enemies["PHANTOM"] = new Enemy("Phantom", 25, 25, 5, 5, 0.195, "Assets/HostileSprites/phantomSprite.jpeg", "Assets/Entities/phantomEntity.jpeg", false);
        this->setEnemyId("PHANTOM");
        break;
    }
}

void CombatComponent::resetEnemy()
{
    // Find the enemy in the container
    auto it = enemies.find(this->enemyId);

    if (it != enemies.end()) {
        //Delete the enemy object to free memory
        delete it->second;

        //Remove the enemy from the container
        enemies.erase(it);

        this->enemyPool();

        std::cout << "Enemy " << this->enemyId << " has been deleted." << std::endl;
    }
    else {
        std::cout << "Enemy " << this->enemyId << " not found." << std::endl;
    }
}

void CombatComponent::initEnemyMoves()
{
    this->enemies[this->enemyId]->createMove(0, "The creature uses its razor sharp claws to attack!",
        Move::Subtractor(), this->enemies[this->enemyId]->getDamage(), CharacterManager::getInstance().getCharacter("PLAYER")->getHp(), 0);
}

//Text Functions
void CombatComponent::setEnemyId(const std::string& text)
{
    this->enemyId = text;
    std::cout << "--------------------ENEMY ID SET TO: " << this->enemyId << "\n";
}