#include "EventManager.h"
#include "GameFlags.h"
#include "TriggerManager.h"
#include "NPCManager.h"
#include "CharacterManager.h"
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
    this->forceEvent();
}

EventManager::~EventManager() {}

// ============================================================
//  Core
// ============================================================

void EventManager::update(sf::Vector2f mousePos)
{
    if (!eventActivated) return;

    if (!sequencer.isRunning())
        updateEvents();

    sequencer.update(mousePos);

    if (sequencer.isFinished())
        onSequenceFinished();
}

void EventManager::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    dialogueInput->render(target);

    const std::string& activeName = sequencer.getActiveNPCName();
    if (activeName.empty()) return;

    // Check NPCManager first
    NPC* npc = NPCManager::getInstance().getNPC(activeName);
    if (npc)
    {
        npc->setEmotion(sequencer.getActiveEmotion());
        npc->renderPreview(target, EVENT_PORTRAIT_X, EVENT_PORTRAIT_Y);
        return;
    }

    // Fall back to CharacterManager — party characters can speak too
    auto character = CharacterManager::getInstance().getCharacter(activeName);
    if (character)
    {
        character->setEmotion(sequencer.getActiveEmotion());
        character->renderPreview(target, EVENT_PORTRAIT_X, EVENT_PORTRAIT_Y);
    }
}

// ============================================================
//  Event lifecycle
// ============================================================

void EventManager::initEvents()
{
    this->getEventsInDirectory("Assets/Events/" + this->areaName);

    for (const auto& e : events)
    {
        std::cout << "EVENT LOADED: " << e.path
            << " | oneTime: " << e.oneTime
            << " | hasPlayed: " << e.hasPlayed << "\n";
    }
}

void EventManager::updateEvents()
{
    if (!eventActivated) return;
    if (sequencer.isRunning()) return;
    if (events.empty())
    {
        eventActivated = false;
        std::cout << "No events loaded.\n";
        return;
    }

    std::vector<int> valid;
    for (int i = 0; i < (int)events.size(); ++i)
        if (eventCanPlay(events[i]))
            valid.push_back(i);

    if (valid.empty())
    {
        eventActivated = false;
        std::cout << "No playable events remaining.\n";
        return;
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0, (int)valid.size() - 1);
    activeEventIndex = valid[dist(rng)];

    const std::string& path = events[activeEventIndex].path;
    std::vector<Beat> beats = parser.parse(path);

    if (beats.empty())
    {
        std::cerr << "EventManager: no beats parsed from: " << path << "\n";
        eventActivated = false;
        return;
    }

    sequencer.start(std::move(beats), dialogueInput.get());
}

void EventManager::onSequenceFinished()
{
    if (activeEventIndex >= 0 && activeEventIndex < (int)events.size())
        if (events[activeEventIndex].oneTime)
            events[activeEventIndex].hasPlayed = true;

    if (!completionFlag.empty())
        GameFlags::getInstance().set(completionFlag);
    if (!completionTrigger.empty())
        TriggerManager::getInstance().fire(completionTrigger);

    sequencer.reset();
    eventActivated = false;
    activeEventIndex = -1;

    std::cout << "EventManager: event finished.\n";
}

// ============================================================
//  Probability
// ============================================================

bool EventManager::eventChance()
{
    if (eventActivated) return true;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(
        (int)eventThresholdMin,
        (int)eventThresholdMax);

    if ((int)eventOdds > dist(rng))
    {
        std::cout << "Event triggered!\n";
        eventActivated = true;
        eventOdds = 0.f;
        eventIncrease = 1.f;
        return true;
    }

    std::cout << "Event not triggered, odds increased.\n";
    eventOdds += eventIncrease;
    eventIncrease *= 2.f;
    return false;
}

void EventManager::forceEvent()
{
    eventActivated = true;
    eventOdds = 0.f;
    eventIncrease = 1.f;
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

            events.push_back(ev);
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