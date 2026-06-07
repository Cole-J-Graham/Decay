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

struct Beat
{
    enum class Type
    {
        NPC,
        CHARACTER,
        GIVE_ITEM,
        GIVE_GOLD,
        GIVE_EXP,
        GIVE_ON_CHOICE
    } type;

    NPCBlock          npc;
    CharacterBlock    character;
    GiveItemBlock     giveItem;
    GiveGoldBlock     giveGold;
    GiveExpBlock      giveExp;
    GiveOnChoiceBlock giveOnChoice;
};