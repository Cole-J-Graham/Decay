#include "BeatSequencer.h"
#include "Inventory.h"
#include "CharacterManager.h"
#include "CharacterUnlockRegistry.h"
#include "GameTriggers.h"
#include "TriggerManager.h"
#include "Text.h"
#include <iostream>

// ============================================================
//  Constructor
// ============================================================

BeatSequencer::BeatSequencer() {}

// ============================================================
//  Public
// ============================================================

void BeatSequencer::start(std::vector<Beat> inBeats, DialogueInputComponent* dlg)
{
    beats = resolveConditionals(inBeats);
    dialogue = dlg;
    currentBeatIndex = -1;
    lastChoice = Choice::NONE;
    currentState = State::IDLE;
    activeNPCName = "";
    activeEmotion = "";
    running = true;
    finished = false;

    advanceBeat();
}

void BeatSequencer::update(sf::Vector2f mousePos)
{
    if (!running || dialogue == nullptr) return;
    dialogue->update(mousePos);
    updateInput();
}

void BeatSequencer::reset()
{
    beats.clear();
    currentBeatIndex = -1;
    lastChoice = Choice::NONE;
    currentState = State::IDLE;
    activeNPCName = "";
    activeEmotion = "";
    running = false;
    finished = false;
    dialogue = nullptr;
}

// ============================================================
//  Conditional resolution ([IF_FOLLOWER] / [END_IF])
// ============================================================

std::vector<Beat> BeatSequencer::resolveConditionals(const std::vector<Beat>& inBeats)
{
    std::vector<Beat> resolved;
    resolved.reserve(inBeats.size());

    for (size_t i = 0; i < inBeats.size(); ++i)
    {
        const Beat& beat = inBeats[i];

        if (beat.type == Beat::Type::CONDITION_START)
        {
            const std::string& followerId = beat.condition.followerId;

            bool followerPresent = false;
            for (const auto& member : CharacterManager::getInstance().getAllPartyMembers())
            {
                if (member && member->getId() == followerId)
                {
                    followerPresent = true;
                    break;
                }
            }

            if (followerPresent)
            {
                continue; // keep inner beats, drop marker
            }

            // Skip to END_IF
            while (i < inBeats.size() && inBeats[i].type != Beat::Type::CONDITION_END)
                ++i;

            continue; // drop CONDITION_END too
        }

        if (beat.type == Beat::Type::CONDITION_END)
        {
            continue; // drop closing marker
        }

        resolved.push_back(beat);
    }

    return resolved;
}

// ============================================================
//  Input
// ============================================================

void BeatSequencer::updateInput()
{
    if (currentState == State::SHOWING_CHOICES)
    {
        if (dialogue->topDialogueClicked())
        {
            lastChoice = Choice::A;
            dialogue->hideDialogueOptions();
            currentState = State::IDLE;
            advanceBeat();
        }
        else if (dialogue->bottomDialogueClicked())
        {
            lastChoice = Choice::B;
            dialogue->hideDialogueOptions();
            currentState = State::IDLE;
            advanceBeat();
        }
    }
    else if (currentState == State::SHOWING_NPC)
    {
        if (dialogue->mainDialogueClicked())
        {
            std::string empty = "";
            dialogue->hideMainDialogue();
            dialogue->setMainDialogueText(empty);
            currentState = State::IDLE;
            advanceBeat();
        }
    }
}

// ============================================================
//  Beat sequencing
// ============================================================

