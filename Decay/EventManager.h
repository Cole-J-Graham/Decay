#pragma once
#include <filesystem>
#include <fstream>
#include <random>
#include <deque>
#include <vector>
#include <string>
#include <memory>
#include "CombatState.h"
#include "DialogueInputComponent.h"

class EventManager
{
public:
    // -------------------------------------------------------
    //  Constructors and Destructors
    // -------------------------------------------------------

    // General-purpose constructor — used by TravelState and others
    // that trigger events by chance or via forceEvent().
    EventManager(const std::string& areaName);

    // One-time intro constructor — automatically force-activates the event,
    // sets the completion flag, and optionally fires a trigger when done.
    // The calling state only needs to check hasFinished() each frame.
    EventManager(const std::string& areaName,
        const std::string& completionFlag,
        const std::string& completionTrigger = "");

    ~EventManager();

    //Core Functions
    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

    //Event Functions
    void initEvents();
    void updateEvents();
    bool eventChance();
    void forceEvent();

    //Getters
    bool isEventActive() const { return this->eventActivated; }
    bool hasFinished()   const { return this->eventStarted && !this->eventRunning; }

private:

    // -------------------------------------------------------
    //  Block types parsed from event files
    // -------------------------------------------------------
    struct NPCBlock
    {
        std::string npc;
        std::string emotion;
        std::string lineA;
        std::string lineB;
    };

    struct CharacterBlock
    {
        std::string responseA;
        std::string responseB;
    };

    struct Beat
    {
        enum class Type { NPC, CHARACTER } type;
        NPCBlock       npc;
        CharacterBlock character;
    };

    // -------------------------------------------------------
    //  Event file definition
    // -------------------------------------------------------
    struct EventDefinition
    {
        std::string path;
        bool        oneTime = false;
        bool        hasPlayed = false;
    };

    // -------------------------------------------------------
    //  State machine
    // -------------------------------------------------------
    enum class State
    {
        IDLE,
        SHOWING_NPC,
        SHOWING_CHOICES,
    };

    enum class Choice { NONE, A, B };

    // -------------------------------------------------------
    //  Private helpers
    // -------------------------------------------------------
    void        initInternal();
    void        loadEventFile(const std::string& path);
    void        advanceBeat();
    void        showNPCBeat(const NPCBlock& block, const std::string& line);
    void        showChoiceBeat(const CharacterBlock& block);

    Beat        parseNPCBlock();
    Beat        parseCharacterBlock();
    std::string parseValue(const std::string& line);

    bool        openFile(const std::string& path);
    void        closeFile();
    std::string readFileLine();

    void        getEventsInDirectory(const std::string& directoryPath);
    bool        eventCanPlay(const EventDefinition& event) const;
    void        updateInput();

    // -------------------------------------------------------
    //  Members
    // -------------------------------------------------------
    std::unique_ptr<DialogueInputComponent> dialogueInput;

    // One-time event completion — set at construction, used in advanceBeat()
    std::string completionFlag;
    std::string completionTrigger;

    // Probability
    bool  eventActivated = false;
    bool  eventRunning = false;
    bool  eventStarted = false;
    float eventOdds = 0.f;
    float eventIncrease = 1.f;
    float eventThresholdMax = 1000.f;
    float eventThresholdMin = 0.f;

    // Area / file
    std::string   areaName;
    std::ifstream ifs;
    bool          isFileOpen = false;

    // Beat sequence
    std::vector<Beat> beats;
    int               currentBeatIndex = -1;

    // Player's last choice
    Choice lastChoice = Choice::NONE;

    // Active event tracking
    std::deque<EventDefinition> events;
    int                         activeEventIndex = -1;

    // Display state
    State       currentState = State::IDLE;
    std::string activeNPCName;
};