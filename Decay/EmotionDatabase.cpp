#include "EmotionDatabase.h"
#include "NPCManager.h"
#include "CharacterManager.h"
#include "NPC.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

EmotionDatabase& EmotionDatabase::getInstance()
{
    static EmotionDatabase instance;
    return instance;
}

bool EmotionDatabase::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "EmotionDatabase: failed to open " << filePath << "\n";
        return false;
    }

    int count = 0;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        // Split fields on '|'
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, '|'))
            fields.push_back(field);

        // Expected format:
        // type|id|displayName|assetId|scale|emotions
        // type      = NPC or CHARACTER
        // emotions  = EMOTION_NAME:assetId pairs separated by semicolons
        if (fields.size() < 5)
        {
            std::cerr << "EmotionDatabase: invalid line (too few fields): " << line << "\n";
            continue;
        }

        const std::string& type = fields[0];
        const std::string& id = fields[1];
        const std::string& displayName = fields[2];
        const std::string& assetId = fields[3];
        float scale = std::stof(fields[4]);

        // Parse emotion pairs: NEUTRAL:ovi_neutral;ANGRY:ovi_angry
        std::vector<std::pair<std::string, std::string>> emotions;
        if (fields.size() > 5 && !fields[5].empty())
        {
            std::stringstream es(fields[5]);
            std::string token;
            while (std::getline(es, token, ';'))
            {
                auto colon = token.find(':');
                if (colon == std::string::npos) continue;
                emotions.push_back({
                    token.substr(0, colon),
                    token.substr(colon + 1)
                    });
            }
        }

        if (type == "NPC")
        {
            auto npc = std::make_unique<NPC>(id, displayName, assetId, scale);
            for (const auto& [emotion, emotionAsset] : emotions)
                npc->addEmotion(emotion, emotionAsset);
            NPCManager::getInstance().addNPC(id, std::move(npc));
            count++;
        }
        else if (type == "CHARACTER")
        {
            // Characters are constructed by InitializeCharacters — we just
            // register emotion assets on the already-existing instance.
            auto character = CharacterManager::getInstance().getCharacter(id);
            if (character)
            {
                for (const auto& [emotion, emotionAsset] : emotions)
                    character->addEmotion(emotion, emotionAsset);
                count++;
            }
            else
            {
                std::cerr << "EmotionDatabase: CHARACTER not found in CharacterManager: " << id << "\n";
            }
        }
        else
        {
            std::cerr << "EmotionDatabase: unknown type '" << type << "' on line: " << line << "\n";
        }
    }

    std::cout << "EmotionDatabase: loaded " << count << " entries from " << filePath << "\n";
    return true;
}