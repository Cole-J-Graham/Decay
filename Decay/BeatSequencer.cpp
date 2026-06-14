#include "BeatSequencer.h"
#include "Inventory.h"
#include "CharacterManager.h"
#include "GameTriggers.h"
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
    started = true;

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
    started = false;
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
                // Follower is here — keep the inner beats, drop just this marker.
                continue;
            }

            // Follower isn't here — skip everything up to and including the
            // matching END_IF. If no END_IF is found (malformed event file),
            // this consumes the rest of the sequence.
            while (i < inBeats.size() && inBeats[i].type != Beat::Type::CONDITION_END)
                ++i;

            continue; // also drops the CONDITION_END itself
        }

        if (beat.type == Beat::Type::CONDITION_END)
        {
            // Block was kept (its CONDITION_START fell through above) —
            // drop the closing marker too.
            continue;
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
        std::cout << "BeatSequencer: sequence finished.\n";
        return;
    }

    const Beat& beat = beats[currentBeatIndex];

    if (beat.type == Beat::Type::NPC)
    {
        const std::string& line = (lastChoice == Choice::B)
            ? beat.npc.lineB
            : beat.npc.lineA;
        showNPCBeat(beat.npc, line);
    }
    else if (beat.type == Beat::Type::CHARACTER)
    {
        const std::string& cid = beat.character.characterId;

        bool inParty = false;

        if (!cid.empty()) {
            for (const auto& member : CharacterManager::getInstance().getAllPartyMembers()) {
                if (member && member->getId() == cid) {
                    inParty = true;
                    break;
                }
            }
        }
        else {
            inParty = true; // no ID, always show (choice blocks without a character)
        }

        if (!inParty) {
            advanceBeat(); // not in party, skip silently
            return;
        }

        if (!beat.character.line.empty())
        {
            // Spoken line — show like NPC but with character portrait
            activeNPCName = cid;
            activeEmotion = beat.character.emotion;  // empty string is fine, setEmotion handles it
            std::string line = beat.character.line;
            dialogue->setMainDialogueText(line);
            dialogue->showMainDialogue();
            currentState = State::SHOWING_NPC; // reuse NPC click-to-continue flow
        }
        else {
            showChoiceBeat(beat.character); // existing choice behaviour
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
    else
    {
        std::cerr << "BeatSequencer: unknown beat type at index " << currentBeatIndex << "\n";
        advanceBeat();
    }
}

void BeatSequencer::showNPCBeat(const NPCBlock& block, const std::string& line)
{
    activeNPCName = block.npc;

    if (!block.emotionA.empty() || !block.emotionB.empty()) {
        activeEmotion = (lastChoice == Choice::B) ? block.emotionB : block.emotionA;
    }
    else {
        activeEmotion = block.emotion;
    }

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
//  Reward dispatch
// ============================================================

void BeatSequencer::dispatchGiveItem(const GiveItemBlock& block)
{
    giveItem(block.itemId, block.quantity);
}

void BeatSequencer::dispatchGiveGold(const GiveGoldBlock& block)
{
    giveGold(block.amount);
}

void BeatSequencer::dispatchGiveExp(const GiveExpBlock& block)
{
    giveExpToParty(block.amount);
}

void BeatSequencer::dispatchGiveOnChoice(const GiveOnChoiceBlock& block)
{
    if (lastChoice == Choice::B)
    {
        if (block.choiceBGold > 0)
            giveGold(block.choiceBGold);
        if (!block.choiceBItemId.empty())
            giveItem(block.choiceBItemId, block.choiceBQuantity);
        if (block.choiceBExp > 0.f)
            giveExpToParty(block.choiceBExp);
    }
    else // Choice::A or NONE defaults to A
    {
        if (block.choiceAGold > 0)
            giveGold(block.choiceAGold);
        if (!block.choiceAItemId.empty())
            giveItem(block.choiceAItemId, block.choiceAQuantity);
        if (block.choiceAExp > 0.f)
            giveExpToParty(block.choiceAExp);
    }
}

// ============================================================
//  Penalty dispatch
// ============================================================

void BeatSequencer::dispatchTakeGold(const TakeGoldBlock& block)
{
    takeGold(block.amount);
}

void BeatSequencer::dispatchTakeItem(const TakeItemBlock& block)
{
    takeItem(block.itemId, block.quantity);
}

void BeatSequencer::dispatchTakeDamage(const TakeDamageBlock& block)
{
    damagePartyMembers(block.amount);
}

void BeatSequencer::dispatchTakeOnChoice(const TakeOnChoiceBlock& block)
{
    if (lastChoice == Choice::B)
    {
        if (block.choiceBGold > 0)
            takeGold(block.choiceBGold);
        if (!block.choiceBItemId.empty())
            takeItem(block.choiceBItemId, block.choiceBQuantity);
        if (block.choiceBDamage > 0.f)
            damagePartyMembers(block.choiceBDamage);
    }
    else // Choice::A or NONE defaults to A
    {
        if (block.choiceAGold > 0)
            takeGold(block.choiceAGold);
        if (!block.choiceAItemId.empty())
            takeItem(block.choiceAItemId, block.choiceAQuantity);
        if (block.choiceADamage > 0.f)
            damagePartyMembers(block.choiceADamage);
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
        GameTriggers::showNotification("The party takes " + std::to_string(static_cast<int>(amount)) + " damage!");
}