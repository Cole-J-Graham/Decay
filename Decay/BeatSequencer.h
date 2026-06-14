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
    bool isFinished() const { return started && !running; }

    void reset();

private:
    void advanceBeat();
    void updateInput();

    void showNPCBeat(const NPCBlock& block, const std::string& line);
    void showChoiceBeat(const CharacterBlock& block);

    void dispatchGiveItem(const GiveItemBlock& block);
    void dispatchGiveGold(const GiveGoldBlock& block);
    void dispatchGiveExp(const GiveExpBlock& block);
    void dispatchGiveOnChoice(const GiveOnChoiceBlock& block);

    void dispatchTakeGold(const TakeGoldBlock& block);
    void dispatchTakeItem(const TakeItemBlock& block);
    void dispatchTakeDamage(const TakeDamageBlock& block);
    void dispatchTakeOnChoice(const TakeOnChoiceBlock& block);

    // Rewards helpers
    void giveGold(int amount);
    void giveItem(const std::string& itemId, int quantity);
    void giveExpToParty(float amount);

    // Penalty helpers
    void takeGold(int amount);
    void takeItem(const std::string& itemId, int quantity);
    void damagePartyMembers(float amount);

    // [IF_FOLLOWER]/[END_IF] resolution. Strips CONDITION_START/CONDITION_END
    // markers from the beat list before playback — drops the bracketed beats
    // entirely if the named follower isn't currently in the party, or
    // unwraps (keeps) them if present.
    std::vector<Beat> resolveConditionals(const std::vector<Beat>& inBeats);

    std::vector<Beat>          beats;
    int                        currentBeatIndex = -1;

    Choice                     lastChoice = Choice::NONE;
    State                      currentState = State::IDLE;
    std::string                activeNPCName;
    std::string                activeEmotion;

    bool                       running = false;
    bool                       started = false;

    DialogueInputComponent* dialogue = nullptr;
};