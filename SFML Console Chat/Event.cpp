#include "Event.h"

//Constructors & Destructors
Event::Event()
{
    this->encounterInit = true;
    this->encounterInitTwo = true;
}

Event::~Event()
{

}

//Core Functions
void Event::reInitialize(Assets& assets)
{
    assets.spadeCounter = -1;//Reset Spade sprite switch case counter
    assets.spriteInit = false; //Uninitialize sprite border
    assets.dialogueCounter = 0; //Reset dialogue counter
    //assets.text.setString(""); //Reset dialogue box

    this->encounterInit = true; //Reset Local Control Flow Bools
    this->encounterInitTwo = true;
}

//Castle Events
void Event::spadeEncounter(Assets& assets)
{
    //Initiate Dialogue
    switch (assets.dialogueCounter) {
    case 0:
        if (this->encounterInit == true) {
            assets.spriteInit = true; //Initialize Sprite Border
            assets.spadeInit = false; //Allow Spades Sprite from Assets to be usable again
            assets.spadeCounter = 0; //Pick which Spade Sprite to use via switch statement
            assets.text.setString("Hey, what are you doing here...?"); //Set text for what's happening
            this->encounterInit = false; //Ensure this only runs once...
        }
        break;
    case 1:
        if (this->encounterInitTwo == true) {
            assets.spadeCounter = 1;
            assets.text.setString("Get OUT!");
            assets.soundAngry.play();
            this->encounterInitTwo = false;
        }
        break;
    case 2:
        std::cout << "Success";
        break;
    }
}
