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

    // Rewards helpers
    void giveGold(int amount);
    void giveItem(const std::string& itemId, int quantity);
    void giveExpToParty(float amount);

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