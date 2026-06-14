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
    std::string line;
    std::string responseA;
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

// Downside counterparts to GIVE_GOLD / GIVE_ITEM / GIVE_ON_CHOICE.
// TAKE_GOLD/TAKE_ITEM/TAKE_DAMAGE are unconditional penalties applied as
// soon as the beat is reached. TAKE_ON_CHOICE applies a penalty based on
// lastChoice, mirroring GIVE_ON_CHOICE.
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
    float amount = 0.f;  // flat HP damage applied to each party member
};

struct TakeOnChoiceBlock
{
    // Choice A penalties
    int         choiceAGold = 0;
    std::string choiceAItemId;
    int         choiceAQuantity = 1;
    float       choiceADamage = 0.f;

    // Choice B penalties
    int         choiceBGold = 0;
    std::string choiceBItemId;
    int         choiceBQuantity = 1;
    float       choiceBDamage = 0.f;
};

// [IF_FOLLOWER] / [END_IF] markers. CONDITION_START carries the required
// party member id; CONDITION_END carries nothing. BeatSequencer strips both
// out (and the bracketed beats too, if the follower isn't present) during
// resolveConditionals() before playback — nothing past that point ever sees
// these types.
struct ConditionBlock
{
    std::string followerId;  // party member id required for this block to play
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
        CONDITION_END
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
};