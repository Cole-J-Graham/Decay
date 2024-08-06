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
}

//Core Functions
void CombatComponent::updateCombat(const sf::Vector2f mousePos)
{
    if (!this->enemyId.empty() && !this->movesInitialized) { 
        this->initMoves(); 
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
    CharacterManager::getInstance().getCharacter("PLAYER")->createMove("Slash", "The player slashes at the opponent with all his might!", 
        "Players basic attack", "Slash", Move::Subtractor(), this->enemies[this->enemyId]->getHp(), CharacterManager::getInstance().getCharacter("PLAYER")->getDamage());
    CharacterManager::getInstance().getCharacter("PLAYER")->createMove("Hefty Blow", "The player charges up a heavy attack for maximum damage!",
        "Players heavy attack", "Hefty Blow", Move::Subcooldown(), this->enemies[this->enemyId]->getHp(), CharacterManager::getInstance().getCharacter("PLAYER")->getDamage());

    //CharacterManager::getInstance().getCharacter("ZIN")->createMove("Protection", "Zin's basic barrier", "Protection");
    //CharacterManager::getInstance().getCharacter("ZIN")->createMove("Healing", "Zin's basic healing", "Healing");

    //CharacterManager::getInstance().getCharacter("THOM")->createMove("Harden", "Thom's defense boost", "Harden");
    //CharacterManager::getInstance().getCharacter("THOM")->createMove("Spiked", "Thom's thorn passive ability", "Spiked");
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

//Text Functions
void CombatComponent::setEnemyId(std::string text)
{
    this->enemyId = text;
}