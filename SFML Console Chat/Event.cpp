#include "Event.h"

//Constructors & Destructors
Event::Event()
{
    this->encounterInit = true;
}

Event::~Event()
{

}

//Castle Events
void Event::spadeEncounter(Assets& assets)
{
	assets.text.setString("'Get, OUT!'");
    if (this->encounterInit == true) {
        assets.soundAngry.play();
        assets.zinInitAngry = true;
        assets.spriteInit = true;
        assets.zinSprite();
        this->encounterInit = false;
    }
}
