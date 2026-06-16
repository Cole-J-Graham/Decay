#pragma once
#include "CharacterManager.h"
#include "CharacterUnlockRegistry.h"

class InitializeCharacters
{
public:
    //Static method to get the singleton instance
    static InitializeCharacters& getInstance();

    //Delete the copy constructor and assignment operator
    InitializeCharacters(const InitializeCharacters&) = delete;
    InitializeCharacters& operator=(const InitializeCharacters&) = delete;

    //Public method to initialize characters and stats
    void initialize();

private:
    //Private constructor and destructor to prevent direct instantiation
    InitializeCharacters();
    ~InitializeCharacters();

    //Character Functions
    void initCharacters();
    void initNPCs();

    //Stat Functions
    void initStats();

    //Lore Functions
    void initLore();

    // Restore characters whose unlock flags are already set (save/load)
    void restoreUnlockedCharacters();
};