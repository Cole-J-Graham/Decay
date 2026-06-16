#pragma once
#include <string>

// ============================================================
//  Beat.h
//  All data structures that describe a single step in an
//  event sequence. EventFileParser produces these; 
//  BeatSequencer consumes them.
// ============================================================

struct NPCBlock
{
    std::string npc;
    std::string emotion;    // flat, applies regardless of choice
    std::string emotionA;   // if last choice was A
    std::string emotionB;   // if last choice was B
    std::string lineA;
    std::string lineB;
};

struct CharacterBlock
{
    std::string characterId;
    std::string emotion;    // portrait emotion when this character speaks
    std::string line;       // single line (no choice dependency)
    std::string lineA;      // spoken if last choice was A (or NONE)
    std::string lineB;      // spoken if last choice was B
    std::string responseA;  // choice button text
    std::string responseB;
};

struct GiveItemBlock
{
    std::string itemId;
    int         quantity = 1;
};

struct GiveGoldBlock
{
    int amount = 0;
};

struct GiveExpBlock
{
    float amount = 0.f;
};

struct GiveOnChoiceBlock
{
    // Choice A
    int         choiceAGold = 0;
    std::string choiceAItemId;
    int         choiceAQuantity = 1;
    float       choiceAExp = 0.f;

    // Choice B
    int         choiceBGold = 0;
    std::string choiceBItemId;
    int         choiceBQuantity = 1;
    float       choiceBExp = 0.f;
};

struct TakeGoldBlock
{
    int amount = 0;
};

struct TakeItemBlock
{
    std::string itemId;
    int         quantity = 1;
};

struct TakeDamageBlock
{
    float amount = 0.f;
};

struct TakeOnChoiceBlock
{
    int         choiceAGold = 0;
    std::string choiceAItemId;
    int         choiceAQuantity = 1;
    float       choiceADamage = 0.f;

    int         choiceBGold = 0;
    std::string choiceBItemId;
    int         choiceBQuantity = 1;
    float       choiceBDamage = 0.f;
};

// [IF_FOLLOWER] / [END_IF] markers.
struct ConditionBlock
{
    std::string followerId;
};

// [FIRE_TRIGGER] — fires a TriggerManager key instantly, no click required.
struct FireTriggerBlock
{
    std::string triggerId;
};

// [FIRE_ON_CHOICE] — fires different triggers depending on the last choice.
struct FireOnChoiceBlock
{
    std::string triggerA;
    std::string triggerB;
};

struct Beat
{
    enum class Type
    {
        NPC,
        CHARACTER,
        GIVE_ITEM,
        GIVE_GOLD,
        GIVE_EXP,
        GIVE_ON_CHOICE,
        TAKE_GOLD,
        TAKE_ITEM,
        TAKE_DAMAGE,
        TAKE_ON_CHOICE,
        CONDITION_START,
        CONDITION_END,
        FIRE_TRIGGER,
        FIRE_ON_CHOICE
    } type;

    NPCBlock          npc;
    CharacterBlock    character;
    GiveItemBlock     giveItem;
    GiveGoldBlock     giveGold;
    GiveExpBlock      giveExp;
    GiveOnChoiceBlock giveOnChoice;
    TakeGoldBlock     takeGold;
    TakeItemBlock     takeItem;
    TakeDamageBlock   takeDamage;
    TakeOnChoiceBlock takeOnChoice;
    ConditionBlock    condition;
    FireTriggerBlock  fireTrigger;
    FireOnChoiceBlock fireOnChoice;
};