void BeatSequencer::advanceBeat()
{
    ++currentBeatIndex;

    if (currentBeatIndex >= (int)beats.size())
    {
        activeNPCName = "";
        activeEmotion = "";
        running = false;
        finished = true; // stays true until reset() — gives callers a reliable signal
        std::cout << "BeatSequencer: sequence finished.\n";
        return;
    }

    const Beat& beat = beats[currentBeatIndex];

    if (beat.type == Beat::Type::NPC)
    {
        const std::string& line = (lastChoice == Choice::B)
            ? beat.npc.lineB : beat.npc.lineA;
        showNPCBeat(beat.npc, line);
    }
    else if (beat.type == Beat::Type::CHARACTER)
    {
        const std::string& cid = beat.character.characterId;

        bool inParty = false;
        if (!cid.empty()) {
            // Check active party first
            for (const auto& member : CharacterManager::getInstance().getAllPartyMembers()) {
                if (member && member->getId() == cid) { inParty = true; break; }
            }
            // Also allow characters that exist in the registry (not yet unlocked)
            // so they can appear in their own introduction events
            if (!inParty && CharacterUnlockRegistry::getInstance().getPending(cid))
                inParty = true;
        }
        else {
            inParty = true; // choice blocks with no character id always show
        }

        if (!inParty) {
            advanceBeat();
            return;
        }

        // Spoken line (supports LINE, LINE_A, LINE_B)
        if (!beat.character.line.empty() ||
            !beat.character.lineA.empty() ||
            !beat.character.lineB.empty())
        {
            const std::string& line = (!beat.character.lineA.empty() || !beat.character.lineB.empty())
                ? (lastChoice == Choice::B ? beat.character.lineB : beat.character.lineA)
                : beat.character.line;

            activeNPCName = cid;
            activeEmotion = beat.character.emotion;
            std::string displayLine = line;
            dialogue->setMainDialogueText(displayLine);
            dialogue->showMainDialogue();
            currentState = State::SHOWING_NPC;
        }
        else {
            showChoiceBeat(beat.character);
        }
    }
    else if (beat.type == Beat::Type::GIVE_ITEM)
    {
        dispatchGiveItem(beat.giveItem);
        advanceBeat();
    }
    else if (beat.type == Beat::Type::GIVE_GOLD)
    {
        dispatchGiveGold(beat.giveGold);
        advanceBeat();
    }
    else if (beat.type == Beat::Type::GIVE_EXP)
    {
        dispatchGiveExp(beat.giveExp);
        advanceBeat();
    }
    else if (beat.type == Beat::Type::GIVE_ON_CHOICE)
    {
        dispatchGiveOnChoice(beat.giveOnChoice);
        advanceBeat();
    }
    else if (beat.type == Beat::Type::TAKE_GOLD)
    {
        dispatchTakeGold(beat.takeGold);
        advanceBeat();
    }
    else if (beat.type == Beat::Type::TAKE_ITEM)
    {
        dispatchTakeItem(beat.takeItem);
        advanceBeat();
    }
    else if (beat.type == Beat::Type::TAKE_DAMAGE)
    {
        dispatchTakeDamage(beat.takeDamage);
        advanceBeat();
    }
    else if (beat.type == Beat::Type::TAKE_ON_CHOICE)
    {
        dispatchTakeOnChoice(beat.takeOnChoice);
        advanceBeat();
    }
    else if (beat.type == Beat::Type::FIRE_TRIGGER)
    {
        dispatchFireTrigger(beat.fireTrigger);
        advanceBeat();
    }
    else if (beat.type == Beat::Type::FIRE_ON_CHOICE)
    {
        dispatchFireOnChoice(beat.fireOnChoice);
        advanceBeat();
    }
    else
    {
        std::cerr << "BeatSequencer: unknown beat type at index " << currentBeatIndex << "\n";
        advanceBeat();
    }
}

void BeatSequencer::showNPCBeat(const NPCBlock& block, const std::string& line)
{
    activeNPCName = block.npc;

    if (!block.emotionA.empty() || !block.emotionB.empty())
        activeEmotion = (lastChoice == Choice::B) ? block.emotionB : block.emotionA;
    else
        activeEmotion = block.emotion;

    std::string displayLine = line.empty() ? block.lineA : line;
    dialogue->setMainDialogueText(displayLine);
    dialogue->showMainDialogue();
    currentState = State::SHOWING_NPC;

    std::cout << "[NPC:" << block.npc << "|" << activeEmotion << "] " << displayLine << "\n";
}

void BeatSequencer::showChoiceBeat(const CharacterBlock& block)
{
    std::string responseA = Text::wrapText(block.responseA, 1800.f);
    std::string responseB = Text::wrapText(block.responseB, 1800.f);

    dialogue->setDialogueOptions(responseA, responseB);
    dialogue->showDialogueOptions();
    currentState = State::SHOWING_CHOICES;

    std::cout << "[CHOICE A] " << block.responseA << "\n";
    std::cout << "[CHOICE B] " << block.responseB << "\n";
}

// ============================================================
//  Trigger dispatch
// ============================================================

void BeatSequencer::dispatchFireTrigger(const FireTriggerBlock& block)
{
    if (block.triggerId.empty()) return;
    std::cout << "BeatSequencer: firing trigger: " << block.triggerId << "\n";
    TriggerManager::getInstance().fire(block.triggerId);
}

void BeatSequencer::dispatchFireOnChoice(const FireOnChoiceBlock& block)
{
    if (lastChoice == Choice::B)
    {
        if (!block.triggerB.empty())
        {
            std::cout << "BeatSequencer: firing trigger (choice B): " << block.triggerB << "\n";
            TriggerManager::getInstance().fire(block.triggerB);
        }
    }
    else
    {
        if (!block.triggerA.empty())
        {
            std::cout << "BeatSequencer: firing trigger (choice A): " << block.triggerA << "\n";
            TriggerManager::getInstance().fire(block.triggerA);
        }
    }
}

// ============================================================
//  Reward dispatch
// ============================================================

void BeatSequencer::dispatchGiveItem(const GiveItemBlock& block) { giveItem(block.itemId, block.quantity); }
void BeatSequencer::dispatchGiveGold(const GiveGoldBlock& block) { giveGold(block.amount); }
void BeatSequencer::dispatchGiveExp(const GiveExpBlock& block) { giveExpToParty(block.amount); }

