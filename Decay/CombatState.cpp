#include "CombatState.h"

#include "RewardSystem.h"

#include <iostream>

// Constructors and Destructors
CombatState::CombatState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->initUi();

    this->combatFrame = 0;
    this->stateEnd = false;
    this->combatConsoleActive = false;
}

// Core Functions
void CombatState::combatLoop(const sf::Vector2f mousePos)
{
    if (this->stateEnd) {
        this->enableCombatConsoleContinue();

        if (this->combatConsoleClicked()) {
            this->finishCombatEnd();
        }

        return;
    }

    this->detectEnemyDeath();

    if (this->stateEnd) {
        return;
    }

    switch (this->combatFrame) {
    case 0:
        this->handleCharacterTurn(0, mousePos);
        break;

    case 1:
        this->handleCharacterTurn(1, mousePos);
        break;

    case 2:
        this->handleCharacterTurn(2, mousePos);
        break;

    case 3:
        this->handleEnemyTurn(mousePos);
        break;

    case 4:
        this->resetAllCharacterTurns();
        this->combatFrame = 0;
        this->disableCombatConsoleContinue();
        break;

    default:
        this->combatFrame = 0;
        this->disableCombatConsoleContinue();
        break;
    }
}

bool CombatState::detectEnemyDeath()
{
    if (this->getEnemyId().empty()) {
        return false;
    }

    auto it = this->enemies.find(this->getEnemyId());

    if (it == this->enemies.end() || it->second == nullptr) {
        return false;
    }

    if (it->second->getHp() <= 0) {
        this->beginCombatEnd();
        return true;
    }

    return false;
}

void CombatState::beginCombatEnd()
{
    if (this->stateEnd) {
        return;
    }

    std::cout << "Enemy " << this->getEnemyId() << " has been defeated." << "\n";

    this->stateEnd = true;
    this->combatFrame = 0;

    this->resetAllCharacterTurns();

    auto it = this->enemies.find(this->getEnemyId());

    std::ostringstream rewardMessage;
    rewardMessage << "Enemy defeated.";

    if (it != this->enemies.end() && it->second != nullptr) {
        it->second->resetTurn();

        RewardResult rewards = RewardSystem::grantRewards(
            it->second->getRewards(),
            Inventory::getInstance()
        );

        if (rewards.expGranted > 0) {
            CharacterManager::getInstance().addExpToParty(static_cast<float>(rewards.expGranted));
        }

        if (rewards.anyRewardGranted) {
            rewardMessage << " Received ";

            bool firstReward = true;

            if (rewards.goldGranted > 0) {
                rewardMessage << "Gold x" << rewards.goldGranted;
                firstReward = false;
            }

            if (rewards.expGranted > 0) {
                if (!firstReward) {
                    rewardMessage << ", ";
                }

                rewardMessage << "EXP x" << rewards.expGranted;
                firstReward = false;
            }

            for (const auto& reward : rewards.grantedRewards) {
                const Inventory::ItemDefinition* definition =
                    Inventory::getInstance().getItemDefinition(reward.itemId);

                std::string itemName = reward.itemId;

                if (definition != nullptr) {
                    itemName = definition->displayName;
                }

                if (!firstReward) {
                    rewardMessage << ", ";
                }

                rewardMessage << itemName << " x" << reward.quantity;
                firstReward = false;
            }

            rewardMessage << ".";
        }
        else {
            rewardMessage << " No rewards received.";
        }
    }

    rewardMessage << " Click to continue...";

    this->ui.text("COMBAT_MESSAGE").setString(rewardMessage.str());
    this->ui.text("COMBAT_MESSAGE").setShown();

    this->enableCombatConsoleContinue();
}

void CombatState::finishCombatEnd()
{
    this->disableCombatConsoleContinue();

    this->ui.text("COMBAT_MESSAGE").setString("");
    this->ui.text("COMBAT_MESSAGE").setShown();

    this->clearCurrentEnemy();
    this->clearCombatMoves();
    this->resetAllCharacterTurns();

    this->combatFrame = 0;
    this->stateEnd = false;

    if (!this->states->empty()) {
        this->states->pop();
    }
}

void CombatState::resetCombat()
{
    this->disableCombatConsoleContinue();

    this->ui.text("COMBAT_MESSAGE").setString("");
    this->ui.text("COMBAT_MESSAGE").setHidden();

    this->clearCurrentEnemy();
    this->clearCombatMoves();
    this->resetAllCharacterTurns();

    this->combatFrame = 0;
    this->stateEnd = false;
}

