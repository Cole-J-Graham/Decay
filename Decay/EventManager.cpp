#include "EventManager.h"
#include "GameFlags.h"
#include "TriggerManager.h"
#include <iostream>

namespace
{
    constexpr float EVENT_PORTRAIT_X = 25.f;
    constexpr float EVENT_PORTRAIT_Y = 585.f;
}

// ============================================================
//  Constructors / Destructor
// ============================================================

EventManager::EventManager(const std::string& areaName)
    : areaName(areaName)
{
    this->dialogueInput = std::make_unique<DialogueInputComponent>();
    this->initEvents();
}

EventManager::EventManager(const std::string& areaName,
    const std::string& completionFlag,
    const std::string& completionTrigger)
    : areaName(areaName)
    , completionFlag(completionFlag)
    , completionTrigger(completionTrigger)
{
    this->dialogueInput = std::make_unique<DialogueInputComponent>();
    this->initEvents();
    this->forceEvent();  // one-time intros always auto-activate
}

EventManager::~EventManager() {}

// ============================================================
//  Core
// ============================================================

void EventManager::update(sf::Vector2f mousePos)
{
    this->dialogueInput->update(mousePos);
    this->updateEvents();
    this->updateInput();
}

void EventManager::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    this->dialogueInput->render(target);

    if (this->activeNPCName.empty()) return;

    auto character = CharacterManager::getInstance().getCharacter(this->activeNPCName);
    if (character == nullptr) return;

    character->renderPreview(target, EVENT_PORTRAIT_X, EVENT_PORTRAIT_Y);
}

// ============================================================
//  Event lifecycle
// ============================================================

void EventManager::initEvents()
{
    this->getEventsInDirectory("Assets/Events/" + this->areaName);

    for (auto& e : events)
    {
        std::cout << "EVENT LOADED: " << e.path
            << " | oneTime: " << e.oneTime
            << " | hasPlayed: " << e.hasPlayed << "\n";
    }
}

void EventManager::updateEvents()
{
    if (!this->eventActivated) return;

    if (!this->eventRunning && !this->events.empty())
    {
        std::vector<int> valid;
        for (int i = 0; i < (int)this->events.size(); ++i)
            if (this->eventCanPlay(this->events[i]))
                valid.push_back(i);

        if (valid.empty())
        {
            this->eventActivated = false;
            std::cout << "No playable events remaining.\n";
            return;
        }

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> dist(0, (int)valid.size() - 1);
        this->activeEventIndex = valid[dist(rng)];

        const std::string& path = this->events[this->activeEventIndex].path;
        if (this->openFile(path))
        {
            std::cout << "Opened event file: " << path << "\n";
            this->eventRunning = true;
            this->eventStarted = true;
            this->loadEventFile(path);
            this->currentBeatIndex = -1;
            this->lastChoice = Choice::NONE;
            this->advanceBeat();
        }
    }
}

// ============================================================
//  Input handling
// ============================================================

void EventManager::updateInput()
{
    if (currentState == State::SHOWING_CHOICES)
    {
        if (this->dialogueInput->topDialogueClicked())
        {
            this->lastChoice = Choice::A;
            this->dialogueInput->hideDialogueOptions();
            this->currentState = State::IDLE;
            this->advanceBeat();
        }
        else if (this->dialogueInput->bottomDialogueClicked())
        {
            this->lastChoice = Choice::B;
            this->dialogueInput->hideDialogueOptions();
            this->currentState = State::IDLE;
            this->advanceBeat();
        }
    }
    else if (currentState == State::SHOWING_NPC)
    {
        if (this->dialogueInput->mainDialogueClicked())
        {
            std::string empty = "";
            this->dialogueInput->hideMainDialogue();
            this->dialogueInput->setMainDialogueText(empty);
            this->currentState = State::IDLE;
            this->advanceBeat();
        }
    }
}

// ============================================================
//  Beat sequencing
// ============================================================

void EventManager::advanceBeat()
{
    ++this->currentBeatIndex;

    if (this->currentBeatIndex >= (int)this->beats.size())
    {
        // Mark one-time events as played
        if (this->activeEventIndex >= 0 && this->activeEventIndex < (int)this->events.size())
            if (this->events[this->activeEventIndex].oneTime)
                this->events[this->activeEventIndex].hasPlayed = true;

        // Set completion flag and fire trigger if this was a one-time intro event
        if (!this->completionFlag.empty())
            GameFlags::getInstance().set(this->completionFlag);
        if (!this->completionTrigger.empty())
            TriggerManager::getInstance().fire(this->completionTrigger);

        this->eventRunning = false;
        this->eventActivated = false;
        this->activeEventIndex = -1;
        this->currentBeatIndex = -1;
        this->activeNPCName = "";
        this->beats.clear();

        std::cout << "Event finished.\n";
        return;
    }

    const Beat& beat = this->beats[this->currentBeatIndex];

    if (beat.type == Beat::Type::NPC)
    {
        const std::string& line = (this->lastChoice == Choice::B)
            ? beat.npc.lineB
            : beat.npc.lineA;
        this->showNPCBeat(beat.npc, line);
    }
    else
    {
        this->showChoiceBeat(beat.character);
    }
}

