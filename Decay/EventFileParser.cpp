#include "EventFileParser.h"
#include <iostream>

// ============================================================
//  Public
// ============================================================

std::vector<Beat> EventFileParser::parse(const std::string& path)
{
    std::vector<Beat> beats;

    ifs.open(path);
    if (!ifs.is_open())
    {
        std::cerr << "EventFileParser: failed to open file: " << path << "\n";
        return beats;
    }

    std::string line;
    while (true)
    {
        line = readLine();
        if (line.empty() && ifs.eof()) break;
        if (line.empty()) continue;

        if (line == "[SPEAK_NPC]")             beats.push_back(parseNPCBlock());
        else if (line == "[SPEAK_CHARACTER]")  beats.push_back(parseCharacterBlock());
        else if (line == "[GIVE_ITEM]")        beats.push_back(parseGiveItemBlock());
        else if (line == "[GIVE_GOLD]")        beats.push_back(parseGiveGoldBlock());
        else if (line == "[GIVE_EXP]")         beats.push_back(parseGiveExpBlock());
        else if (line == "[GIVE_ON_CHOICE]")   beats.push_back(parseGiveOnChoiceBlock());
        else if (line == "[FIRE_TRIGGER]")     beats.push_back(parseFireTriggerBlock());
        else if (line == "[FIRE_ON_CHOICE]")   beats.push_back(parseFireOnChoiceBlock());
        else if (line == "[IF_FOLLOWER]")      beats.push_back(parseConditionStartBlock());
        else if (line == "[END_IF]")           beats.push_back(parseConditionEndBlock());
        else if (line == "[TAKE_DAMAGE]")    beats.push_back(parseTakeDamageBlock());
        else if (line == "[TAKE_GOLD]")      beats.push_back(parseTakeGoldBlock());
        else if (line == "[TAKE_ITEM]")      beats.push_back(parseTakeItemBlock());
        else if (line == "[TAKE_ON_CHOICE]") beats.push_back(parseTakeOnChoiceBlock());
        else
            std::cout << "EventFileParser: unknown block header: " << line << "\n";
    }

    ifs.close();
    std::cout << "EventFileParser: loaded " << beats.size() << " beats from " << path << "\n";
    return beats;
}

// ============================================================
//  Block parsers
// ============================================================

Beat EventFileParser::parseNPCBlock()
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

        if (key == "NPC")            beat.npc.npc = val;
        else if (key == "EMOTION")   beat.npc.emotion = val;
        else if (key == "EMOTION_A") beat.npc.emotionA = val;
        else if (key == "EMOTION_B") beat.npc.emotionB = val;
        else if (key == "LINE") { beat.npc.lineA = val; beat.npc.lineB = val; }
        else if (key == "LINE_A")    beat.npc.lineA = val;
        else if (key == "LINE_B")    beat.npc.lineB = val;
    }

    if (beat.npc.lineB.empty()) beat.npc.lineB = beat.npc.lineA;
    return beat;
}

Beat EventFileParser::parseCharacterBlock()
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

        if (key == "CHARACTER")       beat.character.characterId = val;
        else if (key == "EMOTION")    beat.character.emotion = val;
        else if (key == "LINE")       beat.character.line = val;
        else if (key == "LINE_A")     beat.character.lineA = val;
        else if (key == "LINE_B")     beat.character.lineB = val;
        else if (key == "RESPONSE_A") beat.character.responseA = val;
        else if (key == "RESPONSE_B") beat.character.responseB = val;
    }

    // Mirror LINE_B from LINE_A if only one provided (same as NPC blocks)
    if (!beat.character.lineA.empty() && beat.character.lineB.empty())
        beat.character.lineB = beat.character.lineA;

    return beat;
}

Beat EventFileParser::parseGiveItemBlock()
{
    Beat beat;
    beat.type = Beat::Type::GIVE_ITEM;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;

        auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "ITEM")          beat.giveItem.itemId = val;
        else if (key == "QUANTITY") beat.giveItem.quantity = std::stoi(val);
    }

    return beat;
}

Beat EventFileParser::parseGiveGoldBlock()
{
    Beat beat;
    beat.type = Beat::Type::GIVE_GOLD;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;

        auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "AMOUNT") beat.giveGold.amount = std::stoi(val);
    }

    return beat;
}

Beat EventFileParser::parseGiveExpBlock()
{
    Beat beat;
    beat.type = Beat::Type::GIVE_EXP;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;

        auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "AMOUNT") beat.giveExp.amount = std::stof(val);
    }

    return beat;
}

