#include "CombatState.h"
#include "BonfireState.h"
#include "RewardSystem.h"
#include "MusicManager.h"
#include "EnemyDatabase.h"
#include "GameFlags.h"
#include "TriggerManager.h"
#include "SaveManager.h"
#include <iostream>
#include <algorithm>

// ── Constructor ───────────────────────────────────────────────────────────

CombatState::CombatState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{}

// ── State interface ───────────────────────────────────────────────────────

void CombatState::updateKeybinds() {}

void CombatState::update()
{
    this->checkForQuit();
    this->updateMousePositions();

    this->console.update(this->getMousePosView());
    this->updateCombat(this->getMousePosView());
    this->combatLoop(this->getMousePosView());
    this->updateCombatAnimations();
}

void CombatState::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    this->console.render(*target);
    this->renderCombat(target);
    this->renderCombatAnimations(target);
}

// ── Combat loop ───────────────────────────────────────────────────────────

void CombatState::combatLoop(const sf::Vector2f mousePos)
{
    // Defeat screen
    if (this->defeatState)
    {
        if (this->console.defeatBonfireClicked()) this->handleReturnToBonfire();
        if (this->console.defeatLoadClicked())    this->handleLoadLastSave();
        return;
    }

    // Victory screen
    if (this->stateEnd)
    {
        this->console.enableContinue();
        if (this->console.continueClicked()) this->finishCombatEnd();
        return;
    }

    if (this->detectPartyWipe()) return;

    this->detectEnemyDeath();
    if (this->stateEnd) return;

    switch (this->combatFrame)
    {
    case 0: this->handleCharacterTurn(0, mousePos); break;
    case 1: this->handleCharacterTurn(1, mousePos); break;
    case 2: this->handleCharacterTurn(2, mousePos); break;
    case 3: this->handleEnemyTurn(mousePos);        break;
    case 4:
        this->resetAllCharacterTurns();
        this->combatFrame = 0;
        this->console.disableContinue();
        break;
    default:
        this->combatFrame = 0;
        this->console.disableContinue();
        break;
    }
}

// ── Party wipe ────────────────────────────────────────────────────────────

bool CombatState::detectPartyWipe()
{
    if (this->defeatState) return true;

    const auto& party = CharacterManager::getInstance().getAllPartyMembers();
    if (party.empty()) return false;

    for (const auto& member : party)
        if (member && member->isAlive()) return false;

    this->beginDefeat();
    return true;
}

void CombatState::beginDefeat()
{
    if (this->defeatState) return;

    std::cout << "CombatState: party wiped.\n";

    this->defeatState = true;
    this->combatFrame = 0;

    this->resetAllCharacterTurns();
    this->console.disableContinue();
    this->console.setTurnIndicator("");
    this->console.showDefeatPanel();

    MusicManager::getInstance().pop();
}

void CombatState::handleReturnToBonfire()
{
    CharacterManager::getInstance().restParty();

    this->clearCurrentEnemy();
    this->clearCombatMoves();
    this->resetAllCharactersForNewCombat();

    this->defeatState = false;
    this->combatFrame = 0;

    this->console.hideDefeatPanel();

    if (!this->states->empty()) this->states->pop();

    this->states->push(new BonfireState(
        this->window, this->states, this->currentAreaIdForBonfire));
}

void CombatState::handleLoadLastSave()
{
    // Find most recent save by timestamp
    int         latestSlot = -1;
    std::string latestTimestamp = "";

    for (int i = 0; i < SaveManager::maxSlots; ++i)
    {
        const auto summary = SaveManager::getInstance().getSlotSummary(i);
        if (!summary.exists) continue;
        if (summary.timestamp > latestTimestamp)
        {
            latestTimestamp = summary.timestamp;
            latestSlot = i;
        }
    }

    if (latestSlot == -1)
    {
        std::cout << "CombatState: no save found, falling back to bonfire.\n";
        this->handleReturnToBonfire();
        return;
    }

    SaveManager::getInstance().loadFromSlot(latestSlot, nullptr);

    this->clearCurrentEnemy();
    this->clearCombatMoves();
    this->resetAllCharactersForNewCombat();

    this->defeatState = false;
    this->combatFrame = 0;
    this->console.hideDefeatPanel();

    if (!this->states->empty()) this->states->pop();
}

