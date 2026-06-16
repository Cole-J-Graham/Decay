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
    // General-purpose constructor — scans a directory for event files.
    EventManager(const std::string& areaName);

    // One-time intro constructor — auto-activates and sets a
    // completion flag / trigger when the sequence finishes.
    EventManager(const std::string& areaName,
        const std::string& completionFlag,
        const std::string& completionTrigger = "");

    // Direct-file constructor — plays exactly one specific file.
    // suppressPortrait = true skips NPC/character portrait rendering,
    // used by BonfireState where the sprite is already visible in the slot.
    EventManager(const std::string& areaName,
        const std::string& filePath,
        bool directFile,
        const std::string& completionTrigger = "",
        bool suppressPortrait = false);

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

    // hasFinished() is set by EventManager itself when onSequenceFinished()
    // runs, and stays true until this EventManager is destroyed.
    // It does NOT delegate to the sequencer (which resets itself immediately).
    bool hasFinished() const { return finished; }

private:
    struct EventDefinition
    {
        std::string path;
        bool        oneTime = false;
        bool        hasPlayed = false;
        std::string playedFlagKey;
    };

    void getEventsInDirectory(const std::string& directoryPath);
    void loadSingleFile(const std::string& filePath);
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

    // Set in onSequenceFinished(), stays true — callers poll this
    bool finished = false;

    // When true, render() skips NPC/character portrait drawing.
    // Used for bonfire companion conversations where the sprite
    // is already rendered in the party preview slot.
    bool suppressPortrait = false;

    // Area
    std::string areaName;

    // Event list
    std::deque<EventDefinition> events;
    int                         activeEventIndex = -1;
};