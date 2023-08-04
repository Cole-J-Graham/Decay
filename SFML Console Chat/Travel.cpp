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
void Travel::travelCore(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    this->castleEntrance(assets, notevent, combat, player);
    this->castleDepths(assets, notevent, combat, player);
}

//Draw Castle
void Travel::castleEntrance(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    if (this->castleEntranceInit == true && this->castleDepthsInit == false) {
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
}

void Travel::castleDepths(Assets& assets, Event& notevent, Combat& combat, Player& player)
{
    if (this->castleEntranceInit == false && this->castleDepthsInit == true) {
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
}