#pragma once
#include <filesystem>
#include <fstream>
#include <random>
#include <deque>
#include <vector>
#include <string>
#include <memory>
#include "BeatSequencer.h"
#include "EventFileParser.h"
#include "CombatState.h"
#include "DialogueInputComponent.h"

// ============================================================
//  EventManager
//  Owns event lifecycle (activation, directory scanning,
//  one-time tracking, probability) and rendering.
//  Delegates all beat logic to BeatSequencer and all file
//  parsing to EventFileParser.
// ============================================================

class EventManager
{
public:
    // General-purpose constructor.
    EventManager(const std::string& areaName);

    // One-time intro constructor — auto-activates and sets a
    // completion flag / trigger when the sequence finishes.
    EventManager(const std::string& areaName,
        const std::string& completionFlag,
        const std::string& completionTrigger = "");

    ~EventManager();

    // Core
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

    // Event control
    void initEvents();
    void updateEvents();
    bool eventChance();
    void forceEvent();

    // Getters
    bool isEventActive() const { return eventActivated; }
    bool hasFinished()   const { return sequencer.isFinished(); }

private:
    struct EventDefinition
    {
        std::string path;
        bool        oneTime = false;
        bool        hasPlayed = false;

        // GameFlags key used to persist hasPlayed for one-time events
        // across EventManager reconstructions (area revisits, save/load).
        std::string playedFlagKey;
    };

    void getEventsInDirectory(const std::string& directoryPath);
    bool eventCanPlay(const EventDefinition& event) const;
    void onSequenceFinished();

    // Subsystems
    std::unique_ptr<DialogueInputComponent> dialogueInput;
    BeatSequencer                           sequencer;
    EventFileParser                         parser;

    // One-time completion
    std::string completionFlag;
    std::string completionTrigger;

    // Probability
    bool  eventActivated = false;
    float eventOdds = 0.f;
    float eventIncrease = 1.f;
    float eventThresholdMax = 1000.f;
    float eventThresholdMin = 0.f;

    // Area
    std::string areaName;

    // Event list
    std::deque<EventDefinition> events;
    int                         activeEventIndex = -1;
};