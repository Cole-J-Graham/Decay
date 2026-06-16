#pragma once
#include "Beat.h"
#include "DialogueInputComponent.h"
#include <vector>
#include <string>
#include <memory>

// ============================================================
//  BeatSequencer
//  Owns the beat vector for one event playthrough.
//  Drives the state machine, handles all reward dispatch,
//  and tells the DialogueInputComponent what to show.
// ============================================================

class BeatSequencer
{
public:
    enum class State
    {
        IDLE,
        SHOWING_NPC,
        SHOWING_CHOICES
    };

    enum class Choice { NONE, A, B };

    BeatSequencer();

    // Load a new set of beats and start from the beginning.
    void start(std::vector<Beat> beats, DialogueInputComponent* dialogue);

    // Call every frame — handles click input and drives the sequence.
    void update(sf::Vector2f mousePos);

    // Active NPC name for portrait rendering in EventManager.
    const std::string& getActiveNPCName() const { return activeNPCName; }
    const std::string& getActiveEmotion() const { return activeEmotion; }

    State getState() const { return currentState; }

    bool isRunning()  const { return running; }

    // isFinished() stays true after the sequence ends until reset() is called.
    // This gives EventManager a reliable one-frame window to detect completion
    // even after the sequencer has internally cleaned up.
    bool isFinished() const { return finished; }

    void reset();

private:
    void advanceBeat();
    void updateInput();

    void showNPCBeat(const NPCBlock& block, const std::string& line);
    void showChoiceBeat(const CharacterBlock& block);

    void dispatchFireTrigger(const FireTriggerBlock& block);
    void dispatchFireOnChoice(const FireOnChoiceBlock& block);

    void dispatchGiveItem(const GiveItemBlock& block);
    void dispatchGiveGold(const GiveGoldBlock& block);
    void dispatchGiveExp(const GiveExpBlock& block);
    void dispatchGiveOnChoice(const GiveOnChoiceBlock& block);

    void dispatchTakeGold(const TakeGoldBlock& block);
    void dispatchTakeItem(const TakeItemBlock& block);
    void dispatchTakeDamage(const TakeDamageBlock& block);
    void dispatchTakeOnChoice(const TakeOnChoiceBlock& block);

    // Reward helpers
    void giveGold(int amount);
    void giveItem(const std::string& itemId, int quantity);
    void giveExpToParty(float amount);

    // Penalty helpers
    void takeGold(int amount);
    void takeItem(const std::string& itemId, int quantity);
    void damagePartyMembers(float amount);

    // [IF_FOLLOWER]/[END_IF] resolution
    std::vector<Beat> resolveConditionals(const std::vector<Beat>& inBeats);

    std::vector<Beat>       beats;
    int                     currentBeatIndex = -1;

    Choice                  lastChoice = Choice::NONE;
    State                   currentState = State::IDLE;
    std::string             activeNPCName;
    std::string             activeEmotion;

    bool                    running = false;
    bool                    finished = false; // stays true until reset()

    DialogueInputComponent* dialogue = nullptr;
};