void BeatSequencer::dispatchGiveOnChoice(const GiveOnChoiceBlock& block)
{
    if (lastChoice == Choice::B)
    {
        if (block.choiceBGiveGold > 0)        giveGold(block.choiceBGiveGold);
        if (!block.choiceBGiveItemId.empty()) giveItem(block.choiceBGiveItemId, block.choiceBGiveQuantity);
        if (block.choiceBGiveExp > 0.f)       giveExpToParty(block.choiceBGiveExp);
    }
    else
    {
        if (block.choiceAGiveGold > 0)        giveGold(block.choiceAGiveGold);
        if (!block.choiceAGiveItemId.empty()) giveItem(block.choiceAGiveItemId, block.choiceAGiveQuantity);
        if (block.choiceAGiveExp > 0.f)       giveExpToParty(block.choiceAGiveExp);
    }
}

// ============================================================
//  Penalty dispatch
// ============================================================

void BeatSequencer::dispatchTakeGold(const TakeGoldBlock& block) { takeGold(block.amount); }
void BeatSequencer::dispatchTakeItem(const TakeItemBlock& block) { takeItem(block.itemId, block.quantity); }
void BeatSequencer::dispatchTakeDamage(const TakeDamageBlock& block) { damagePartyMembers(block.amount); }

void BeatSequencer::dispatchTakeOnChoice(const TakeOnChoiceBlock& block)
{
    if (lastChoice == Choice::B)
    {
        if (block.choiceBLoseGold > 0)        takeGold(block.choiceBLoseGold);
        if (!block.choiceBLoseItemId.empty()) takeItem(block.choiceBLoseItemId, block.choiceBLoseQuantity);
        if (block.choiceBTakeDamage > 0.f)    damagePartyMembers(block.choiceBTakeDamage);
    }
    else
    {
        if (block.choiceALoseGold > 0)        takeGold(block.choiceALoseGold);
        if (!block.choiceALoseItemId.empty()) takeItem(block.choiceALoseItemId, block.choiceALoseQuantity);
        if (block.choiceATakeDamage > 0.f)    damagePartyMembers(block.choiceATakeDamage);
    }
}

// ============================================================
//  Reward helpers
// ============================================================

void BeatSequencer::giveGold(int amount)
{
    if (amount <= 0) return;
    Inventory::getInstance().addGold(amount);
    GameTriggers::showNotification("+" + std::to_string(amount) + " Gold");
    std::cout << "BeatSequencer: gave gold: " << amount << "\n";
}

void BeatSequencer::giveItem(const std::string& itemId, int quantity)
{
    if (Inventory::getInstance().addItem(itemId, quantity))
    {
        const auto* def = Inventory::getInstance().getItemDefinition(itemId);
        const std::string displayName = (def != nullptr) ? def->displayName : itemId;
        GameTriggers::showNotification("Obtained: " + displayName + " x" + std::to_string(quantity));
    }
    std::cout << "BeatSequencer: gave item: " << itemId << " x" << quantity << "\n";
}

void BeatSequencer::giveExpToParty(float amount)
{
    if (amount <= 0.f) return;

    bool anyGained = false;
    for (auto& member : CharacterManager::getInstance().getAllPartyMembers())
    {
        if (member && member->getStats())
        {
            member->getStats()->addExp(amount);
            anyGained = true;
            std::cout << "BeatSequencer: gave exp " << amount
                << " to " << member->getId() << "\n";
        }
    }

    if (anyGained)
        GameTriggers::showNotification("+" + std::to_string(static_cast<int>(amount)) + " Party EXP");
}

// ============================================================
//  Penalty helpers
// ============================================================

void BeatSequencer::takeGold(int amount)
{
    if (amount <= 0) return;
    const int currentGold = Inventory::getInstance().getGold();
    const int actualLoss = (amount < currentGold) ? amount : currentGold;
    Inventory::getInstance().removeGold(amount);
    if (actualLoss > 0)
        GameTriggers::showNotification("-" + std::to_string(actualLoss) + " Gold");
    std::cout << "BeatSequencer: took gold: " << amount << "\n";
}

void BeatSequencer::takeItem(const std::string& itemId, int quantity)
{
    if (Inventory::getInstance().removeItem(itemId, quantity))
    {
        const auto* def = Inventory::getInstance().getItemDefinition(itemId);
        const std::string displayName = (def != nullptr) ? def->displayName : itemId;
        GameTriggers::showNotification("Lost: " + displayName + " x" + std::to_string(quantity));
    }
    std::cout << "BeatSequencer: took item: " << itemId << " x" << quantity << "\n";
}

void BeatSequencer::damagePartyMembers(float amount)
{
    if (amount <= 0.f) return;

    bool anyDamaged = false;
    for (auto& member : CharacterManager::getInstance().getAllPartyMembers())
    {
        if (member)
        {
            member->takeDamage(amount);
            anyDamaged = true;
            std::cout << "BeatSequencer: dealt " << amount
                << " damage to " << member->getId() << "\n";
        }
    }

    if (anyDamaged)
        GameTriggers::showNotification("The party takes "
            + std::to_string(static_cast<int>(amount)) + " damage!");
}