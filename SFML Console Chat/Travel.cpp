#include "Travel.h"

//Constructors & Destructors
Travel::Travel()
{
    this->castleEntranceInit = true;
    this->frameInit = false;

    this->frame = 0;
}

Travel::~Travel()
{

}

//Core
void Travel::travelCore(Assets& assets)
{
    this->castleEntrance(assets, notevent);
    this->castleDepths(assets, notevent);
}

//Draw Castle
void Travel::castleEntrance(Assets& assets, Event& notevent)
{
    if (this->castleEntranceInit == true && this->castleDepthsInit == false) {
        //Uninitialize && Reinitialize castleDepth Event
        notevent.reInitialize(assets);
        switch (this->frame) {
        case 0:
            //Draw Map Sprite
            assets.locationText.setString("Castle Entrance");
            if (this->frameInit == false) {
                assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castleentrance.jpeg");
                this->frameInit = true;
            }
            assets.map.setTexture(assets.mapTexture);
            assets.map.setPosition(440.0f, -200.0f); // absolute position
            break;
        case 1:
            if (this->frameInit == false) {
                assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/download.jpeg");
                this->frameInit = true;
            }
            assets.map.setTexture(assets.mapTexture);
            combat.combatLoop(assets);
            break;
        case 2:
            if (this->frameInit == false) {
                assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/down.jpeg");
                this->frameInit = true;
            }
            assets.map.setTexture(assets.mapTexture);
            break;
        }
    }
}

void Travel::castleDepths(Assets& assets, Event& notevent)
{
    if (this->castleEntranceInit == false && this->castleDepthsInit == true) {
        this->frame = 0;
        switch (this->frame) {
        case 0:
            assets.locationText.setString("Castle Depths");
            if (this->frameInit == false) {
                assets.mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castleDepths.jpeg");
                this->frameInit = true;
            }
            //Initialize Spade and Sprite
            notevent.spadeEncounter(assets);
            break;
        }
    }
}