#pragma once
#include "Beat.h"
#include <fstream>
#include <vector>
#include <string>

// ============================================================
//  EventFileParser
//  Stateless parser — opens a file, reads all blocks, returns
//  a vector<Beat>. Knows nothing about game state or managers.
// ============================================================

class EventFileParser
{
public:
    // Returns an empty vector if the file cannot be opened.
    std::vector<Beat> parse(const std::string& path);

private:
    Beat parseNPCBlock();
    Beat parseCharacterBlock();
    Beat parseGiveItemBlock();
    Beat parseGiveGoldBlock();
    Beat parseGiveExpBlock();
    Beat parseGiveOnChoiceBlock();

    std::string readLine();
    std::string parseValue(const std::string& line);

    std::ifstream ifs;
};