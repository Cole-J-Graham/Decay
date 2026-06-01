#pragma once

#include "EnemyTypes.h"

#include <string>
#include <unordered_map>
#include <vector>

class EnemyDatabase
{
public:
    static EnemyDatabase& getInstance();

    EnemyDatabase(const EnemyDatabase&) = delete;
    EnemyDatabase& operator=(const EnemyDatabase&) = delete;

    bool loadFromFile(const std::string& filePath);

    const EnemyDefinition* getEnemy(const std::string& id) const;
    const std::vector<EnemyDefinition>& getAllEnemies() const;

private:
    EnemyDatabase() = default;

private:
    std::vector<EnemyDefinition> enemies;
    std::unordered_map<std::string, std::size_t> enemyIndexById;
};