void EventManager::showNPCBeat(const NPCBlock& block, const std::string& line)
{
    this->activeNPCName = block.npc;

    std::string displayLine = line.empty() ? block.lineA : line;
    this->dialogueInput->setMainDialogueText(displayLine);
    this->dialogueInput->showMainDialogue();
    this->currentState = State::SHOWING_NPC;

    std::cout << "[NPC:" << block.npc << "|" << block.emotion << "] " << displayLine << "\n";
}

void EventManager::showChoiceBeat(const CharacterBlock& block)
{
    this->dialogueInput->setDialogueOptions(
        const_cast<std::string&>(block.responseA),
        const_cast<std::string&>(block.responseB));
    this->dialogueInput->showDialogueOptions();
    this->currentState = State::SHOWING_CHOICES;

    std::cout << "[CHOICE A] " << block.responseA << "\n";
    std::cout << "[CHOICE B] " << block.responseB << "\n";
}

// ============================================================
//  File parsing
// ============================================================

void EventManager::loadEventFile(const std::string& /*path*/)
{
    this->beats.clear();

    std::string line;
    while (true)
    {
        line = this->readFileLine();
        if (line.empty() && ifs.eof()) break;
        if (line.empty()) continue;

        if (line == "[SPEAK_NPC]")
            this->beats.push_back(this->parseNPCBlock());
        else if (line == "[SPEAK_CHARACTER]")
            this->beats.push_back(this->parseCharacterBlock());
        else
            std::cout << "Unknown block header: " << line << "\n";
    }

    std::cout << "Loaded " << this->beats.size() << " beats.\n";
    this->closeFile();
}

EventManager::Beat EventManager::parseNPCBlock()
{
    Beat beat;
    beat.type = Beat::Type::NPC;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;

        auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "NPC")     beat.npc.npc = val;
        else if (key == "EMOTION") beat.npc.emotion = val;
        else if (key == "LINE") { beat.npc.lineA = val; beat.npc.lineB = val; }
        else if (key == "LINE_A")  beat.npc.lineA = val;
        else if (key == "LINE_B")  beat.npc.lineB = val;
    }

    if (beat.npc.lineB.empty()) beat.npc.lineB = beat.npc.lineA;

    return beat;
}

EventManager::Beat EventManager::parseCharacterBlock()
{
    Beat beat;
    beat.type = Beat::Type::CHARACTER;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;

        auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "RESPONSE_A") beat.character.responseA = val;
        else if (key == "RESPONSE_B") beat.character.responseB = val;
    }

    return beat;
}

std::string EventManager::readFileLine()
{
    std::string line;
    if (std::getline(ifs, line))
        return line;
    return "";
}

std::string EventManager::parseValue(const std::string& line)
{
    auto sep = line.find(':');
    if (sep == std::string::npos || sep + 2 > line.size()) return "";
    return line.substr(sep + 2);
}

// ============================================================
//  File management
// ============================================================

bool EventManager::openFile(const std::string& path)
{
    ifs.open(path);
    isFileOpen = ifs.is_open();
    if (!isFileOpen)
        std::cerr << "Failed to open file: " << path << "\n";
    return isFileOpen;
}

void EventManager::closeFile()
{
    if (isFileOpen)
    {
        ifs.close();
        isFileOpen = false;
    }
}

// ============================================================
//  Probability
// ============================================================

bool EventManager::eventChance()
{
    if (this->eventActivated) return true;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(
        (int)this->eventThresholdMin,
        (int)this->eventThresholdMax);

    if ((int)this->eventOdds > dist(rng))
    {
        std::cout << "Event triggered!\n";
        this->eventActivated = true;
        this->eventOdds = 0.f;
        this->eventIncrease = 1.f;
        return true;
    }

    std::cout << "Event not triggered, odds increased.\n";
    this->eventOdds += this->eventIncrease;
    this->eventIncrease *= 2.f;
    return false;
}

void EventManager::forceEvent()
{
    this->eventActivated = true;
    this->eventOdds = 0.f;
    this->eventIncrease = 1.f;
}

// ============================================================
//  Directory scanning
// ============================================================

void EventManager::getEventsInDirectory(const std::string& directoryPath)
{
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
        {
            if (!entry.is_regular_file()) continue;

            EventDefinition ev;
            ev.path = entry.path().string();
            ev.oneTime = entry.path().filename().string().find(".once.") != std::string::npos;
            ev.hasPlayed = false;

            this->events.push_back(ev);
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
}

// ============================================================
//  Helper
// ============================================================

bool EventManager::eventCanPlay(const EventDefinition& event) const
{
    return !(event.oneTime && event.hasPlayed);
}