Beat EventFileParser::parseGiveOnChoiceBlock()
{
    Beat beat;
    beat.type = Beat::Type::GIVE_ON_CHOICE;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;
        auto sep = line.find(':');
        if (sep == std::string::npos) continue;
        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "CHOICE_A_GIVEGOLD")          beat.giveOnChoice.choiceAGiveGold = std::stoi(val);
        else if (key == "CHOICE_A_GIVEITEM")      beat.giveOnChoice.choiceAGiveItemId = val;
        else if (key == "CHOICE_A_GIVEQUANTITY")  beat.giveOnChoice.choiceAGiveQuantity = std::stoi(val);
        else if (key == "CHOICE_A_GIVEEXP")       beat.giveOnChoice.choiceAGiveExp = std::stof(val);
        else if (key == "CHOICE_B_GIVEGOLD")      beat.giveOnChoice.choiceBGiveGold = std::stoi(val);
        else if (key == "CHOICE_B_GIVEITEM")      beat.giveOnChoice.choiceBGiveItemId = val;
        else if (key == "CHOICE_B_GIVEQUANTITY")  beat.giveOnChoice.choiceBGiveQuantity = std::stoi(val);
        else if (key == "CHOICE_B_GIVEEXP")       beat.giveOnChoice.choiceBGiveExp = std::stof(val);
    }
    return beat;
}


Beat EventFileParser::parseFireTriggerBlock()
{
    Beat beat;
    beat.type = Beat::Type::FIRE_TRIGGER;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;

        auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "TRIGGER") beat.fireTrigger.triggerId = val;
    }

    return beat;
}

Beat EventFileParser::parseFireOnChoiceBlock()
{
    Beat beat;
    beat.type = Beat::Type::FIRE_ON_CHOICE;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;

        auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "TRIGGER_A")      beat.fireOnChoice.triggerA = val;
        else if (key == "TRIGGER_B") beat.fireOnChoice.triggerB = val;
    }

    return beat;
}

Beat EventFileParser::parseConditionStartBlock()
{
    Beat beat;
    beat.type = Beat::Type::CONDITION_START;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;

        auto sep = line.find(':');
        if (sep == std::string::npos) continue;

        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "FOLLOWER") beat.condition.followerId = val;
    }

    return beat;
}

Beat EventFileParser::parseConditionEndBlock()
{
    Beat beat;
    beat.type = Beat::Type::CONDITION_END;
    return beat;
}

Beat EventFileParser::parseTakeDamageBlock()
{
    Beat beat;
    beat.type = Beat::Type::TAKE_DAMAGE;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;
        auto sep = line.find(':');
        if (sep == std::string::npos) continue;
        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";
        if (key == "AMOUNT") beat.takeDamage.amount = std::stof(val);
    }
    return beat;
}

Beat EventFileParser::parseTakeGoldBlock()
{
    Beat beat;
    beat.type = Beat::Type::TAKE_GOLD;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;
        auto sep = line.find(':');
        if (sep == std::string::npos) continue;
        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";
        if (key == "AMOUNT") beat.takeGold.amount = std::stoi(val);
    }
    return beat;
}

Beat EventFileParser::parseTakeItemBlock()
{
    Beat beat;
    beat.type = Beat::Type::TAKE_ITEM;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;
        auto sep = line.find(':');
        if (sep == std::string::npos) continue;
        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";
        if (key == "ITEM")          beat.takeItem.itemId = val;
        else if (key == "QUANTITY") beat.takeItem.quantity = std::stoi(val);
    }
    return beat;
}

Beat EventFileParser::parseTakeOnChoiceBlock()
{
    Beat beat;
    beat.type = Beat::Type::TAKE_ON_CHOICE;

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) break;
        auto sep = line.find(':');
        if (sep == std::string::npos) continue;
        std::string key = line.substr(0, sep);
        std::string val = (sep + 2 <= line.size()) ? line.substr(sep + 2) : "";

        if (key == "CHOICE_A_TAKEDAMAGE")        beat.takeOnChoice.choiceATakeDamage = std::stof(val);
        else if (key == "CHOICE_A_LOSEGOLD")     beat.takeOnChoice.choiceALoseGold = std::stoi(val);
        else if (key == "CHOICE_A_LOSEITEM")     beat.takeOnChoice.choiceALoseItemId = val;
        else if (key == "CHOICE_A_LOSEQUANTITY") beat.takeOnChoice.choiceALoseQuantity = std::stoi(val);
        else if (key == "CHOICE_B_TAKEDAMAGE")   beat.takeOnChoice.choiceBTakeDamage = std::stof(val);
        else if (key == "CHOICE_B_LOSEGOLD")     beat.takeOnChoice.choiceBLoseGold = std::stoi(val);
        else if (key == "CHOICE_B_LOSEITEM")     beat.takeOnChoice.choiceBLoseItemId = val;
        else if (key == "CHOICE_B_LOSEQUANTITY") beat.takeOnChoice.choiceBLoseQuantity = std::stoi(val);
    }
    return beat;
}

// ============================================================
//  Helpers
// ============================================================

std::string EventFileParser::readLine()
{
    std::string line;
    if (std::getline(ifs, line))
        return line;
    return "";
}

std::string EventFileParser::parseValue(const std::string& line)
{
    auto sep = line.find(':');
    if (sep == std::string::npos || sep + 2 > line.size()) return "";
    return line.substr(sep + 2);
}