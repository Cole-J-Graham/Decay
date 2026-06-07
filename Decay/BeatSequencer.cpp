#include "BeatSequencer.h"
#include "Inventory.h"
#include "CharacterManager.h"
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
    beats = std::move(inBeats);
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
    dialogue->setDialogueOptions(
        const_cast<std::string&>(block.responseA),
        const_cast<std::string&>(block.responseB));
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
//  Reward helpers
// ============================================================

void BeatSequencer::giveGold(int amount)
{
    Inventory::getInstance().addGold(amount);
    std::cout << "BeatSequencer: gave gold: " << amount << "\n";
}

void BeatSequencer::giveItem(const std::string& itemId, int quantity)
{
    Inventory::getInstance().addItem(itemId, quantity);
    std::cout << "BeatSequencer: gave item: " << itemId << " x" << quantity << "\n";
}

void BeatSequencer::giveExpToParty(float amount)
{
    for (auto& member : CharacterManager::getInstance().getAllPartyMembers())
    {
        if (member && member->getStats())
        {
            member->getStats()->addExp(amount);
            std::cout << "BeatSequencer: gave exp " << amount
                << " to " << member->getId() << "\n";
        }
    }
}