// ── Enemy death (victory) ─────────────────────────────────────────────────

bool CombatState::detectEnemyDeath()
{
    if (this->getEnemyId().empty()) return false;

    auto it = this->enemies.find(this->getEnemyId());
    if (it == this->enemies.end() || !it->second) return false;

    if (it->second->getHp() <= 0)
    {
        this->beginCombatEnd();
        return true;
    }

    return false;
}

void CombatState::beginCombatEnd()
{
    if (this->stateEnd) return;

    std::cout << "Enemy " << this->getEnemyId() << " defeated.\n";

    if (!this->pendingDefeatedFlag.empty())
    {
        GameFlags::getInstance().set(this->pendingDefeatedFlag);
        TriggerManager::getInstance().fire("boss_defeated:" + this->pendingDefeatedFlag);
        this->pendingDefeatedFlag = "";
    }

    this->stateEnd = true;
    this->combatFrame = 0;
    this->resetAllCharacterTurns();

    auto it = this->enemies.find(this->getEnemyId());

    std::ostringstream msg;
    msg << "Enemy defeated.";

    if (it != this->enemies.end() && it->second)
    {
        it->second->resetTurn();

        RewardResult rewards = RewardSystem::grantRewards(
            it->second->getRewards(), Inventory::getInstance());

        if (rewards.expGranted > 0)
            CharacterManager::getInstance().addExpToParty(
                static_cast<float>(rewards.expGranted));

        if (rewards.anyRewardGranted)
        {
            msg << " Received ";
            bool first = true;

            auto comma = [&]() { if (!first) msg << ", "; first = false; };

            if (rewards.goldGranted > 0) { comma(); msg << "Gold x" << rewards.goldGranted; }
            if (rewards.expGranted > 0) { comma(); msg << "EXP x" << rewards.expGranted; }

            for (const auto& r : rewards.grantedRewards)
            {
                const auto* def = Inventory::getInstance().getItemDefinition(r.itemId);
                comma();
                msg << (def ? def->displayName : r.itemId) << " x" << r.quantity;
            }
            msg << ".";
        }
        else msg << " No rewards received.";
    }

    msg << " Click to continue...";

    this->console.setMessage(msg.str());
    this->console.showMessage();
    this->console.enableContinue();
}

void CombatState::finishCombatEnd()
{
    this->console.disableContinue();
    this->console.setMessage("");
    this->console.showMessage();

    this->clearCurrentEnemy();
    this->clearCombatMoves();
    this->resetAllCharactersForNewCombat();

    this->combatFrame = 0;
    this->stateEnd = false;

    MusicManager::getInstance().pop();

    if (!this->states->empty()) this->states->pop();
}

// ── Combat start ──────────────────────────────────────────────────────────

void CombatState::resetCombat()
{
    this->console.disableContinue();
    this->console.setMessage("");
    this->console.hideMessage();
    this->console.hideDefeatPanel();

    this->clearCurrentEnemy();
    this->clearCombatMoves();
    this->resetAllCharactersForNewCombat();

    this->combatFrame = 0;
    this->stateEnd = false;
    this->defeatState = false;
    this->pendingDefeatedFlag = "";
}

bool CombatState::startCombat(const std::string& areaId)
{
    this->resetCombat();
    this->setCurrentArea(areaId);
    this->currentAreaIdForBonfire = areaId;

    if (!this->enemyPool(this->getCurrentArea())) return false;

    this->combatFrame = 0;
    this->stateEnd = false;
    this->console.disableContinue();
    this->applyCombatMusic(areaId);
    return true;
}

