#include "EnemyDatabase.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace
{
    std::vector<std::string> split(const std::string& text, char delimiter)
    {
        std::vector<std::string> parts;
        std::stringstream ss(text);
        std::string part;

        while (std::getline(ss, part, delimiter)) {
            if (!part.empty()) {
                parts.push_back(part);
            }
        }

        return parts;
    }

    std::vector<RewardEntry> parseRewardItems(const std::string& text)
    {
        std::vector<RewardEntry> rewards;

        if (text.empty() || text == "NONE") {
            return rewards;
        }

        std::vector<std::string> rewardTokens = split(text, ',');

        for (const std::string& token : rewardTokens) {
            std::vector<std::string> rewardParts = split(token, ':');

            if (rewardParts.size() < 2) {
                std::cerr << "Invalid reward token: " << token << "\n";
                continue;
            }

            RewardEntry reward;
            reward.itemId = rewardParts[0];
            reward.quantity = std::stoi(rewardParts[1]);

            rewards.push_back(reward);
        }

        return rewards;
    }
}

EnemyDatabase& EnemyDatabase::getInstance()
{
    static EnemyDatabase instance;
    return instance;
}

bool EnemyDatabase::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open enemy database: " << filePath << "\n";
        return false;
    }

    this->enemies.clear();
    this->enemyIndexById.clear();

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        if (line[0] == '#') {
            continue;
        }

        // Allows a header row.
        if (line.rfind("id|", 0) == 0) {
            continue;
        }

        std::vector<std::string> fields = split(line, '|');

        if (fields.size() < 16) {
            std::cerr << "Invalid enemy line: " << line << "\n";
            continue;
        }

        EnemyDefinition enemy;

        enemy.id = fields[0];
        enemy.name = fields[1];

        enemy.hp = std::stof(fields[2]);
        enemy.hpMax = std::stof(fields[3]);
        enemy.damage = std::stof(fields[4]);
        enemy.defense = std::stof(fields[5]);
        enemy.scale = std::stof(fields[6]);

        enemy.spritePath = fields[7];
        enemy.viewerPath = fields[8];

        enemy.rewards.items = parseRewardItems(fields[9]);
        enemy.rewards.gold.min = std::stoi(fields[10]);
        enemy.rewards.gold.max = std::stoi(fields[11]);
        enemy.rewards.exp.min = std::stoi(fields[12]);
        enemy.rewards.exp.max = std::stoi(fields[13]);

        enemy.moveIds = split(fields[14], ',');
        enemy.spawnAreas = split(fields[15], ',');

        if (enemy.id.empty()) {
            std::cerr << "Enemy has empty id: " << line << "\n";
            continue;
        }

        this->enemyIndexById[enemy.id] = this->enemies.size();
        this->enemies.push_back(enemy);
    }

    std::cout << "Loaded enemies: " << this->enemies.size() << "\n";
    return true;
}

const EnemyDefinition* EnemyDatabase::getEnemy(const std::string& id) const
{
    auto it = this->enemyIndexById.find(id);

    if (it == this->enemyIndexById.end()) {
        return nullptr;
    }

    return &this->enemies[it->second];
}

const std::vector<EnemyDefinition>& EnemyDatabase::getAllEnemies() const
{
    return this->enemies;
}