bool CombatState::startCombat(const std::string& areaId)
{
    this->resetCombat();

    this->setCurrentArea(areaId);

    const bool spawnedEnemy = this->enemyPool(this->getCurrentArea());

    if (!spawnedEnemy) {
        return false;
    }

    this->combatFrame = 0;
    this->stateEnd = false;
    this->disableCombatConsoleContinue();

    return true;
}

// State Functions
void CombatState::updateKeybinds()
{}

void CombatState::update()
{
    this->updateMousePositions();

    this->ui.update(this->getMousePosView());

    this->updateCombat(this->getMousePosView());
    this->combatLoop(this->getMousePosView());
    this->updateCombatAnimations();
}

void CombatState::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    this->ui.render(*target);
    this->renderCombat(target);
    this->renderCombatAnimations(target);
}

// Character Functions
void CombatState::resetAllCharacterTurns()
{
    auto& allCharacters = CharacterManager::getInstance().getAllCharacters();

    for (auto& pair : allCharacters) {
        pair.second->resetTurn();
    }
}

// Combat Turn Helpers
void CombatState::handleCharacterTurn(int partyIndex, const sf::Vector2f mousePos)
{
    auto& party = CharacterManager::getInstance().getParty();

    if (party.size() <= partyIndex) {
        this->combatFrame++;
        this->disableCombatConsoleContinue();
        return;
    }

    auto character = party.getCharacter(partyIndex);

    if (character == nullptr) {
        this->combatFrame++;
        this->disableCombatConsoleContinue();
        return;
    }

    character->characterTurn(this->combatFrame, mousePos);

    if (character->isWaitingForContinue()) {
        this->enableCombatConsoleContinue();

        if (this->combatConsoleClicked()) {
            character->continueTurn(this->combatFrame);
            this->disableCombatConsoleContinue();
            return;
        }
    }
}

void CombatState::handleEnemyTurn(const sf::Vector2f mousePos)
{
    if (this->getEnemyId().empty()) {
        return;
    }

    auto it = this->enemies.find(this->getEnemyId());

    if (it == this->enemies.end() || it->second == nullptr) {
        return;
    }

    Enemy* enemy = it->second;

    if (!enemy->isWaitingForContinue()) {
        enemy->enemyTurn(this->combatFrame, mousePos);
    }

    if (enemy->isWaitingForContinue()) {
        this->enableCombatConsoleContinue();

        if (this->combatConsoleClicked()) {
            enemy->continueTurn(this->combatFrame);
            this->disableCombatConsoleContinue();
            return;
        }
    }
}

// Combat Console Helpers
void CombatState::enableCombatConsoleContinue()
{
    if (!this->combatConsoleActive) {
        this->combatConsoleActive = true;
        this->ui.button("COMBAT_CONSOLE_CONTINUE").show();
    }
}

void CombatState::disableCombatConsoleContinue()
{
    this->combatConsoleActive = false;

    this->ui.button("COMBAT_CONSOLE_CONTINUE").setIdle();
    this->ui.button("COMBAT_CONSOLE_CONTINUE").hide();
}

bool CombatState::combatConsoleClicked()
{
    return this->combatConsoleActive &&
        this->ui.button("COMBAT_CONSOLE_CONTINUE").isPressed();
}

// UI Functions
void CombatState::initUi()
{
    this->ui.addRectangle("HOSTILEBORDER", std::make_unique<Rectangle>(
        1695, 420, 200, 200,
        sf::Color::Transparent,
        sf::Color::White,
        1.f,
        false
    ));

    this->ui.addRectangle("COMBATCONSOLE", std::make_unique<Rectangle>(
        350, 830, 1250, 175,
        sf::Color::Transparent,
        sf::Color::White,
        1.f,
        false
    ));

    this->ui.addRectangle("COMBATCONSOLE_BUTTONPANEL", std::make_unique<Rectangle>(
        350, 800, 1250, 25,
        sf::Color::Transparent,
        sf::Color::White,
        1.f,
        false
    ));

    this->ui.addText("COMBAT_MESSAGE", std::make_unique<Text>(
        355, 835, 16,
        "",
        sf::Color::White,
        true
    ));

    this->ui.addButton("COMBAT_CONSOLE_CONTINUE", std::make_unique<Button>(
        350, 830, 1250, 175, 0.5f, "",
        sf::Color(0, 0, 0, 0),
        sf::Color(255, 255, 255, 20),
        sf::Color(255, 255, 255, 40),
        true
    ));
}
