#include "CombatState.h"
#include "RewardSystem.h"
#include "MusicManager.h"
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
    this->resetAllCharactersForNewCombat();

    this->combatFrame = 0;
    this->stateEnd = false;

    MusicManager::getInstance().pop();  // resume area music

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
	this->resetAllCharactersForNewCombat();

    this->combatFrame = 0;
    this->stateEnd = false;
}

bool CombatState::startCombat(const std::string& areaId)
{
    this->resetCombat();
    this->setCurrentArea(areaId);

    const bool spawnedEnemy = this->enemyPool(this->getCurrentArea());
    if (!spawnedEnemy) return false;

    this->combatFrame = 0;
    this->stateEnd = false;
    this->disableCombatConsoleContinue();

	//Transform areaID to lowercase for db matching, but keep original for logging
    std::string areaIdLower = areaId;
    std::transform(areaIdLower.begin(), areaIdLower.end(), areaIdLower.begin(), ::tolower);
    const std::string combatContext = "combat_" + areaIdLower;
    // Match db format: "combat_forest", "combat_castle", etc.
    if (MusicManager::getInstance().hasContext(combatContext)) {
        MusicManager::getInstance().play(combatContext);
    }
    else {
        std::cout << "No combat music found for area " << areaId
            << ". Attempted: " << combatContext << "\n";
        // No generic fallback exists in db, so just leave travel music playing
    }

    return true;
}

// State Functions
void CombatState::updateKeybinds()
{}

void CombatState::update()
{
    this->checkForQuit();
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
	// Mid combat turn resets should only reset the turn state, not the pose or combat status effects, so that stuns and locks persist across turns but still consume their duration properly.
    auto& allCharacters = CharacterManager::getInstance().getAllCharacters();

    for (auto& pair : allCharacters) {
        pair.second->resetTurn();
    }
}

void CombatState::resetAllCharactersForNewCombat()
{
	// Full combat resets should clear turn state, pose, and combat status effects, so that characters start fresh in the new combat.
    auto& allCharacters = CharacterManager::getInstance().getAllCharacters();
    for (auto& pair : allCharacters) {
        auto& c = pair.second;
        c->resetTurn();
        c->resetPose();
        c->clearCombatStatus();
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

    this->ui.text("TURN_INDICATOR_TEXT").setString("TURN  " + character->getId());

    // ← Check this FIRST before anything else can reset characterFrame
    if (character->isWaitingForContinue()) {
        this->enableCombatConsoleContinue();

        if (this->combatConsoleClicked()) {
            character->continueTurn(this->combatFrame);
            this->disableCombatConsoleContinue();
        }
        return;
    }

    character->clearJustContinued();

    if (character->isStunned()) {
        this->enableCombatConsoleContinue();
        this->ui.text("COMBAT_MESSAGE").setString(character->getId() + " is stunned and skips their turn.");
        this->ui.text("COMBAT_MESSAGE").setShown();

        if (this->combatConsoleClicked()) {
            character->consumeStunTurn();
            character->resetTurn();
            this->combatFrame++;
            this->disableCombatConsoleContinue();
            this->ui.text("COMBAT_MESSAGE").setString("");
            this->ui.text("COMBAT_MESSAGE").setHidden();
        }
        return;
    }

    if (character->isActionLocked()) {
        character->resetTurn();
        this->enableCombatConsoleContinue();
        this->ui.text("COMBAT_MESSAGE").setString(character->getId() + " is locked into their action and skips their turn.");
        this->ui.text("COMBAT_MESSAGE").setShown();

        if (this->combatConsoleClicked()) {
            character->consumeActionLockTurn();
            character->tickTemporaryEffects();
            character->consumePoseTurn();
            this->combatFrame++;
            this->disableCombatConsoleContinue();
            this->ui.text("COMBAT_MESSAGE").setString("");
            this->ui.text("COMBAT_MESSAGE").setHidden();
        }
        return;
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        character->clearWaitingForMouseRelease();
    }

    character->characterTurn(this->combatFrame, mousePos);
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
        this->ui.text("COMBAT_CONTINUE_HINT").setShown();
    }
}

void CombatState::disableCombatConsoleContinue()
{
    this->combatConsoleActive = false;
    this->ui.button("COMBAT_CONSOLE_CONTINUE").setIdle();
    this->ui.button("COMBAT_CONSOLE_CONTINUE").hide();
    this->ui.text("COMBAT_CONTINUE_HINT").setHidden();
}

bool CombatState::combatConsoleClicked()
{
    return this->combatConsoleActive &&
        this->ui.button("COMBAT_CONSOLE_CONTINUE").isPressed();
}

// UI Functions
void CombatState::initUi()
{
    // ── Enemy zone border ─────────────────────────────────────────────
    this->ui.addRectangle("HOSTILEBORDER", std::make_unique<Rectangle>(
        1695, 420, 200, 200,
        sf::Color::Transparent,
        sf::Color(255, 80, 80, 120),   // red tint — hostile zone
        1.f, false
    ));

    // ── Combat console — filled dark panel ───────────────────────────
    this->ui.addRectangle("COMBATCONSOLE_BG", std::make_unique<Rectangle>(
        350, 825, 1250, 175,
        sf::Color(10, 10, 20, 210),    // near-black fill
        sf::Color(255, 255, 255, 50),
        1.f, false
    ));

    // Thin gold accent bar along the top of the console
    this->ui.addRectangle("COMBATCONSOLE_ACCENT", std::make_unique<Rectangle>(
        350, 825, 1250, 2,
        sf::Color(255, 200, 80, 160),
        sf::Color::Transparent,
        0.f, false
    ));

    // Main message text — slightly inset
    this->ui.addText("COMBAT_MESSAGE", std::make_unique<Text>(
        355, 835, 16, "", sf::Color::White, true
    ));

    // "Click to continue" hint — bottom-right of console
    this->ui.addText("COMBAT_CONTINUE_HINT", std::make_unique<Text>(
        1455, 830, 12, "[ Click to continue ]",
        sf::Color(180, 180, 180, 140), true   // starts hidden
    ));

    // Invisible click target covering the whole console
    this->ui.addButton("COMBAT_CONSOLE_CONTINUE", std::make_unique<Button>(
        350, 825, 1250, 175, 0.5f, "",
        sf::Color(0, 0, 0, 0),
        sf::Color(255, 255, 255, 12),
        sf::Color(255, 255, 255, 25),
        true
    ));

    // ── Turn indicator bar above the console ─────────────────────────
    this->ui.addRectangle("TURN_INDICATOR_BG", std::make_unique<Rectangle>(
        350, 800, 1250, 22,
        sf::Color(20, 20, 35, 200),
        sf::Color(255, 255, 255, 40),
        1.f, false
    ));

    this->ui.addText("TURN_INDICATOR_TEXT", std::make_unique<Text>(
        360, 803, 12, "", sf::Color(160, 220, 255, 220), false
    ));
}