bool CombatState::startBossCombat(const std::string& enemyId,
    const std::string& areaId,
    const std::string& defeatedFlag,
    const std::string& musicContext)
{
    this->resetCombat();
    this->setCurrentArea(areaId);
    this->currentAreaIdForBonfire = areaId;

    const EnemyDefinition* def = EnemyDatabase::getInstance().getEnemy(enemyId);
    if (!def)
    {
        std::cerr << "CombatState::startBossCombat: enemy not found: " << enemyId << "\n";
        return false;
    }

    this->clearCurrentEnemy();
    this->enemies[def->id] = new Enemy(
        def->name, def->hp, def->hpMax, def->damage, def->defense,
        def->scale, def->spritePath, def->viewerPath, def->rewards, false);

    this->setEnemyId(def->id);
    this->pendingDefeatedFlag = defeatedFlag;

    this->combatFrame = 0;
    this->stateEnd = false;
    this->console.disableContinue();
    this->applyCombatMusic(areaId, musicContext);
    return true;
}

void CombatState::applyCombatMusic(const std::string& areaId,
    const std::string& overrideContext)
{
    if (!overrideContext.empty() &&
        MusicManager::getInstance().hasContext(overrideContext))
    {
        MusicManager::getInstance().play(overrideContext);
        return;
    }

    std::string lower = areaId;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    const std::string ctx = "combat_" + lower;

    if (MusicManager::getInstance().hasContext(ctx))
        MusicManager::getInstance().play(ctx);
    else
        std::cout << "CombatState: no combat music for: " << areaId << "\n";
}

// ── Character helpers ─────────────────────────────────────────────────────

void CombatState::resetAllCharacterTurns()
{
    for (auto& pair : CharacterManager::getInstance().getAllCharacters())
        pair.second->resetTurn();
}

void CombatState::resetAllCharactersForNewCombat()
{
    for (auto& pair : CharacterManager::getInstance().getAllCharacters())
    {
        pair.second->resetTurn();
        pair.second->resetPose();
        pair.second->clearCombatStatus();
    }
}

// ── Turn handlers ─────────────────────────────────────────────────────────

void CombatState::handleCharacterTurn(int partyIndex, const sf::Vector2f mousePos)
{
    auto& party = CharacterManager::getInstance().getParty();

    if (party.size() <= partyIndex)
    {
        this->combatFrame++;
        this->console.disableContinue();
        return;
    }

    auto character = party.getCharacter(partyIndex);
    if (!character)
    {
        this->combatFrame++;
        this->console.disableContinue();
        return;
    }

    this->console.setTurnIndicator("TURN  " + character->getId());

    if (character->isWaitingForContinue())
    {
        this->console.enableContinue();
        if (this->console.continueClicked())
        {
            character->continueTurn(this->combatFrame);
            this->console.disableContinue();
        }
        return;
    }

    character->clearJustContinued();

    if (character->isStunned())
    {
        this->console.enableContinue();
        this->console.setMessage(character->getId() + " is stunned and skips their turn.");
        this->console.showMessage();

        if (this->console.continueClicked())
        {
            character->consumeStunTurn();
            character->resetTurn();
            this->combatFrame++;
            this->console.disableContinue();
            this->console.setMessage("");
            this->console.hideMessage();
        }
        return;
    }

    if (character->isActionLocked())
    {
        character->resetTurn();
        this->console.enableContinue();
        this->console.setMessage(character->getId() + " is locked and skips their turn.");
        this->console.showMessage();

        if (this->console.continueClicked())
        {
            character->consumeActionLockTurn();
            character->tickTemporaryEffects();
            character->consumePoseTurn();
            this->combatFrame++;
            this->console.disableContinue();
            this->console.setMessage("");
            this->console.hideMessage();
        }
        return;
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        character->clearWaitingForMouseRelease();

    character->characterTurn(this->combatFrame, mousePos);
}

void CombatState::handleEnemyTurn(const sf::Vector2f mousePos)
{
    if (this->getEnemyId().empty()) return;

    auto it = this->enemies.find(this->getEnemyId());
    if (it == this->enemies.end() || !it->second) return;

    Enemy* enemy = it->second;

    if (!enemy->isWaitingForContinue())
        enemy->enemyTurn(this->combatFrame, mousePos);

    if (enemy->isWaitingForContinue())
    {
        this->console.enableContinue();
        if (this->console.continueClicked())
        {
            enemy->continueTurn(this->combatFrame);
            this->console.disableContinue();
        }
    }
}