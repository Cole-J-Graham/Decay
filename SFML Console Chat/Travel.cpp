#include "Travel.h"

//Constructors & Destructors
Travel::Travel()
{
    //Control control flow of what map is currently being used in travelCore() Function...
    this->introCounter = 0;
    this->forestCounter = 0;
    this->castleCounter = 0;

    //Frame Stuff
    this->frameInit = false;
    this->introCounterDialogue = -1;
    this->frame = 0;

    //Bonfire Detection initialization (Controls whether or not the detection rect is drawn...)
    this->forestBonfireInit = false;
}

Travel::~Travel()
{

}

//Core
void Travel::travelCore(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    switch (assets.mapCounter) {
    case -1:
        this->intro(window, assets, notevent, combat, player);
        break;
    case 0:
        this->forestMap(window, assets, notevent, combat, player);
        break;
    case 1:
        this->castleMap(assets, notevent, combat, player);
        break;
    }
}

//Draw Intro
void Travel::intro(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    switch (this->introCounter) {
    case 0:
        this->introBeginning(window, assets, notevent, combat, player);
        break;
    }
}

void Travel::introBeginning(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{ //Frame init true or false fucking how
    notevent.reInitialize(assets);
    switch (this->introCounterDialogue) {
    case 0:
        assets.locationText.setString("");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        
        assets.text.setString("There once was a kingdom plentiful and prosperous. The citizens had very little to worry of and days were filled with joy. Though, not all good things last forever.");
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("A horrible blight began to grow deep from within the world. This sparked a dreadful plague those would later call 'Decay' which had sprung up from the Earth without warning.\n Anyone afflicted with the illness would watch as their skin would rot off of their very body. It caused the kingdom to be brought to its limits.");
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("You were a great knight of the kingdom. Raised with a blade and eventually working your way to the top of the ranks, you were the captain of the royal guard.\n Though, despite your prestiege, you were not safe from this terrible disease either.\nYou became afflicted with the decay throughout your help with the injured and it began to rot your flesh down to the bone.");
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("Some priests seemed to unexplainably have the power to resist the decay. \nMany believed they were granted the power by God himself as they possessed the power to burn the blight from the core of a human and restore them.\nThe king of the kingdom upon discovering this quickly rushed to find a priest to stop the disease from ravaging what is left of your body.");
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("A priestess came to your aid, saving most of your body from the decay and your life. However, much of your face had been melted off from the decay, only one of your eyes now usable.\nYou stayed as a knight of the kingdom after you were rescued, though it was by now on the brink of collapse.\n\nMuch of the world outside of the kingdom had shifted and changed. Many anomalies had taken place and much of the world and its creatures were no longer what you knew.\n Chaos scratching at the kingdoms walls, you had a last stand with what was left of your royal guard leading them into battle.");
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Intro/intro6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        assets.text.setString("Despite your best efforts and hundreds of abominations slain under your sword, you had eventually fallen along with the kingdom. You had not lost your life, though nothing is left for you in these ruins.\nYou pick yourself up from the mud and begin to force yourself forwards into the lands unknown...");
        break;
    case 6:
        assets.mapCounter = 0;
        assets.text.setString("");
        break;
    }
}

//Draw Forest
void Travel::forestMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    //Pick which location is currently selected within the forest...
    switch (this->forestCounter) {
    case 0:
        this->forestBonfire(window, assets, notevent, combat, player);
        break;
    case 1:
        this->forestEntrance(assets, notevent, combat, player);
        break;
    case 2:
        this->forestDepths(assets, notevent, combat, player);
        break;
    case 3:
        this->forestAbyssal(assets, notevent, combat, player);
        break;
    }
}

void Travel::forestBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    switch (this->frame) {
    case 0:
        assets.locationText.setString("Forest Bonfire");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestbonfire.jpeg");
            this->frameInit = true;
        }
        notevent.healCharactersText(window, assets);
        notevent.smithingText(window, assets);
        assets.bonfireAssets = true;
        assets.introAssets = false; //Disable intro hiding assets for further in the game
        assets.zinCounter = 0; //Set correct frame for zins sprite to appear
        this->forestBonfireInit = true; //Draw detection rects for healing and smithing
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

void Travel::forestEntrance(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Uninit bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 1:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 2:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 3:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 4:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 5:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 6:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 7:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 8:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 9:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 10:
        assets.locationText.setString("Forest Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forest11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

void Travel::forestDepths(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 1:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 2:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 3:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 4:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 5:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 6:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 7:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 8:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 9:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 10:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths11.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 11:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Forest Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestdepths12.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

void Travel::forestAbyssal(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        this->forestBonfireInit = false; //Unint bonfire
        assets.bonfireAssets = false;
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 1:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 2:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 3:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 4:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 5:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 6:
        assets.locationText.setString("Abyssal Forest");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/abyssalwoods7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    }
}

//Draw Castle
void Travel::castleMap(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    switch (this->castleCounter) {
    case 0:
        this->castleEntrance(assets, notevent, combat, player);
        break;
    case 1:
        this->castleDepths(assets, notevent, combat, player);
        break;
    }
}

void Travel::castleEntrance(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    //Uninitialize && Reinitialize castleDepth Event
    notevent.reInitialize(assets);
    switch (this->frame) {
    case 0:
        //Draw Map Sprite
        assets.locationText.setString("Castle Entrance");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle1.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        assets.map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 1:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle2.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        combat.combatLoop(assets, player);
        break;
    case 2:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle3.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 3:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle4.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 4:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle5.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 5:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle6.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 6:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle7.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 7:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle8.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 8:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle9.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    case 9:
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castle10.jpeg");
            this->frameInit = true;
        }
        assets.map.setTexture(assets.mapTexture);
        break;
    }
}

void Travel::castleDepths(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    this->frame = 0;
    switch (this->frame) {
    case 0:
        assets.locationText.setString("Castle Depths");
        if (this->frameInit == false) {
            assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castle/castleDepths1.jpeg");
            this->frameInit = true;
        }
        //Initialize Spade and Sprite
        notevent.spadeEncounter(assets);
        break;
    }
}